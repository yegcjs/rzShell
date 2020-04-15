#include"pwd.h"
#include<iostream>
#include<unistd.h>
pwd::pwd(string input)
    :Command(input){
    if(check_init()){
        char cur_dir[10010];
        getcwd(cur_dir,10000);
        cout<<cur_dir<<endl;
    }
}

int pwd::check_init(){
    if(option[0]!=string("")){
        print_error((char*)"option",option[0]);
        return 0;
    }
    if(option.size()>1){
        print_error((char*)"option",option[1]);
        return 0;
    }
    return 1;
}

void pwd::print_error(char *error_type,string args){
    string error=string(error_type);
    args="\'"+args+"\'";
    cout<<"pwd: ";

    if(error==string("option"))
        cout<<"invalid option --"<<args;
}
 
pwd::~pwd(){}