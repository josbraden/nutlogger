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
                    config = setconfigfield(config, key, value);
                }
            }
        }
    }
    infile.close();
    //TODO Start program
    return 0;
}

//Function to map config file options to the config object variables
configobj setconfigfield(configobj config, string key, string value) {
    int value_int = 0;
    if (key.compare("mysql_username") == 0) {
        config.mysql_username = value;
    }
    else if (key.compare("mysql_password") == 0) {
        config.mysql_password = value;
    }
    else if (key.compare("mysql_host") == 0) {
        config.mysql_host = value;
    }
    else if (key.compare("mysql_database") == 0) {
        config.mysql_database = value;
    }
    else if (key.compare("nut_server") == 0) {
        config.nut_server = value;
    }
    else if (key.compare("nut_port") == 0) {
        value_int = stoi(value);
        //Entire TCP port range is a pretty wide sanity check
        if (value_int > 1 && value_int < 65535) {
            config.nut_port = value_int;
        }
    }
    else if (key.compare("pollinterval") == 0) {
        value_int = stoi(value);
        if (value_int < 300 && value_int > 2) {
            config.pollinterval = value_int;
        }
    }
    else {
        if (config.verbose) {
            cout << "Ignoring unknown config entry: " << key << "=" << value << endl;
        }
    }
    return config;
}
