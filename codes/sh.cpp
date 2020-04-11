#include"sh.h"
#include<iostream>
#include<unistd.h>

sh::sh(string input)
    :Command(input){
    //cmdManager manager;
    char original_dir[10010];
    getcwd(original_dir,10009);
    
    auto split = [](string line,string &cmd,string &argv){
        cmd.clear(),argv.clear();
        int i=0;
        while(line[i]==' ') i++;
        while(i<line.size()&&line[i]!=' ')
            cmd+=line[i++];
        while(i<line.size())
            argv+=line[i++];
        return;
    };
    
    if(check_init()){
        for(int i=0;i<files.size();i++){
            if(sizeof(wdir[i]))
                cd tmp(wdir[i]);
            
            char buffer[10010];
            while(!fgets(buffer,10009,files[i])){ 
                string line(buffer,0,sizeof(buffer)-1);
                string cmd,args;
                split(line,cmd,args);
                if(myCommands.count(cmd))
                    manager.run(cmd,args);
                else system(line.c_str());
            }
            
            cd back(original_dir);
        }
    }
    else 
        cout<<"type \'man sh\' for help"<<endl;

}

int sh::check_init(){
    for(int i=0;i<option.size();i++){
        if(option[i]!=string("")||i>0){
            print_error((char*)"option",option[i]);
            return 0;
        }
    }
    for(int i=0;i<args[0].size();i++){
        if(filetype(args[0][i])==_file_){
            files.push_back(fopen(args[0][i].c_str(),"r"));
            string tmp_dir=args[0][i];
            for(int j=tmp_dir.size();j>=0;j--)
                if(i=='\\'||i=='/'||!i){
                    tmp_dir = tmp_dir.substr(0,i);
                    break;
                }
            wdir.push_back(tmp_dir);
        }
        else{
            print_error((char*)"noFile",args[0][i]);
            return 0;
        }
    }
} 

void sh::print_error(char *error_type,string argv){
    string error = string(error_type);
    argv = "\'"+argv+"\'";

    cout<<"sh: ";

    if(error==string("option"))
        cout<<"Invalid option -- "<<argv<<endl;
    if(error==string("noFile"))
        cout<<"Can\'t open "<<argv<<endl;
}

sh::~sh(){
    for(int i=0;i<files.size();i++)
        fclose(files[i]);
}