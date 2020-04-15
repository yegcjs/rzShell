#include"cp.h"
#include<iostream>
#include<sys/stat.h>
#include<dirent.h>

using namespace std;

cp::cp(string &input)
    :Command(input){
    int status=check_init();

    auto copy=[](string old_file,string new_file){
        FILE *in = fopen(old_file.c_str(),"rb");
        FILE *out = fopen(new_file.c_str(),"wb");
        if(!in || !out) return;
        while(!feof(in)){
            char byte;
            if(fread(&byte,sizeof(char),1,in)>=0)
                fwrite(&byte,sizeof(char),1,out);
            else break;
        }
        fclose(in);
        fclose(out);
    };

    if(status==1){
        copy(file_list[0],target);
    }
    else if(status==2){
        for(int i=0;i<dir_list.size();i++)
            mkdir((target+"/"+dir_list[i]).c_str(),S_IRWXG);
        for(int i=0;i<file_list.size();i++)
            copy(file_list[i],target+"/"+rel_file_list[i]);
    }
    else
        cout<<"cp: try \'man cp\' for help"<<endl;
}

cp::~cp(){}

int cp::check_init(){

    //get copy Target
    int last = args.size()-1;
    while(!args[last].size()&&last>=0)
        last--;
    if(last<0){
        print_error((char*)"noOperand",string(""));
        return -1;
    }
    else {
        target = args[last][args[last].size()-1];
        if(last==0 && args[last].size()==1){
            print_error((char*)"noTarget",target);
            return -1;
        }
        args[last][args[last].size()-1]=string("");
    }

    //check: match option and args
    for(int i=0;i<option.size();i++){
        if(option[i]!=string("r")){
            if(i!=0 || option[i]!=string("")){
                print_error((char *)"option",option[i]);
                return -1;
            }
        }

        for(int j=0;j<args[i].size();j++){
            string cur = args[i][j];
            if(cur==string(""))//original target
                break;
            if(cur==target)
                print_error((char*)"same",cur);
            else switch(filetype(cur)){
            case _dir_:{
                if(option[i]==string("r"))
                    open_dir(cur,split(cur));
                else{
                    print_error((char*)"-rNotSpecified",cur);
                    return -1;
                }
                break;
            }
            case _null_:{
                print_error((char*)"notExist",cur);
                return -1;
            }
            case _file_:{
                file_list.push_back(cur);
                rel_file_list.push_back(split(cur));
                break;
            }
            }
        }
    }    

    switch (filetype(target))
    {
    case _file_:{
        //cout<<"debug:"<<target<<endl;
        if(dir_list.size()||file_list.size()>1){//not only 1 file
            print_error((char*)"notDir",target);
            return -1;
        }
        else return 1;
    }
    case _dir_:{
        return 2;
    }
    case _null_:{
        if(dir_list.size()||file_list.size()>1){
            mkdir(target.c_str(),S_IRWXU|S_IRWXG);
            return 2;
        }
        return 1;
    }
    }

}

void cp::open_dir(string path,string rel_path){
    DIR *cur_dir =  opendir(path.c_str());
    if(!cur_dir)
        return;
    //cout<<"debug:"<<path<<","<<rel_path<<endl;
    dir_list.push_back(rel_path);
    dirent *item;
    while(item=readdir(cur_dir)){
        string cur_file = string(item->d_name);
        if(cur_file==string(".")||cur_file==string(".."))
            continue;
        string nxt_dir = path+string("/")+cur_file;
        if(filetype(nxt_dir)==_dir_)
            open_dir(nxt_dir,rel_path+string("/")+cur_file);
        else{
            file_list.push_back(nxt_dir);
            rel_file_list.push_back(rel_path+string("/")+cur_file);
        }
    }
    closedir(cur_dir);
}

string cp::split(const string &dir){
    int p=1,len=dir.size();
    while(dir[len-1]=='\\'||dir[len-1]=='/')
        p++;
    while(len-p>=0){
        if(dir[len-p]=='\\'||dir[len-p]=='/')
            break;
        p++;
    }
            
    string newDir;
    while(--p){
        if(dir[len-p]=='\\'||dir[len-p]=='/')
            break;
        newDir+=dir[len-p];
    }

    return newDir;
};

void cp::print_error(char *error_type,string args){
    string error=string(error_type);
    args = "\'"+args+"\'";
    cout<<"cp: ";
    if(error==string("noOperand"))
        cout<<"missing file operand."<<endl;
    else if(error==string("noTarget"))
        cout<<"missing destination file operand after "<<args<<endl;
    else if(error==string("option"))
        cout<<"invalid option -- "<<args<<endl;
    else if(error==string("notExist"))
        cout<<"cannot stat "<<args<<": No such file or directory."<<endl;
    else if(error==string("option"))
        cout<<args<<" and "<<args<<"are the same."<<endl;
    else if(error==string("-rNotSpecified"))
        cout<<"-r not specified; ommiting directory "<<args<<endl;
    else if(error==string("notDir"))
        cout<<"target "<<args<<" is not a directory."<<endl;


    return;
}
