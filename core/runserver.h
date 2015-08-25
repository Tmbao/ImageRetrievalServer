#ifndef RUNSERVER_H_INCLUDED
#define RUNSERVER_H_INCLUDED

#include "configurations.h"
#include "app/appdata.h"
#include "extract/extract.h"
#include "quantize/quantize.h"
#include "query/query.h"
#include "utils/score.h"
#include "utils/utils.h"


// Import postgresql
#include <pqxx/pqxx> 
using namespace pqxx;

#include <thread>
#include <unistd.h>


struct Request {
    int id;
    string fileName;
    Request(int _id = 0, string _fileName = ""): id(_id), fileName(_fileName) {}
};


connection db("hostaddr=" + sqlHost + " port=5432 dbname=irserverdb user=" + sqlUser + " password=" + sqlPassword);

void processQuery(int id, string fileName) {

    printf("Process %d: %s\n", id, fileName.c_str());

    AppData *app = AppData::getInstance();
    int nDocs = app->path.size();

    string kpPath = fileName + ".kp.mat";
    string siftPath = fileName + ".sift.mat";
    string tempPath = fileName + ".temp.mat";
    string weightPath = fileName + ".weight.mat";
    string termIDPath = fileName + ".term.mat";
    string imgPath = fileName;

    mat _kp, _sift;
    extractFeatures(imgPath, _kp, _sift, kpPath, siftPath, tempPath, true);

    vec _weights;
    icol _termID;
    buildBoW(_sift, _weights, _termID, weightPath, termIDPath, true);

    vector<double> qTfidf = app->ivt.makeQueryTfidf(_weights, _termID);

    // Compute ranked list
    Score score(computeAllScores(qTfidf));
    vector<int> rankedList(nDocs);
    for (int i = 0; i < nDocs; i++)
        rankedList[i] = i;
    sort(rankedList.begin(), rankedList.end(), score);

   	vector <int> cntClass(nClass);
    for (int i = 0; i * i < nDocs; i++) {
        string fileBaseName = getFileBaseName(app->path[rankedList[i]]);
        int classId = (fileBaseName[0] - '0') * 10 + fileBaseName[1] - '0';
        cntClass[classId]++;
    }

    int resClass = 0;
    for (int i = 1; i < nClass; ++i)
    	if (cntClass[resClass] < cntClass[i])
    		resClass = i;

    vector <string> rankedListStr(1);
    sprintf(rankedListStr[0].c_str(), "%02d", resClass);

    // Save ranked list into db
    string pgArray = vectorToPgArray(rankedListStr);

    work upd(db);
    upd.exec("update iradapter_responserankedlist \
        set (content, status) = ('" + pgArray + "', 'C') \
        where id = " + to_string(id));
    upd.commit();
}

void runServer() {

    try {

        while (true) {
            printf("Fetching requests\n");

            vector<Request> requests;

            // Fetching all current requests
            nontransaction slt(db);

            result res(slt.exec("select * \
                from iradapter_requestimage as ri inner join iradapter_responserankedlist as rl \
			on ri.id = rl.request_id \
                where rl.status = 'P'"));
            for (result::const_iterator it = res.begin(); it != res.end(); it++)
                requests.push_back(Request(it[0].as<int>(), it[1].as<string>()));
            slt.commit();

            if (!requests.empty()) {
                // Process requests
                for (Request request : requests) {
                    // Create thread
                    thread tQuery(processQuery, request.id, mediaRoot + "/" + request.fileName);
                    tQuery.join();
                }
            }

            printf("Sleeping...\n");
            usleep(loopSleepTime);
        }

        db.disconnect();
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

#endif
