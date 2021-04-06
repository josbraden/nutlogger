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

    //Function declarations
    void setconfigfield(std::string key, std::string value);
    void upslist_sortUnique();
};

//Init functions
int init(argobj argdata);
configobj setconfigfield(configobj config, std::string key, std::string value);

//UPS functions
int testups(configobj config);

//Database functions
int testmysql(configobj config);
int getupsknt(configobj config, int index);
int addups(configobj config, int index);

//Main loop functions
int logger(configobj config);
