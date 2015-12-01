#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "../configurations.h"
#include "../app/appdata.h"


string getFileBaseName(string fileName) {
    return fileName.substr(0, fileName.rfind("."));
}

int parseInt(string s) {
    return atoi(s.c_str());
}

string vectorToJson(vector<string> v, string name) {
    string json = "{\n\t" + name + ": [\n";
    for (int i = 0; i < v.size(); i++) {
        json += "\t\t" + v[i];
        if (i + 1 < v.size())
            json += ",";
        json += "\n";
    }
    json += "\t]\n}";
    return json;
}

string vectorToPgArray(vector<string> v) {
    string pgArray = "{";
    for (int i = 0; i < v.size(); i++) {
        pgArray += "\"" + v[i] + "\"";
        if (i + 1 < v.size())
            pgArray += ", ";
    }
    pgArray += "}";
    return pgArray;
}

void loadBoW(int imageId, vec &weights, icol &termID) {
    AppData *app = AppData::getInstance();
    string imgPath = app->path[imageId];
    
    debugVar(imageId);

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

   // app->kp.push_back(_kp);

    buildBoW(_sift, weights, termID, weightPath, termIDPath, forceOverwrite);
}

#endif
