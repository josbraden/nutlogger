//Object for command line args
class argobj {
    public:
    bool verbose = false;
};

//Object for program runtime configurations
//Read from the config file or copied from args
class configobj {
    public:
    bool verbose = false;
    int pollinterval = 5;
    std::string mysql_host = "127.0.0.1";
	std::string mysql_username = "upsuser";
	std::string mysql_password = "foobar";
	std::string mysql_database = "ups";
	bool mysql_compress = false;
};

int init(argobj argdata);
