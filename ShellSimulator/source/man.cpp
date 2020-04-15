#include"man.h"
#include<iostream>
man::man(string input)
    :Command(input),man_dir(shell_dir+"/files/manuals/"){
    if(check_init()){
        char back[30]="\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        int cur_my=0,cur_sys=0;
        for(int i=0;i<isMyCmd.size();i++){
            if(isMyCmd[i]){
                while(!feof(files[cur_my])){
                    printf("%s",back);
                    int line=0;
                
                    while(++line<=10 && !feof(files[cur_my])){
                        char buffer[100010];
                        if(fgets(buffer,10010,files[cur_my])<=0){
                            cout<<"---END---"<<endl;
                            break;
                        }
                        puts(buffer);
                    }
                
                    printf("type enter to continue");
                }
                cur_my++;
            }
            else{
                system((string("man ")+sys_cmd[cur_sys]).c_str());
                cur_sys++;
            }
        }
    }
    else cout<<"type \'man man\' for help"<<endl;
}

int man::check_init(){
    for(int i=0;i<option.size();i++){
        if(i||option[i]!=string("")){
            print_error((char*)"option",option[i]);
            return 0;
        }
    }
    for(int i=0;i<args[0].size();i++){
        string manual_file = man_dir+"/"+args[0][i]+".man";
        if(filetype(manual_file)!=_file_){
            if(myCommands.count(args[0][i]))
                print_error((char*)"noMan",args[0][i]);
            else{
                sys_cmd.push_back(args[0][i]);
                isMyCmd.push_back(false);
            }
        }
        else{
            files.push_back(fopen(manual_file.c_str(),"r"));
            isMyCmd.push_back(true);
        }
    }
    return files.size();
}

void man::print_error(char *error_type,string argv){
    string error=string(error_type);
    cout<<"man: ";
    argv="\'"+argv+"\'";
    if(error==string("option"))
        cout<<"invalid option -- "<<argv<<endl;
    if(error==string("noMan"))
        cout<<"No manual entry for"<<argv;
    
}

man::~man(){
    for(int i=0;i<files.size();i++)
        fclose(files[i]);
}