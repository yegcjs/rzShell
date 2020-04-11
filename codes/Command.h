#pragma once
#include<vector>
#include<string>
using namespace std;
class Command{
protected:
    //<[option(s)],[args]>
    vector<string>option;
    vector<vector<string>> args;
    
    enum type{_file_,_dir_,_null_};
    type filetype(string file);
public:
    Command(string input);
    virtual ~Command();
    //if pass:return 0, else return non-0
    virtual int check_init()=0;
    virtual void print_error(char* error_type,string args)=0;
};