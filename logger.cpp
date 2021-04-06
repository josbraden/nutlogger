/*
Main logger loop code
*/
#include <iostream>
#include <string>
#include <vector>
#include "nutlogger.h"
using namespace std;

int logger(configobj config) {
    //Before starting loop, see if devices are in database yet
    if (config.verbose) {
        cout << "Checking database for devices..." << endl;
    }
    for (long unsigned int i = 0; i < config.upslist.size(); i++) {
        if (getupsknt(config, i) != 1) {
            if (config.verbose) {
                cout << "Adding " << config.upslist[i] << " to database" << endl;
            }
            addups(config, i);
        }
    }
    //Get device IDs
    if (config.verbose) {
        cout << "Getting device IDs from database" << endl;
    }
    //Update 'extra' dvice info
    if (config.verbose) {
        cout << "Updating device extra data fields" << endl;
    }
    //Other startup stuff?
    //Start logging loop
    if (config.verbose) {
        cout << "Starting logging" << endl;
    }
    return 0;
}
