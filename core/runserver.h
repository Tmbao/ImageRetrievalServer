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

void processQuery(int id, string fileName, int queryExpansion = 0) {

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

    if (queryExpansion) {
        int nVerified = queryExpansion + 1;
        double qeVec[number_of_visual_words];
        for (int i = 0; i < number_of_visual_words; i++) 
            qeVec[i] = 0;
        // Initialize with query image
        for (int i = 0; i < _weights.size(); i++)
            qeVec[_termID[i]] += _weights[i];

        // Add the top image
        for (int i = 0; i < queryExpansion; i++) {
            vec _tweights;
            icol _ttermID;
            loadBoW(rankedList[i], _tweights, _termID);
            for (int j = 0; j < _tweights.size(); j++)
                qeVec[_ttermID[j]] += _tweights[j];
        }

        int nWords = 0;
        for (int i = 0; i < number_of_visual_words; i++)
            if (qeVec[i] > 0) 
                nWords++;
            
        _weights = vec(nWords);
        _termID = icol(nWords);
        for (int i = 0, j = 0; i < number_of_visual_words; i++) 
            if (qeVec[i] > 0) {
                _weights[j] = qeVec[i] / nVerified;
                _termID[j] = i;
                j++;
            }


        qTfidf = app->ivt.makeQueryTfidf(_weights, _termID);
        score = Score(computeAllScores(qTfidf));
        sort(rankedList.begin(), rankedList.end(), score);
    }

    vector<string> rankedListStr;

    for (int i = 0; i < nDocs; i++) {
        string fileName  = getFileBaseName(app->path[rankedList[i]]);
        if (i < 20) {
            debugVar(score.score[rankedList[i]]);
            debugVar(fileName);
        }
        fileName = fileName.substr(0, fileName.rfind('.'));
        vector<string> classes = groups[fileName];
        for (string className : classes) 
            rankedListStr.push_back(className);
    }

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
            // printf("Fetching requests\n");

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
                    thread tQuery(processQuery, request.id, mediaRoot + "/" + request.fileName, 0);
                    tQuery.join();
                }
            }

            // printf("Sleeping...\n");
            usleep(loopSleepTime);
        }

        db.disconnect();
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

#endif
