# Shell Simulator User Guide



<!-- TOC -->

* [Shell Simulator](#ShellSimulator)
  * [效果展示](#效果展示)
  * [基本命令](#基本命令)
    * [cd](#cd)
    * [cmp](#cmp)
    * [cat](#cat)
    * [wc](#wc)
    * [cp](#cp)
    * [man](#man)
  * [sh](#sh)
  * [install命令与命令开发](#install命令与命令开发)
    * [install命令的实现](#install命令的实现)
      * [Shell Simulator的模块结构](#ShellSimulator的模块结构)
      * [Shell Simulator目录下的文件](#ShellSimulator目录下的文件)
  		* [install命令执行流程](#install命令执行流程)
		* [编写命令涉及的API](#编写命令涉及的API)
		* [一个例子: demo](#一个例子:demo)
* [其他未定义命令](#其他未定义命令)
  
  

<!-- TOC -->

## 效果展示

![DeepinScreenshot_dde-desktop_20200422010602](https://github.com/yegcjs/simu-Shell/raw/master/pic/DeepinScreenshot_dde-desktop_20200422010602.png)

## 基本命令

### cd

改变当前工作目录，支持相对路径、绝对路径，支持`~`开头替代`/home/username`

* 命令格式

  > cd /path/to/directory/

### cmp

逐个字节比较两个文件，并输出第一不同字节所在的位置和行数

* 命令格式

  >cmp file1 file2

### cat

链接文件并输出连接后文件内容

* 命令格式

>cat files

### wc

统计文件，并输出统计内容（默认输出行数、字节数、单词数）

结果与参数给出顺序无关

* 命令格式

> wc [option]... file[s]

* 参数
  * -l: 行数
  * -c: 字节数
  * -w: 单词数

### cp

复制文件（夹）

* 命令格式

> cp file TargetFile
>
> cp [option] file[s] ... folder[s] TargetFolder

* 参数
  * -r: 复制内容包含文件夹

### man

输出用户手册

* 命令格式

> man command[s]



## sh

用户可以编写`.sh`文件

> sh /path/to/sh/xxx.sh

即可



## install命令与命令开发

安装或卸载（使用option -d）已经提供原文件或`*.o`文件的命令

* 命令格式

>install [option] command[s]

* 参数

  -d: 后跟要卸载的命令

### install命令的实现

install命令通过调用`system("make")`编译新命令并重新链接实现增加新命令或删除旧命令

### Shell Similator 的模块结构

![image-20200421115938685](https://github.com/yegcjs/simu-Shell/raw/master/pic/image-20200421115938685.png)

1. myTerm中通过`system("./myShell)`启动myShell
2. myShell中读取命令并根据命令是否已经被install决定是否分配给cmdManager
3. cmdManager收到分配后，调用相应的命令（每个命令为一个类，都继承自Command基类）

#### ShellSimulator下的文件目录

![image-20200421120438254](https://github.com/yegcjs/simu-Shell/raw/master/pic/image-20200421120438254.png)

* ./files/config.txt 中记录已经install的命令

![image-20200421120544722](https://github.com/yegcjs/simu-Shell/raw/master/pic\image-20200421120544722.png)

* ./files/manuals/*.man为各个命令同名的帮助文档
* ./source下存放所有源文件
* ./bin下存放所有.o文件
* ./makefile中进行除myTerm模块以外的所有编译

### install命令执行流程

1. cmdManager调用install
2. install检查用户给出的参数中的命令是否已经被安装，以及是否在./source目录下有对应的源文件，未安装且有源文件的加入一个set中
3. 改写config.txt，加入新命令
4. 改写cmdManager，加入对新命令调用的代码段
5. 改写makefile，加入对新命令的编译和链接
6. 调用`system("make")`重新编译myShell
7. `exit(1)`退出当前`myShell`
8. `myTerm`收到返回值后重新`system("myShell")`重启myShell



### 编写命令涉及的API

myShell提供`cmdManager.h/.cpp`来调用命令，调用命令的代码为

```c++
if(cmd == string("myCommand"))
    myCommand tmp(argv);
```

即命令的调用通过创建临时变量完成。其中`argv`为命令行中除去命令名的部分，该分割在`myShell.h/.cpp`中完成，不需要重新设计。

开发一个新的命令，开发者需要：

* 设计一个类，包含同名.h,.cpp文件，并存放到./source目录下

* 该类的构造函数`myCommand(string argv);`

* 并在构造函数中完成所有命令操作。

开发者也可以借助`Command`类作为基类对命令进行开发，

* Command中提供的API

```c++
class Command{ //Base
protected:
    vector<string> option;
	vector<vector<string>> args;
	enum type{_file_,_dir_,_null_};
	type filetype(string file);
public:
	Command(string input);
	virtual ~Command();
	virtual int check_init()=0;
	virtual void print_error(char*error_type,string args)=0;
};
```

在Command的构造函数中，将完成命令行的分割并存储到options和args中

例如：

>cmd file1 file2 -abc file3 file4 -e file5

将得到：

`option[0]="",args[0]={"file1","file2"}`

`option[1]="abc",args[1]={"file3","file4"}`

`option[2]="e", args[2]={"file5"}`

* 开发者需要在派生类中根据命令的参数及其意义，重定义`check_init`和`paint_error`


```c++
#include"Command.h"
class myCommand:public Command{
public:
  myCommand(string input);
  int check_init();
  void print_error(char * error_type, string args);
};
```

* 一般来说，建议`myCommand(string input)`按如下格式定义

```c++
myCommand::myCommand(string input)
	:Command(input){
    if(!check_init())
        cout<<"myCommand: type man myCommand for help"<<endl;
    else{
        //your
        //code
        //here
    }
}
```

#### 一个例子: demo

* demo.h

```c++
#include"Command.h"

using namespace std;

class demo:public Command{
public:
  demo(string input);
  ~demo();
  int check_init();
  void print_error(char* error_type,string argv);
};
```

* demo.cpp

  ```c++
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
  ```

  将`demo.h`和`demo.cpp`存放在`./source`目录下

  运行myTerm启动终端和myShell

  安装demo：

  >install demo

  ![DeepinScreenshot_select-area_20200422005121](https://github.com/yegcjs/simu-Shell/raw/master/pic/DeepinScreenshot_select-area_20200422005121.png)

  尝试运行demo：![DeepinScreenshot_select-area_20200422005219](https://github.com/yegcjs/simu-Shell/raw/master/pic/DeepinScreenshot_select-area_20200422005219.png)

  卸载demo：

  ![DeepinScreenshot_select-area_20200422005121](https://github.com/yegcjs/simu-Shell/raw/master/pic/DeepinScreenshot_select-area_20200422005104.png)

  也可以同时安装、卸载多个命令

## 其他未定义命令

将通过`system(CommandLine)`调用系统的Shell运行。
