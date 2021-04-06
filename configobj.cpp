#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "nutlogger.h"
using namespace std;

void configobj::setconfigfield(string key, string value) {
    int value_int = 0;
    if (key.compare("mysql_username") == 0) {
        mysql_username = value;
    }
    else if (key.compare("mysql_password") == 0) {
        mysql_password = value;
    }
    else if (key.compare("mysql_host") == 0) {
        mysql_host = value;
    }
    else if (key.compare("mysql_database") == 0) {
        mysql_database = value;
    }
    else if (key.compare("nut_server") == 0) {
        nut_server = value;
    }
    else if (key.compare("nut_port") == 0) {
        value_int = stoi(value);
        //Entire TCP port range is a pretty wide sanity check
        if (value_int > 1 && value_int < 65535) {
            nut_port = value_int;
        }
    }
    else if (key.compare("pollinterval") == 0) {
        value_int = stoi(value);
        //Maximum poll wait: 24 hours
        //Minimum: 2 seconds
        if (value_int < 86400 && value_int > 2) {
            pollinterval = value_int;
        }
    }
    else if (key.compare("upsname") == 0) {
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

//Function to populate the upsidlist with the IDs of the UPSs in the upslist
void configobj::set_upsidlist() {
    for (long unsigned int i = 0; i < upslist.size(); i++) {
        upsidlist[i] = getupsid(*this, i);
    }
}
