#include<cstdlib>
#include<unistd.h>
#include<pwd.h>
using namespace std;

int main(){
    char term_dir[10010];
    getcwd(term_dir,10009);
    while(1){
        int status = system("./myShell");
        if(status/256!=1)
            return 0;
        chdir(term_dir);
    }
    return 0;
}