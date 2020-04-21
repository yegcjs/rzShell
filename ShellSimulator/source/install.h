#pragma once
#include"Command.h"
#include<set>
class install:public Command{
private:
    set<string> newCommands,abanCommands;
    FILE *config,*makefile,*managercpp;
    //successfully 1 else 0
    int update_config();
    int update_makefile();
    int update_manager();
public:
    install(string input);
    ~install();
    //number of OK
    int check_init();
    void print_error(char *error_type,string argv);
};

extern set<string> myCommands;
extern string shell_dir;