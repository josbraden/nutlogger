#include <vector>
//Object for command line args
class argobj {
    public:
    bool verbose = false;
    bool singleloop = false;
    bool mysql_compress = false;
};

//Object for program runtime configurations
//Read from the config file or copied from args
class configobj {
    public:
    //Program stuff
    bool verbose = false;
    bool singleloop = false;
    int pollinterval = 35;
    std::string configfilename = "nutlogger.cnf";
    std::string configfile;
    //MySQL stuff
    std::string mysql_host = "127.0.0.1";
	std::string mysql_username = "upsuser";
	std::string mysql_password = "foobar";
	std::string mysql_database = "ups";
    bool mysql_compress = false;
    //Nut server stuff
    std::string nut_server = "127.0.0.1";
    int nut_port = 3493;
    //UPS stuff
    std::vector<std::string> upslist;
    std::vector<int> upsidlist;

    //Function declarations
    void setconfigfield(std::string key, std::string value);
    void upslist_sortUnique();
    void getexepath();
};

//Object to hold data for log entries
class logdataobj {
    public:
    int status = 0;
    int battery_charge;
    int battery_runtime;
    float battery_voltage;
    float input_voltage;
    float output_voltage;
    int ups_load;
    std::string ups_status;
};

//Object to hold extra data fields for a UPS device
class extradataobj {
    public:
    int status = 0;
    int battery_charge_low;
    int battery_charge_warning;
    std::string battery_mfr_date;
    int battery_runtime_low;
    std::string battery_type;
    float battery_voltage_nominal;
    std::string device_mfr;
    std::string device_model;
    std::string device_serial;
    std::string device_type;
    std::string driver_name;
    std::string driver_version;
    std::string driver_version_data;
    std::string driver_version_internal;
    float input_voltage_nominal;
    std::string ups_beeper_status;
    int ups_delay_shutdown;
    int ups_delay_start;
    std::string ups_mfr;
    std::string ups_model;
    std::string ups_productid;
    int ups_realpower_nominal;
    std::string ups_serial;
    std::string ups_test_result;
    int ups_timer_shutdown;
    int ups_timer_start;
    int ups_vendorid;
};

//Init functions
int init(argobj argdata);

//UPS functions
int testups(configobj config);
extradataobj getextradata(configobj config, int index);
logdataobj getlogdata(configobj config, int index);

//Database functions
int testmysql(configobj config);
int getupsknt(configobj config, int index);
int addups(configobj config, int index);
int getupsid(configobj config, int index);
int updateextradata(configobj config, int index, extradataobj extradata);
int addlogentry(configobj config, int index, logdataobj logdata);
int rotatelogs(configobj config);
int optimizearchive(configobj config);

//Main loop functions
int logger(configobj config);
configobj set_upsidlist(configobj config);
