/*
Handles startup stuff, config file reading and other settings

Config parsing from:
https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c

Vector sorting and unique-ing from:
https://stackoverflow.com/questions/26824260/c-unique-values-in-a-vector
*/
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "nutlogger.h"
#include "version.h"
using namespace std;

//Handles program initialization
int init(argobj args) {
    configobj config;
    ifstream infile;
    string line, key, value;
    string configfile = "nutlogger.cnf";
    //Set variables from args
    config.verbose = args.verbose;
    //Open and parse config file
    infile.open(configfile, ios::in);
    if (!infile) {
        if (config.verbose) {
            cout << "Error: " << configfile << " not found!" << endl;
        }
        return 2;
    }
    while (getline(infile, line)) {
        if (!(line.at(0) == '#')) {
            istringstream is_line(line);
            if (getline(is_line, key, '=')) {
                if (getline(is_line, value)) {
                    config.setconfigfield(key, value);
                }
            }
        }
    }
    infile.close();
    if (config.upslist.size() == 0) {
        if (config.verbose) {
            cout << "No UPS devices listed for monitor, exiting" << endl;
        }
        return 0;
    }
    //Sort and unique config.upslist
    config.upslist_sortUnique();
    //TODO Start program
    return 0;
}
