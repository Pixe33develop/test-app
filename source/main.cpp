#include "options_parser.h"
#include "worker.h"

#include <iostream>

#include <algorithm>

using namespace std;

int main (int argc, char **argv)
{
    OptionsParser parser(argc, argv);

    if (parser.hasError()) {
        cout << parser.errorMessage() << endl << endl;
        cout << parser.helpInfo() << endl;
        return 0;
    }

    Worker worker(parser.operationType());

    cout << "Begin conversion..." << endl;

    worker.process(parser) ? cout << "Conversion success!" << endl
                           : cout << "Conversion failed!" << endl;

    return 0;
}
