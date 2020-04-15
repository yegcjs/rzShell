#pragma once
#include"Command.h"

using namespace std;

class wc:public Command{
public:
    wc(string input);
    ~wc();
    //return number of files to count
    int check_init();
    void print_error(char *error_type,string args);
private:
    int tot_w,tot_c,tot_l;
    bool w,c,l;
    vector<FILE*> files;
};