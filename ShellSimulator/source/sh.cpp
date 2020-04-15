#include"sh.h"
#include<iostream>
#include<unistd.h>
#include<cstring>
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
            if(wdir[i].size())
                cd tmp(wdir[i]);
            
            char buffer[10010];
        
            while(fgets(buffer,10009,files[i])>0){
                for(int i=strlen(buffer)-1;i>=0;i--)
                    if(buffer[i]=='\n' || buffer[i]==' ' || buffer[i]=='\t')
                        buffer[i]='\0';
                    else break;
                //printf("%sp",buffer);
                string line(buffer);
                cout<<line<<endl;
                //printf("%s>",buffer);
                //cout<<line<<"p"<<endl;
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
                if(tmp_dir[j]=='\\'||tmp_dir[j]=='/'||!j){
                    bool flag=0;
                    while((tmp_dir[j]=='\\'||tmp_dir[j]=='/')&&j){
                        j--;
                        flag=true;
                    }
                    if(flag) j++;
                    tmp_dir = tmp_dir.substr(0,j);
                    break;
                }
            
            wdir.push_back(tmp_dir);
        }
        else{
            print_error((char*)"noFile",args[0][i]);
            return 0;
        }
    }
    return files.size();
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