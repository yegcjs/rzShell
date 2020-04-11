#pragma once
#include"Command.h"

class cd:public Command{
private:
    string new_dir;
public:
    cd(string input);
    int check_init();
    void print_error(char *error_type,string args);
    ~cd();
};