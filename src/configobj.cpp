#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unistd.h>
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

//Function to get the exe's running directory
string configobj::getexepath() {
    string fullFileName = "";

    // Code taken from: http://www.gamedev.net/community/forums/topic.asp?topic_id=459511
    // Further plagerized from: https://cplusplus.com/forum/unices/14780/
    string path = "";
    pid_t pid = getpid();
    char buf[20] = {0};
    sprintf(buf,"%d",pid);
    string _link = "/proc/";
    _link.append( buf );
    _link.append( "/exe");
    char proc[512];
    int ch = readlink(_link.c_str(),proc,512);
    if (ch != -1) {
        proc[ch] = 0;
        path = proc;
        string::size_type t = path.find_last_of("/");
        path = path.substr(0,t);
    }
    fullFileName = path + string("/");
    configfile = fullFileName + configfilename;
}
