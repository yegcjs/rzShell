#include"cd.h"
#include<unistd.h>
#include<iostream>
#include<pwd.h>
cd::cd(string input)
    :Command(input){
    if(check_init()){
        chdir(new_dir.c_str());
    }
    else cout<<"type \'man cd\' for help"<<endl;
}

int cd::check_init(){
    for(int i=0;i<option.size();i++){
        if(i||option[i]!=string("")){
            print_error((char *)"option",option[i]);
            return 0;
        }
    }
    if(args[0].size()>1){
        print_error((char*)"args",string(""));
        return 0;
    }
    new_dir=args[0][0];

    int i=0;
    while(i<new_dir.size()&&new_dir[i]==' ') i++;
    if(i<new_dir.size()&&new_dir[i]=='~'){
        passwd *pwd=getpwuid(getuid());
        string suffix = (i+1)<new_dir.size()?new_dir.substr(i+1,new_dir.size()-i-1):"";
        new_dir="/home/"+string(pwd->pw_name)+suffix;
        //cout<<"debug:"<<new_dir<<"(debug)"<<endl;
    }

    switch (filetype(new_dir))
    {
    case _null_:{
        print_error((char*)"notExist",new_dir);
        break;
    }
    case _file_:
        print_error((char*)"notDir",new_dir);
        break;
    }

    return 1;
}

void cd::print_error(char *error_type,string args){
    string error=string(error_type);
    args="\'"+args+"\'";
    cout<<"cd: ";

    if(error==string("option"))
        cout<<"invalid option --"<<args;
    if(error==string("args"))
        cout<<"too many arguments";
    if(error==string("notExist"))
        cout<<args<<": No such file or directory."<<endl;
    if(error==string("notDir"))
        cout<<args<<": Not a directory"<<endl;
}

cd::~cd(){}