#pragma once
#include"Command.h"
#include<cstdio>

class cmp:public Command{
public:
    cmp(string input);
    ~cmp();
    int check_init();
    void compare();
private:
    string File1,File2;
    FILE *fptr1,*fptr2;
    void print_error(char* error_type,string args);
};