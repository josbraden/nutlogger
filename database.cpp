/*
For database related functionality
*/
#include <iostream>
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
