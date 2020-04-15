#include"Command.h"
#include<dirent.h>
#include<iostream>

Command::Command(string input){
    int status=1;//0:option 1:argv
    option.push_back(string(""));//the first option "empty"
    
    for(int i=0;i<input.size();i++){
        string nxt_option=""; 
        vector<string> cur_args;
        
        //skip space
        while(i<input.size()&&input[i]==' ')
            ++i;
        
        //this args
        while(i<input.size()&&input[i]!='-'){
            string tmp_argv="";
            while(i<input.size()&&input[i]!=' ')
                tmp_argv+=input[i++];
            if(tmp_argv!=string(""))
                cur_args.push_back(tmp_argv);
            while(i<input.size()&&input[i]==' ')
                i++;
        }
        args.push_back(cur_args);
        //next option
        if(i<input.size()&&input[i]=='-'){
            i++;
            while(i<input.size()&&input[i]!=' ')
                nxt_option+=input[i++];
            option.push_back(nxt_option);
        }
    }
}

Command::type Command::filetype(string file){
    FILE *f;
    DIR *dir;
    //cout<<"debug:"<<file<<endl;
    if(dir=opendir(file.c_str())){
        closedir(dir);
        return _dir_;
    }
    else if(f=fopen(file.c_str(),"r")){
        fclose(f);
        return _file_;
    }
    return _null_;
}

Command::~Command(){}