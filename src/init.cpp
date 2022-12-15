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
#include <cstring>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "../include/nutlogger.h"
using namespace std;

//Handles program initialization
int init(argobj args) {
    configobj config;
    ifstream infile;
    string line, key, value;
    //Set variables from args
    config.verbose = args.verbose;
    config.singleloop = args.singleloop;
    config.mysql_compress = args.mysql_compress;
    //Get config file location
    config.getexepath();
    //Open and parse config file
    infile.open(config.configfile, ios::in);
    if (!infile) {
        if (config.verbose) {
            cout << "Error: " << config.configfile << " not found!" << endl;
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
    //Sort and unique config.upslist
    config.upslist_sortUnique();
    if (!config.upslist.size()) {
        if (config.verbose) {
            cout << "No UPS devices listed for monitor, exiting" << endl;
        }
        return 0;
    }
    //Test MySQL and UPS connections
    if (testups(config)) {
        if (config.verbose) {
            cout << "Error while testing UPS devices, exiting" << endl;
        }
        return 1;
    }
    if (testmysql(config)) {
        if (config.verbose) {
            cout << "Error testing MySQL connection, exiting" << endl;
        }
        return 1;
    }
    //Start main program loop
    return logger(config);
}
