#include <vector>
//Object for command line args
class argobj {
    public:
    bool verbose = false;
};

//Object for program runtime configurations
//Read from the config file or copied from args
class configobj {
    public:
    //Program stuff
    bool verbose = false;
    int pollinterval = 35;
    //MySQL stuff
    std::string mysql_host = "127.0.0.1";
	std::string mysql_username = "upsuser";
	std::string mysql_password = "foobar";
	std::string mysql_database = "ups";
    bool mysql_compress = false;
    //Nut server stuff
    std::string nut_server = "127.0.0.1";
    int nut_port = 3943;
    //UPS stuff
    std::vector<std::string> upslist;
    std::vector<int> upsidlist;

    //Function declarations
    void setconfigfield(std::string key, std::string value);
    void upslist_sortUnique();
    void set_upsidlist();
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
configobj setconfigfield(configobj config, std::string key, std::string value);

//UPS functions
int testups(configobj config);
extradataobj getextradata(configobj config, int index);

//Database functions
int testmysql(configobj config);
int getupsknt(configobj config, int index);
int addups(configobj config, int index);
int getupsid(configobj config, int index);
int updateextradata(configobj config, int index, extradataobj extradata);

//Main loop functions
int logger(configobj config);
