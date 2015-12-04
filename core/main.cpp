#include "configurations.h"
#include "initialize.h"
#include "runserver.h"
#include "test.h"

#include "app/appdata.h"
#include "extract/extract.h"
#include "quantize/quantize.h"
#include "query/query.h"
#include "utils/score.h"
#include "utils/utils.h"


int main(int argc, char **argv) {
    cout << "argc " << argc << endl;    

    // Initialize
    // extractAll();
    // quantizeAllData();
    //initializeClassName();
    extractAndQuantizeAll();

    if (argc > 1) {
        if (strcmp(argv[1], "test") == 0) {
            runTest(5); // Perform query expansion on top 50
	} else if (strcmp(argv[1], "runserver") == 0) {
            runServer();
        }
    }

    return 0;
}
