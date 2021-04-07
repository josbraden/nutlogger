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

extradataobj getextradata(configobj config, int index) {
    extradataobj extradata;
    try {
        nut::Client* nutclient = new nut::TcpClient(config.nut_server, config.nut_port);
        nut::Device nutdevice = nutclient->getDevice(config.upslist[index]);
        //This would be better with some kind of loop but eh
        nut::Variable nutvar = nutdevice.getVariable("battery.charge.low");
        extradata.battery_charge_low = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("battery.charge.warning");
        extradata.battery_charge_warning = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("battery.mfr.date");
        extradata.battery_mfr_date = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("battery.runtime.low");
        nutvar = nutdevice.getVariable("battery.type");
        nutvar = nutdevice.getVariable("battery.voltage.nominal");
        nutvar = nutdevice.getVariable("device.mfr");
        nutvar = nutdevice.getVariable("device.model");
        nutvar = nutdevice.getVariable("device.serial");
        nutvar = nutdevice.getVariable("device.type");
        nutvar = nutdevice.getVariable("driver.name");
        nutvar = nutdevice.getVariable("driver.version");
        nutvar = nutdevice.getVariable("driver.version.data");
        nutvar = nutdevice.getVariable("driver.version.internal");
        nutvar = nutdevice.getVariable("input.voltage.nominal");
        nutvar = nutdevice.getVariable("ups.beeper.status");
        nutvar = nutdevice.getVariable("ups.delay.shutdown");
        nutvar = nutdevice.getVariable("ups.delay.start");
        nutvar = nutdevice.getVariable("ups.mfr");
        nutvar = nutdevice.getVariable("ups.model");
        nutvar = nutdevice.getVariable("ups.productid");
        nutvar = nutdevice.getVariable("ups.realpower.nominal");
        nutvar = nutdevice.getVariable("ups.serial");
        nutvar = nutdevice.getVariable("ups.test.result");
        nutvar = nutdevice.getVariable("ups.timer.shutdown");
        nutvar = nutdevice.getVariable("ups.timer.start");
        nutvar = nutdevice.getVariable("ups.vendorid");
    }
    catch(nut::NutException& ex) {
            if (config.verbose) {
                cerr << "Unexpected problem : " << ex.str() << endl;
            }
            extradata.status = 1;
            return extradata;
        }
    return extradata;
}
