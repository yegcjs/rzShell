#include"cmp.h"
#include<iostream>
cmp::cmp(string input)
    :Command(input),fptr1(NULL),fptr2(NULL){
    if(!check_init())//including open file
        compare();
    else
        cout<<"type \'man cmp\' for help"<<endl;
}

int cmp::check_init(){
    if(option[0]!=string("")){
        print_error((char*)"option",option[0]);
        return -1;
    }

    if(option.size()>1){
        print_error((char*)"option",option[1]);
        return -1;
    }
    
    if(args[0].size()>2){
        print_error((char*)"argv",args[0][2]);
        return -1;
    }

    if(args[0].size()<1){
        return -1;
    }

    auto checkFile = [this](string file_name,FILE *&file){
        file = fopen(file_name.c_str(),(char*)"rb");
        if(!file){
            if(filetype(file_name)==_dir_)
                print_error((char*)"isDirectory",file_name);
            else print_error((char*)"notExist",file_name);
            return -1;
        }
        return 0;
    };
    
    File1=args[0][0];File2=args[0][1];

    if(checkFile(File1,fptr1)) return -1;
    if(checkFile(File2,fptr2)) return -1;

    return 0;
}

void cmp::print_error(char* error_type,string argv){
    const string error=string(error_type);
    cout<<"cmp: ";
    if(error==string("option"))
        cout<<"invalid option -- "<<argv<<endl;
    else if(error==string("argv"))
        cout<<"invalid --ignore-initial value "<<"\'"+argv+"\'"<<endl;    
    else if(error==string("isDirectory"))
        cout<<argv<<": Is a directory"<<endl;
    else if(error==string("notExist"))
        cout<<argv<<": No such file or directory"<<endl;

    return;
}

void cmp::compare(){
    int cnt_byte=0,cnt_line=1;
    while(!feof(fptr1) && !feof(fptr2)){
        char c1=fgetc(fptr1),c2=fgetc(fptr2);
        ++cnt_byte;
        if(c1!=c2){
            cout<<File1<<" "<<File2<<" differ: byte "<<cnt_byte<<", line "<<cnt_line<<endl;
            return;
        }
        else{//c1==c2
            if(c1=='\n') ++cnt_line;
            if(c1==EOF) return;
        }
    }
}

cmp::~cmp(){
    if(fptr1) fclose(fptr1);
    if(fptr2) fclose(fptr2);
}