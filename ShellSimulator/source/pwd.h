#pragma once
#include"Command.h"
using namespace std;

class pwd:public Command{
public:
    pwd(string input);
    int check_init();
    void print_error(char *error_type,string args);
    ~pwd();
};