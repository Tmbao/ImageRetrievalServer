#include <bits/stdc++.h>
#include "dirent.h"

using namespace std;

const string apFolder = "Dataset/ap/";

int main() {
    DIR *dir = opendir(apFolder.c_str());
    long double mAP = 0;
    int cnt = 0;
    cout << "start\n";
    while (dirent *pdir = readdir(dir)) {
        string fName = pdir->d_name;

        if (fName == ".." || fName == ".")
            continue;
	
	fName = apFolder + fName;

	cout << fName << " ";

        ifstream fin(fName.c_str());
        cout << fName << endl;
        long double ap;

        fin >> ap;
        fin.close();
        cout << ap << endl;

        ++cnt;
        mAP += ap;
    }

    cout << cnt << "files"  << " mAP:" << mAP / cnt << endl;
}
