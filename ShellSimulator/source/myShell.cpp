#include"myShell.h"
#include<iostream>
#include<cctype>
#include<cstring>
#include<cstdio>
#include<unistd.h>
#include<pwd.h>
#include"Command.h"


void init(){
    char buffer[10010];

    getcwd(buffer,10009);
    shell_dir=string(buffer);
    gethostname(buffer,10010);
    host=string(buffer);
    username=(getpwuid(getuid())->pw_name);

    
    FILE *cmds=fopen("files/config.txt","r");
    if(!cmds) return;
    while(!feof(cmds)){
        char cmd[10000];
        if(fscanf(cmds,"%[^\n]\n",cmd)>=0);
            myCommands.insert(string(cmd));
    }
 //   freopen("/dev/tty",)
    fclose(cmds);

    FILE *log=fopen("files/log.txt","r");
    if(log){
        char dir[10010];
        
        if(fgets(dir,10009,log)>0)
            manager.run(string("cd"),string(dir));
        fclose(log);
    }
}

void split(string line,string &cmd,string &argv){
    cmd.clear(),argv.clear();
    
    int i=0;
    while(line[i]==' ') i++;
    while(i<line.size()&&line[i]!=' ')
        cmd+=line[i++];
    while(i<line.size())
        argv+=line[i++];
    
    return;
}

/*
int add(string argv){
    FILE *cmds=fopen((shell_dir+string("/files/config.txt")).c_str(),"a");
    if(!cmds){
        cout<<"add: "<<"cannot open file \'config.txt\'"<<endl;
        return 0;
    }
    
    auto checkCommand=[](string cmd){
        for(int j=0;j<cmd.size();j++)
            if(!(islower(cmd[j])||isupper(cmd[j])))
                return -1;
        return 0;
    };
    
    int cnt=0;//successfully added   
    for(int i=0;i<argv.size();i++){
        string cmd="";
        while(i<argv.size()&&argv[i]==' ') i++;
        while(i<argv.size()&&argv[i]!=' ')
            cmd+=argv[i++]; 
        if(cmd==string("")) continue;
        if(checkCommand(cmd)) 
             cout<<"add: "<<"invalid command name "<<"\'"+cmd+"\'"<<endl;
        else if(myCommands.count(cmd))
            cout<<"add: "<<"Command "<<"\'"+cmd+"\'"<<" has been added before."<<endl;
        else if(!manager.prepared(cmd))
            cout<<"add: "<<"Command "<<"\'"+cmd+"\'"<<" has not prepared."<<endl;
        else{
            fprintf(cmds,"%s\n",cmd.c_str());
            myCommands.insert(cmd);
            cnt++;
        }
    }

    cout<<"add: "<<cnt<<" succeed "<<endl;   
    fclose(cmds);
    return cnt;
}
*/

void exec(){
    while(!feof(stdin)){ 
        char cwd[10010];
        getcwd(cwd,10009);
        cout<<username+"@"+host+":"<<cwd<<"$ ";
        string line;char buffer[10010];
        if(fgets(buffer,10009,stdin)<=0)
            return;
        
        line=string(buffer,0,strlen(buffer)-1);
        //getline(cin,line);

        string cmd,args;
        split(line,cmd,args);
        if(myCommands.count(cmd))
            manager.run(cmd,args);
        else system(line.c_str());
    }
}


int main(){
    init();
    cout<<"Welcome to myShell"<<endl;
    exec();
    FILE *log=fopen((shell_dir+string("/files/log.txt")).c_str(),"w");
    if(log) fclose(log);
    return 0;
}