#include"install.h"
#include<iostream>
#include"cd.h"
#include<unistd.h>
using namespace std;
install::install(string input)
    :Command(input){
    //cout<<"hello"<<endl;
    if(!check_init())
        cout<<"type \'man install\' for help"<<endl;
    else{
        if(!update_config()) return;
        //cout<<"update config"<<endl;
        if(!update_makefile()) return;
        //cout<<"update_makefile"<<endl;
        if(!update_manager()) return;
        //cout<<"update_manager"<<endl;
        
        char current_dir[10010];
        getcwd(current_dir,10009);
        cd go(string(shell_dir));
        system("make");
        cd back(string(current_dir));        

        FILE *log =fopen((shell_dir+string("/files/log.txt")).c_str(),"w");
        fprintf(log,"%s",current_dir);
        cout<<"install "<<newCommands.size()<<" commands successfully."<<endl;
        cout<<"uninstall "<<abanCommands.size()<<" commands sucessfully."<<endl;
        fclose(log);
        //if(config) fclose(config);
        //if(makefile) fclose(makefile);
        //if(managercpp) fclose(managercpp);

        exit(1);
    }
}

int install::check_init(){
    /*
    for(int i=0;i<option.size();i++){
        if(i || option[i]!=string("")){
            print_error((char*)"option",option[i]);
            return -1;
        }
    }*/
    for(int i=0;i<option.size();i++){
        if(option[i]!=string("")&&option[i]!=string("d")){
            print_error((char*)"option",option[i]);
            return 0;
        }
        bool flag = option[i]==string("d")?true:false;
        for(int j=0;j<args[i].size();j++){
            if(myCommands.count(args[i][j])){
                if(flag){
                    string h_dir = shell_dir+"/source/"+args[i][j]+".h";
                    string cpp_dir = shell_dir+"/source/"+args[i][j]+".cpp";
                    string bin_dir = shell_dir+"/bin/"+args[i][j]+".o";
                    if((filetype(h_dir)==_file_ && filetype(cpp_dir)==_file_)
                        ||filetype(bin_dir)==_file_){
                        abanCommands.insert(args[i][j]);
                    }
                }
                else print_error((char*)"existing",args[i][j]);
            }  
            else{
                if(!flag){
                    string h_dir = shell_dir+"/source/"+args[i][j]+".h";
                    string cpp_dir = shell_dir+"/source/"+args[i][j]+".cpp";
                    string bin_dir = shell_dir+"/bin/"+args[i][j]+".o";
                    if((filetype(h_dir)==_file_ && filetype(cpp_dir)==_file_)
                            ||filetype(bin_dir)==_file_){
                        newCommands.insert(args[i][j]);
                    }
                }
                else print_error((char*)"notExist",args[i][j]);
            }
        }
    }
    //cout<<"check_int"<<endl;
    if(!(newCommands.size()+abanCommands.size())) return 0;
    config = fopen((shell_dir+"/files/config.txt").c_str(),"w");
    if(!config){print_error((char*)"nofile",string("config.txt"));return 0;}
    makefile = fopen((shell_dir+"/makefile").c_str(),"w");
    if(!makefile){print_error((char*)"nofile",string("makefile"));return 0;}
    managercpp = fopen((shell_dir+"/source/cmdManager.cpp").c_str(),"w"); 
    if(!managercpp){print_error((char*)"nofile",string("cmdManager.cpp"));return 0;}


    return newCommands.size()+abanCommands.size();
}

void install::print_error(char *error_type,string argv){
    string error = string(error_type);
    argv = "\'"+argv+"\'";
    cout<<"install: ";

    if(error==string("option"))
        cout<<"invalid option -- "<<argv<<endl;
    if(error==string("existing"))
        cout<<"command "<<argv<<"is already existing in your shell."<<endl;
    if(error==string("nofile"))
        cout<<"cannot open file "<<argv<<endl;
    if(error==string("notExist"))        
        cout<<"command "<<argv<<"does not exist in your shell."<<endl;


}

int install::update_config(){
    for(set<string>::iterator it=myCommands.begin();it!=myCommands.end();it++)
        if(!abanCommands.count(*it))
            fprintf(config,"%s\n",it->c_str());
    
    for(set<string>::iterator it=newCommands.begin();it!=newCommands.end();it++)
        fprintf(config,"%s\n",it->c_str());

    fclose(config);
    return 1;
}

int install::update_makefile(){
    //default
    //fprintf(makefile,"default:myShell\n");
    //fprintf(makefile,"\t./myShell\n");
    
    //debug
    //fprintf(makefile,"debug:myShell\n");
    //fprintf(makefile,"\tgdb myShell\n");
    
    //myShell
    fprintf(makefile,"myShell:bin/myShell.o bin/Command.o bin/cmdManager.o ");
    for(set<string>::iterator it=myCommands.begin();it!=myCommands.end();it++)
        fprintf(makefile,"bin/%s.o ",it->c_str());   
    for(set<string>::iterator it=newCommands.begin();it!=newCommands.end();it++)
        fprintf(makefile,"bin/%s.o ",it->c_str());
    fprintf(makefile,"\n\tg++ -g bin/myShell.o bin/Command.o bin/cmdManager.o ");
    for(set<string>::iterator it=myCommands.begin();it!=myCommands.end();it++)
        fprintf(makefile,"bin/%s.o ",it->c_str());   
    for(set<string>::iterator it=newCommands.begin();it!=newCommands.end();it++)
        fprintf(makefile,"bin/%s.o ",it->c_str());
    fprintf(makefile," -o myShell\n");
    //fputc('\n',makefile);
    
    //myShell.o
    fprintf(makefile,"bin/myShell.o:source/myShell.cpp source/myShell.h\n");
    fprintf(makefile,"\tg++ -g -c source/myShell.cpp -o bin/myShell.o\n");
    //cmdManager.o
    fprintf(makefile,"bin/cmdManager.o:source/cmdManager.cpp source/cmdManager.h\n");
    fprintf(makefile,"\tg++ -g -c source/cmdManager.cpp -o bin/cmdManager.o\n");
    //Command.o
    fprintf(makefile,"bin/Command.o:source/Command.cpp source/Command.h\n");
    fprintf(makefile,"\tg++ -g -c source/Command.cpp -o bin/Command.o\n");
    
    //mycommands.o
    for(set<string>::iterator it=myCommands.begin();it!=myCommands.end();it++){
        if(abanCommands.count(*it)) continue;
        fprintf(makefile,"bin/%s.o:source/%s.cpp source/%s.h\n",it->c_str(),it->c_str(),it->c_str());
        fprintf(makefile,"\tg++ -g -c source/%s.cpp -o bin/%s.o\n",it->c_str(),it->c_str());
    }
    for(set<string>::iterator it=newCommands.begin();it!=newCommands.end();it++){
        fprintf(makefile,"bin/%s.o:source/%s.cpp source/%s.h\n",it->c_str(),it->c_str(),it->c_str());
        fprintf(makefile,"\tg++ -g -c source/%s.cpp -o bin/%s.o\n",it->c_str(),it->c_str());  
    }

    //clean
    fprintf(makefile,"clean:\n");
    fprintf(makefile,"\trm bin/*.o\n\trm myShell");    
    
    fclose(makefile);
    return 1;
}

int install::update_manager(){
    //include
    fprintf(managercpp,"#include\"cmdManager.h\"\n");
    for(set<string>::iterator it=myCommands.begin();it!=myCommands.end();it++)
        fprintf(managercpp,"#include\"%s.h\"\n",it->c_str());
    for(set<string>::iterator it=newCommands.begin();it!=newCommands.end();it++)
        fprintf(managercpp,"#include\"%s.h\"\n",it->c_str());
    
    //run
    fprintf(managercpp,"void cmdManager::run(string cmd,string argv){\n");
    for(set<string>::iterator it=myCommands.begin();it!=myCommands.end();it++){
        if(abanCommands.count(*it)) continue;
        fprintf(managercpp,"\tif(cmd==string(\"%s\"))\n",it->c_str());
        fprintf(managercpp,"\t\t%s tmp(argv);\n",it->c_str());
    }
    for(set<string>::iterator it=newCommands.begin();it!=newCommands.end();it++){
        fprintf(managercpp,"\tif(cmd==string(\"%s\"))\n",it->c_str());
        fprintf(managercpp,"\t\t%s tmp(argv);\n",it->c_str());
    }
        fprintf(managercpp,"return;\n}\n");

    //prepare
    fprintf(managercpp,"int cmdManager::prepared(string &cmd) const{\n");
    fprintf(managercpp,"\tstring hFile=cmd+\".h\",cppFile=cmd+\".cpp\";\n");
    fprintf(managercpp,"\tFILE *ptrh=fopen(hFile.c_str(),\"r\"),*ptrcpp=fopen(cppFile.c_str(),\"r\");\n");
    fprintf(managercpp,"\tint flag=1;\n");
    fprintf(managercpp,"\tif(!ptrh) flag=0;\n");
    fprintf(managercpp,"\telse fclose(ptrh);\n");
    fprintf(managercpp,"\tif(!ptrcpp) flag=0;\n");
    fprintf(managercpp,"\telse fclose(ptrcpp);\n");
    fprintf(managercpp,"\treturn flag;\n}\n");
    
    fclose(managercpp);
    return 1;
}

install::~install(){}