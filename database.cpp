/*
For database related functionality
*/
#include <iostream>
#include <string>
#include <unistd.h>
#include "nutlogger.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace std;

//Simple function to test connectivity to MySQL server
int testmysql(configobj config) {
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::ConnectOptionsMap connection_properties;
		sql::Statement *stmt;
		sql::ResultSet *res;
		connection_properties["hostName"] = config.mysql_host;
		connection_properties["userName"] = config.mysql_username;
		connection_properties["password"] = config.mysql_password;
		connection_properties["schema"] = config.mysql_database;
		connection_properties["CLIENT_COMPRESS"] = config.mysql_compress;
		driver = get_driver_instance();
		con = driver->connect(connection_properties);
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT 'test connection'");
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return 1;
	}
	return 0;
}

//Gets number of UPSs with given name in config.upslist index
int getupsknt(configobj config, int index) {
    string query = "SELECT COUNT(*) FROM devices WHERE name = " + config.upslist[index];
    int ret;
    try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::ConnectOptionsMap connection_properties;
		sql::Statement *stmt;
		sql::ResultSet *res;
		connection_properties["hostName"] = config.mysql_host;
		connection_properties["userName"] = config.mysql_username;
		connection_properties["password"] = config.mysql_password;
		connection_properties["schema"] = config.mysql_database;
		connection_properties["CLIENT_COMPRESS"] = config.mysql_compress;
		driver = get_driver_instance();
		con = driver->connect(connection_properties);
		stmt = con->createStatement();
		res = stmt->executeQuery(query);
        ret = res->getInt("COUNT(*)");
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return -1;
	}
	return ret;
}

//Adds a UPS to the database and returns it's ID
int addups(configobj config, int index) {
    string query = "INSERT INTO devices (nut_name) VALUES (" + config.upslist[index] + ")";
    int ret;
    try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::ConnectOptionsMap connection_properties;
		sql::Statement *stmt;
		sql::ResultSet *res;
		connection_properties["hostName"] = config.mysql_host;
		connection_properties["userName"] = config.mysql_username;
		connection_properties["password"] = config.mysql_password;
		connection_properties["schema"] = config.mysql_database;
		connection_properties["CLIENT_COMPRESS"] = config.mysql_compress;
		driver = get_driver_instance();
		con = driver->connect(connection_properties);
		stmt = con->createStatement();
		res = stmt->executeQuery(query);
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return -1;
	}
    ret = getupsid(config, index);
    return ret;
}

//Returns DB ID of given UPS
int getupsid(configobj config, int index) {
    string query = "SELECT id FROM devices WHERE nut_name = " + config.upslist[index] + " LIMIT 1";
    int ret;
    try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::ConnectOptionsMap connection_properties;
		sql::Statement *stmt;
		sql::ResultSet *res;
		connection_properties["hostName"] = config.mysql_host;
		connection_properties["userName"] = config.mysql_username;
		connection_properties["password"] = config.mysql_password;
		connection_properties["schema"] = config.mysql_database;
		connection_properties["CLIENT_COMPRESS"] = config.mysql_compress;
		driver = get_driver_instance();
		con = driver->connect(connection_properties);
		stmt = con->createStatement();
		res = stmt->executeQuery(query);
        ret = res->getInt("id");
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return -1;
	}
    return ret;
}

int updateextradata(configobj config, int index, extradataobj extradata) {
    //TODO get info from UPSs
    string query = "INSERT INTO devices_extradata ("
        "devices_id,"
        "battery_charge_low,"
        "battery_charge_warning,"
        "battery_mfr_date,"
        "battery_runtime_low,"
        "battery_type,"
        "battery_voltage_nominal,"
        "device_mfr,"
        "device_model,"
        "device_serial,"
        "device_type,"
        "driver_name,"
        "driver_version,"
        "driver_version_data,"
        "driver_version_internal,"
        "input_voltage_nominal,"
        "ups_beeper_status,"
        "ups_delay_shutdown,"
        "ups_delay_start,"
        "ups_mfr,"
        "ups_model,"
        "ups_productid,"
        "ups_realpower_nominal,"
        "ups_serial,"
        "ups_test_result,"
        "ups_timer_shutdown,"
        "ups_timer_start,"
        "ups_vendorid"
        ") VALUES ("
        + to_string(config.upsidlist[index]) + ","
        + to_string(extradata.battery_charge_low) + ","
        + to_string(extradata.battery_charge_warning) + ","
        + extradata.battery_mfr_date + ","
        + to_string(extradata.battery_runtime_low) + ","
        + extradata.battery_type + ","
        + to_string(extradata.battery_voltage_nominal) + ","
        + extradata.device_mfr + ","
        + extradata.device_model + ","
        + extradata.device_serial + ","
        + extradata.device_type + ","
        + extradata.driver_name + ","
        + extradata.driver_version + ","
        + extradata.driver_version_data + ","
        + extradata.driver_version_internal + ","
        + to_string(extradata.input_voltage_nominal) + ","
        + extradata.ups_beeper_status + ","
        + to_string(extradata.ups_delay_shutdown) + ","
        + to_string(extradata.ups_delay_start) + ","
        + extradata.ups_mfr + ","
        + extradata.ups_model + ","
        + extradata.ups_productid + ","
        + to_string(extradata.ups_realpower_nominal) + ","
        + extradata.ups_serial + ","
        + extradata.ups_test_result + ","
        + to_string(extradata.ups_timer_shutdown) + ","
        + to_string(extradata.ups_timer_start) + ","
        + to_string(extradata.ups_vendorid) + ")"
        "ON DUPLICATE KEY UPDATE devices_id = devices_id"; //do nothing on duplicate keys
    try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::ConnectOptionsMap connection_properties;
		sql::Statement *stmt;
		sql::ResultSet *res;
		connection_properties["hostName"] = config.mysql_host;
		connection_properties["userName"] = config.mysql_username;
		connection_properties["password"] = config.mysql_password;
		connection_properties["schema"] = config.mysql_database;
		connection_properties["CLIENT_COMPRESS"] = config.mysql_compress;
		driver = get_driver_instance();
		con = driver->connect(connection_properties);
		stmt = con->createStatement();
		res = stmt->executeQuery(query);
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return -1;
	}
    return 0;
}
