#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../include/nutlogger.h"
using namespace std;

void configobj::setconfigfield(string key, string value) {
    int value_int = 0;
    if (!key.compare("mysql_username")) {
        mysql_username = value;
    }
    else if (!key.compare("mysql_password")) {
        mysql_password = value;
    }
    else if (!key.compare("mysql_host")) {
        mysql_host = value;
    }
    else if (!key.compare("mysql_database")) {
        mysql_database = value;
    }
    else if (!key.compare("nut_server")) {
        nut_server = value;
    }
    else if (!key.compare("nut_port")) {
        value_int = stoi(value);
        //Entire TCP port range is a pretty wide sanity check
        if (value_int > 1 && value_int < 65535) {
            nut_port = value_int;
        }
    }
    else if (!key.compare("pollinterval")) {
        value_int = stoi(value);
        //Maximum poll wait: 24 hours
        //Minimum: 2 seconds
        if (value_int < 86400 && value_int > 2) {
            pollinterval = value_int;
        }
    }
    else if (!key.compare("upsname")) {
        upslist.push_back(value);
    }
    else {
        if (verbose) {
            cout << "Ignoring unknown config entry: " << key << "=" << value << endl;
        }
    }
}

//Function to sort and unique the UPS device list
void configobj::upslist_sortUnique() {
    sort(upslist.begin(), upslist.end());
    vector<string>::iterator it;
    it = unique(upslist.begin(), upslist.end());
    upslist.resize(distance(upslist.begin(),it));
}
