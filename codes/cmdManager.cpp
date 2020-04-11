#include"cmdManager.h"
#include"cmp.h"
#include"cp.h"
#include"cd.h"
#include"cat.h"
#include"wc.h"
#include"sh.h"
#include"man.h"


int cmdManager::prepared(string &cmd) const{
    string hFile=cmd+".h",cppFile=cmd+".cpp";
    FILE *ptrh=fopen(hFile.c_str(),"r"),*ptrcpp=fopen(cppFile.c_str(),"r");
    
    int flag=1;
    if(!ptrh) flag=0;
    else fclose(ptrh);
    
    if(!ptrcpp) flag=0;
    else fclose(ptrcpp);

    return flag;
}

void cmdManager::run(string cmd,string argv){
    
    if(cmd==string("cmp"))
        cmp tmp(argv);
    if(cmd==string("cp"))
        cp tmp(argv);
    if(cmd==string("cd"))
        cd tmp(argv);
    if(cmd==string("cat"))
        cat tmp(argv);
    if(cmd==string("wc"))
        wc tmp(argv);
    if(cmd==string("sh"))
        sh tmp(argv);
    if(cmd==string("man"))
        man tmp(argv);
    else return;
}