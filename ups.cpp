#include <iostream>
#include <string>
#include <vector>
#include <nutclient.h>
#include "nutlogger.h"
using namespace std;

//Function to test connection to all UPS devices
int testups(configobj config) {
    string testvar;
    if (config.verbose) {
        cout << "Testing UPS devices..." << endl;
    }
    for (long unsigned int i = 0; i < config.upslist.size(); i++) {
        try {
            nut::Client* nutclient = new nut::TcpClient(config.nut_server, config.nut_port);
            nut::Device nutdevice = nutclient->getDevice(config.upslist[i]);
            testvar = nutdevice.getDescription();
            if (config.verbose) {
                cout << "Device " << config.upslist[i] << " description: " << testvar << endl;
            }
            nut::Variable nutvar = nutdevice.getVariable("device.model");
            testvar = nutvar.getValue()[0];
            if (config.verbose) {
                cout << "Device " << config.upslist[i] << " model: " << testvar << endl;
            }
        }
        catch(nut::NutException& ex) {
            if (config.verbose) {
                cerr << "Unexpected problem : " << ex.str() << endl;
            }
            return 1;
        }
    }
    return 0;
}
