#pragma once
#include"Command.h"
class cmdManager{
public:
    //cmdManager();
    void run(string cmd,string args);
    int prepared(string &cmd) const;
};
