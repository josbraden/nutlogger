#include <iostream>
#include <string>
#include "nutlogger.h"
using namespace std;

int main(int argc, char *argv[]) {
    //Handle args
    string arg;
    argobj args;
    if (argc > 1) {
        for (int i = 1; i <= argc; i++) {
            arg = argv[i];
            if (arg.compare("-h") == 0) {
                cout << "Usage: nutlogger [-v]" << endl;
                return 0;
            }
            else if (arg.compare("-v") == 0) {
                args.verbose = true;
            }
            else {
                cout << "Error: unknown arg entered. Use -h for help" << endl;
                return 1;
            }
        }
    }
    return init(args);
}
