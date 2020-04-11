#include"cat.h"
#include<iostream>

cat::cat(string input)
    :Command(input){
    if(!check_init()){
        cout<<"type man \'cat\' for help"<<endl;
        return ;
    }
    for(int i=0;i<files.size();i++){
        while(!feof(files[i])){
            char c;
            if(fscanf(files[i],"%c",&c)<=0)
                break;
            putchar(c);
        }
    }
}

cat::~cat(){
    for(int i=0;i<files.size();i++)
        fclose(files[i]);
}

int cat::check_init(){
    if(option[0]!=string("")){
        print_error((char*)"option",option[0]);
        return 0;
    }
    if(option.size()>1){
        print_error((char*)"option",option[1]);
        return 0;
    }
    for(int i=0;i<args[0].size();i++){
        
        switch(filetype(args[0][i])){
        case _file_:{
            files.push_back(fopen(args[0][1].c_str(),"r"));
            break;
        }
        case _dir_:{
            print_error((char*)"isDir",args[0][i]);
            break;
        }
        case _null_:{
            print_error((char*)"notExist",args[0][i]);
            break;
        }
        }
    }
    return files.size();
}

void cat::print_error(char *error_type,string args){
    string error = string(error_type);
    args = "\'"+args+"\'";
    cout<<"cat: ";

    if(error==string("option"))
        cout<<" invalid option -- "<<args<<endl;
    else if(error==string("isDir"))
        cout<<args<<" is a directory"<<endl;
    else if(error==string("notExist"))
        cout<<args<<" is not a file or directory."<<endl;

}