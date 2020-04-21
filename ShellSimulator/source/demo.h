#include"Command.h"

using namespace std;

class demo:public Command{
public:
  demo(string input);
  ~demo();
  int check_init();
  void print_error(char* error_type,string argv);
};
