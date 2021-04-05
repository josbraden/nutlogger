/*
Config parsing from:
https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c
*/
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "nutlogger.h"
#include "version.h"
using namespace std;

//Handles program initialization
int init(argobj args) {
    ifstream infile;
    string line, key, value;
    string configfile = "nutlogger.cnf";
    //Open and parse config file
    infile.open(configfile, ios::in);
    if (!infile) {
        cout << "Error: " << configfile << " not found!" << endl;
        return 2;
    }
    while (getline(infile, line)) {
        if (!(line.at(0) == '#')) {
            istringstream is_line(line);
            if (getline(is_line, key, '=')) {
                if (getline(is_line, value)) {
                    //todo store the key,value in the config object
                    //store_line(key, value);
                }
            }
        }
    }
    infile.close();
    return 0;
}
