#include"demo.h"
#include<iostream>
demo::demo(string input)
  :Command(input){
  if(check_init())
    for(int i=0;i<args[0].size();i++)
      cout<<args[0][i]<<endl;
  else 
    cout<<"Please type man demo for help"<<endl;
}

demo::~demo(){
  cout<<"This is the destructor of demo!"<<endl;
}

int demo::check_init(){
  cout<<"this is check_init()"<<endl;
  cout<<"suppose that you have enter a wrong argument."<<endl;
  cout<<"demo: let's call print_error"<<endl;
  print_error((char*)"option",option[0]);
}

void demo::print_error(char *error_type,string argv){
  string error = string(error_type);
  cout<<"demo: this is print_error()"<<endl;
  cout<<"demo: error of  "<<error<<". It happens because"<<argv<<endl;
}
