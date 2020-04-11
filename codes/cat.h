#pragma once
#include"Command.h"

using namespace std;

class cat:public Command{
public:
    cat(string input);
    ~cat();
    //return num of file
    int check_init();
    void print_error(char *error_type,string args);
private:
    vector<FILE*> files;
};