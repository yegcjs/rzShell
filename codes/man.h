#pragma once
#include"Command.h"

class man:public Command{
private:
    string man_dir;
    vector<FILE*> files;
public:
    man(string input);
    ~man();
    //return the number of files to be opened
    int check_init();
    void print_error(char *error_type,string argv);
};

extern string shell_dir;