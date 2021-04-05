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
    for (long unsigned int i = 0; i < config.upslist.size(); i++) {
        if (getupsknt(config, i) != 1) {
            //Add device to MySQL database
        }
    }
    return 0;
}
