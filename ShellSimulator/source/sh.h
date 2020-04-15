#pragma once
#include"Command.h"
#include"cd.h"
#include"cmdManager.h"
#include<set>
class sh:public Command{
private:
    vector<FILE*> files;
    vector<string> wdir;
public:
    sh(string input);
    int check_init();
    void print_error(char *error_type,string argv);
    ~sh();
};

extern set<string> myCommands;
extern cmdManager manager;