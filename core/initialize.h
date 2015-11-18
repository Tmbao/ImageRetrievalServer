#ifndef INITIALIZE_H_INCLUDED
#define INITIALIZE_H_INCLUDED


#include "configurations.h"
#include "app/appdata.h"
#include "extract/extract.h"
#include "quantize/quantize.h"


map<string, vector<string>> groups;

void loadClass(string className, string path) {
    FILE *file = fopen(path.c_str(), "r");
    char fileName[100];
    while (fscanf(file, "%s", fileName) != EOF) 
        groups[fileName].push_back(className);
    fclose(file);
}

void initializeClassName() {
    DIR *dir = opendir(groundtruthFolder.c_str());
    while (dirent *pdir = readdir(dir)) {
        string fName = pdir->d_name;
        if (fName[0] == '.') continue;

        string className = fName.substr(0, fName.rfind('_'));
        className = className.substr(0, className.rfind('_'));
        loadClass(className, groundtruthFolder + '/' + fName);
    }

}

void extractAndQuantizeAll() {

    AppData *app = AppData::getInstance();

//    Get list of image files
    DIR *dir = opendir(dataFolder.c_str());
    while (dirent *pdir = readdir(dir)) {
        string fName = pdir->d_name;
        if (fName[0] == '.') continue;

        app->path.push_back(fName);
    }

    debugInfo("Extracting features");

//    Extract features
    app->path.shrink_to_fit();
    // app->kp.reserve(app->path.size());
    // app->sift.reserve(app->path.size());

    buildIndex(forceOverwrite);

    for (int i = 0; i < app->path.size(); i++) {
        string imgPath = app->path[i];

        debugVar(imgPath);

        string tmp = imgPath;
        tmp.replace(tmp.size() - 3, 3, "mat");

        string kpPath = kpFolder + "/" + tmp;
        string siftPath = siftFolder + "/" + tmp;
        string tempPath = tempFolder + "/" + tmp;
        string weightPath = weightFolder + "/" + tmp;
        string termIDPath = termIDFolder + "/" + tmp;

        imgPath = dataFolder + "/" + imgPath;

        debugVar(imgPath);
        debugVar(kpPath);
        debugVar(siftPath);
        debugVar(weightPath);
        debugVar(termIDPath);

        mat _kp, _sift;
        extractFeatures(imgPath, _kp, _sift, kpPath, siftPath, tempPath, forceOverwrite);

        app->kp.push_back(_kp);

        vec _weights;
        icol _termID;

        buildBoW(_sift, _weights, _termID, weightPath, termIDPath, forceOverwrite);
        
//        Insert to inverted index
        app->ivt.add(_weights, _termID, i);
    }

    //    Build TFIDF
    app->ivt.buildTfidf();
}

#endif
