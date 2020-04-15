#pragma once
#include"Command.h"
#include<string>
class cp:public Command{
public:
    cp();
    cp(string &input);
    //-1:error, 1:file->file, 2:files->dir
    int check_init();
    void open_dir(string path,string rel_path);
    ~cp();
private:
    string target;
    vector<string>  rel_file_list,file_list;
    vector<string> dir_list;
    void print_error(char *error_type,string args);
    string split(const string &dir);
};