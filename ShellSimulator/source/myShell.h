#ifndef MYSHELL
#define MYSHELL

//entrance of the shell
#include<set>
#include<string>
#include"cmdManager.h"
using namespace std;

//the cmds which are available for user
set<string> myCommands;

cmdManager manager;
string shell_dir,host,username;
//input all the cmds available from file
void init();

//exec
void exec();

//execute cmd
//void call(string cmd,string argv);

//add available command,return number of successfully added cmds
//int add(string argv);

//
//int sh(string argv);

void split(string line,string &cmd);

#endif