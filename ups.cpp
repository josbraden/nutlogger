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
        extradata.battery_runtime_low = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("battery.type");
        extradata.battery_type = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("battery.voltage.nominal");
        extradata.battery_voltage_nominal = stof(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("device.mfr");
        extradata.device_mfr = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("device.model");
        extradata.device_model = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("device.serial");
        extradata.device_serial = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("device.type");
        extradata.device_type = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("driver.name");
        extradata.driver_name = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("driver.version");
        extradata.driver_version = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("driver.version.data");
        extradata.driver_version_data = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("driver.version.internal");
        extradata.driver_version_internal = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("input.voltage.nominal");
        extradata.input_voltage_nominal = stof(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.beeper.status");
        extradata.ups_beeper_status = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("ups.delay.shutdown");
        extradata.ups_delay_shutdown = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.delay.start");
        extradata.ups_delay_start = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.mfr");
        extradata.ups_mfr = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("ups.model");
        extradata.ups_model = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("ups.productid");
        extradata.ups_productid = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("ups.realpower.nominal");
        extradata.ups_realpower_nominal = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.serial");
        extradata.ups_serial = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("ups.test.result");
        extradata.ups_test_result = nutvar.getValue()[0];
        nutvar = nutdevice.getVariable("ups.timer.shutdown");
        extradata.ups_timer_shutdown = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.timer.start");
        extradata.ups_timer_start = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.vendorid");
        extradata.ups_vendorid = stoi(nutvar.getValue()[0]);
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

logdataobj getlogdata(configobj config, int index) {
    logdataobj logdata;
    try {
        nut::Client* nutclient = new nut::TcpClient(config.nut_server, config.nut_port);
        nut::Device nutdevice = nutclient->getDevice(config.upslist[index]);
        nut::Variable nutvar = nutdevice.getVariable("battery.charge");
        logdata.battery_charge = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("battery.runtime");
        logdata.battery_runtime = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("battery.voltage");
        logdata.battery_voltage = stof(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("input.voltage");
        logdata.input_voltage = stof(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("output.voltage");
        logdata.output_voltage = stof(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.load");
        logdata.ups_load = stoi(nutvar.getValue()[0]);
        nutvar = nutdevice.getVariable("ups.status");
        logdata.ups_status = nutvar.getValue()[0];
    }
    catch(nut::NutException& ex) {
        if (config.verbose) {
            cerr << "Unexpected problem : " << ex.str() << endl;
        }
        logdata.status = 1;
        return logdata;
    }
    return logdata;
}
