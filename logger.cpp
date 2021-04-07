/*
Main logger loop code
*/
#include <iostream>
#include <string>
#include <vector>
#include "nutlogger.h"
using namespace std;

int logger(configobj config) {
    extradataobj extradata;
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
    config.set_upsidlist();
    if (config.upslist.size() != config.upsidlist.size()) {
        if (config.verbose) {
            cout << "Error: not all devices have a corresponding ID, exiting" << endl;
        }
        return 3;
    }
    //Update 'extra' dvice info
    if (config.verbose) {
        cout << "Updating device extra data fields" << endl;
    }
    for (long unsigned int i = 0; i < config.upslist.size(); i++) {
        extradata.status = 0;
        extradata = getextradata(config, i);
        if (extradata.status == 0) {
            updateextradata(config, i, extradata);
        }
    }
    //Start logging loop
    if (config.verbose) {
        cout << "Starting logging" << endl;
    }
    return 0;
}
