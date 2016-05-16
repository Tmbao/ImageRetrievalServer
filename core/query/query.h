#ifndef QUERY_H_INCLUDED
#define QUERY_H_INCLUDED


#include "../configurations.h"
#include "../app/appdata.h"


vector<double> computeAllScores(vector<double> qTfidf) {
    AppData *app = AppData::getInstance();

    vector<double> scores(app->ivt.nDocs);
    for (int i = 0; i < app->ivt.nWords; i++) {
        if (abs(qTfidf[i]) < EPS)
            continue;
        for (int j = 0; j < app->ivt.index[i].size(); j++)
            scores[app->ivt.index[i][j]] += qTfidf[i] * app->ivt.tfidf[i][j];
    }
    
    return scores;
}

vector<double> computeAllAsymScores(vector<double> qTfidf, double alpha = 0.5) {
    AppData *app = AppData::getInstance();

	double nume = 0, deno = 0;
	for (int i = 0; i < app->ivt.nWords; i++) {
		for (int j = 0; j < app->ivt.index[i].size(); j++) {
			nume += app->ivt.tfidf[i][j];
		    deno += min(app->ivt.tfidf[i][j], qTfidf[i]);
		}
		if (std::isnan(qTfidf[i])) {
			debugVar(i);
			break;
		}
	}
	double weight = alpha * nume / (deno * app->ivt.nDocs);
	debugVar(app->ivt.nDocs);
	debugVar(nume);
	debugVar(deno);
	debugVar(weight);

	vector<double> scores(app->ivt.nDocs);
	for (int i = 0; i < app->ivt.nWords; i++) {
		for (int j = 0; j < app->ivt.index[i].size(); j++) {
			scores[app->ivt.index[i][j]] += min(qTfidf[i], app->ivt.tfidf[i][j]) * weight - app->ivt.tfidf[i][j];
		}
	}

	return scores;
}

#endif
