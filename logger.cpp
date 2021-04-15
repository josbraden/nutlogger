/*
Main logger loop code
*/
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "nutlogger.h"
using namespace std;

int logger(configobj config) {
    extradataobj extradata;
    logdataobj logdata;
    vector<logdataobj> initialstate;
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
    config = set_upsidlist(config);
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
    //Get initial status for event triggering
    if (config.verbose) {
        cout << "Getting inital UPS state" << endl;
    }
    for (long unsigned int i = 0; i < config.upslist.size(); i++) {
        initialstate[i] = getlogdata(config, i);
    }
    //Start logging loop
    if (config.verbose) {
        cout << "Starting logging" << endl;
    }
    while (true) {
        for (long unsigned int i = 0; i < config.upslist.size(); i++) {
            if (config.verbose) {
                cout << "Querying " << config.upslist[i] << endl;
            }
            logdata.status = 0;
            logdata = getlogdata(config, i);
            addlogentry(config, i, logdata);
            checkevent(config, i, initialstate[i], logdata);
            //TODO trigger events
        }
        if (config.singleloop) {
            return 0;
        }
        if (config.verbose) {
            cout << "Sleeping for " << config.pollinterval << " seconds" << endl;
        }
        sleep(config.pollinterval);
    }
    return 0;
}

//Checks if an event has occurred, and if so adds an entry in the events table
//Return 0 if no event happened, 1 if an event happened
int checkevent(configobj config, int index, logdataobj initialdata, logdataobj logdata) {
    if (logdata.battery_charge != initialdata.battery_charge || logdata.ups_status != initialdata.ups_status) {
        if (config.verbose) {
            cout << "Event detected! Logging to database" << endl;
        }
        addevententry(config, index, logdata);
        return 1;
    }
    return 0;
}

//Function to populate the upsidlist with the IDs of the UPSs in the upslist
configobj set_upsidlist(configobj config) {
    int upsid;
    for (long unsigned int i = 0; i < config.upslist.size(); i++) {
        upsid = getupsid(config, i);
        config.upsidlist.push_back(upsid);
    }
    return config;
}
