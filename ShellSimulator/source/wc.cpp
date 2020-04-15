#include"wc.h"
#include<iostream>
wc::wc(string input)
    :Command(input){
    tot_w=tot_c=tot_l=0;
    if(!check_init()){
        cout<<"type \'man wc\' for help"<<endl;
        return;
    }
    
    auto isSplit = [](char c){
        if(c==' ') return true;
        if(c=='\t') return true;
        if(c=='\n') return true;
        if(c=='\0') return true;
        return false;
    };

    
    for(int i=0;i<files.size();i++){
        //FILE *file = fopen(files[i].c_str(),"rb");
        FILE *file=files[i];
        bool pre_is_split=true;
        int cur_w=0,cur_l=0,cur_c=0;
        while(!feof(file)){
            char cur;
            if(fread(&cur,sizeof(char),1,file)<=0)
                break;
            cur_c++;
            if(l&&cur=='\n') cur_l++;
            bool cur_is_split = isSplit(cur);
            if(w&&(!cur_is_split)&&(pre_is_split))
                cur_w++;
            pre_is_split=cur_is_split;
        }
        //fclose(file);
        tot_w+=cur_w; tot_l+=cur_l;  tot_c+=cur_c;
        if(l)printf("%5d",cur_l);
        if(w)printf("%6d",cur_w);
        if(c)printf("%7d",cur_c);
        cout<<"  "<<files[i]<<endl;
    }

    if(files.size()>1){
        if(l)printf("%5d",tot_l);
        if(w)printf("%6d",tot_w);
        if(c)printf("%7d",tot_c);
        cout<<"  "<<"total"<<endl;       
    }
}

wc::~wc(){
    for(int i=0;i<files.size();i++)
        fclose(files[i]);
}

int wc::check_init(){
    for(int i=0;i<option.size();i++){
        for(int j=0;j<option[i].length();j++){
            if(option[i][j]=='w') w=true;
            else if(option[i][j]=='c') c=true;
            else if(option[i][j]=='l') l=true;
            else{
                print_error((char*)"option",option[i]);
                return 0;
            }
        }
    }
    
    for(int i=0;i<args.size();i++)
        for(int j=0;j<args[i].size();j++){
            switch (filetype(args[i][j]))
            {
            case _file_:{
                files.push_back(fopen(args[i][j].c_str(),"r"));
                break;
            }
            case _dir_:{
                print_error((char*)"isDir",args[i][j]);
                break;
            }
            case _null_:{
                print_error((char*)"notExist",args[i][j]);
                break;
            }
            default:
                break;
            }
        }
    
    if(!w && !c && !l) w=c=l=true;
    
    return files.size();
}

void wc::print_error(char *error_type,string args){
    string error=string(error_type);
    cout<<"wc: ";

    if(error==string("option"))
        cout<<" invalid option -- "<<args<<endl;
    else if(error==string("isDir"))
        cout<<args<<" is a directory"<<endl;
    else if(error==string("notExist"))
        cout<<args<<" is not a file or directory."<<endl;


}