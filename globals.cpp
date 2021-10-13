#include "ashell.h"
const int BUF_SZ=64;
char *CWD=(char*)malloc(BUF_SZ),*username=(char*)malloc(BUF_SZ),*hostname=(char*)malloc(BUF_SZ);
char prompt_note='%';
char	*HOME, *PATH, *CDPATH;
int savedOut,savedIn;
void prompt(){
	write(1,"/...",4);
	write(1,strrchr(CWD,'/'),24);
	write(1,&prompt_note,1);
	write(1," ",1);
}

void bell(){

}

void getUsername() { // 获取当前登录的用户名
    struct passwd* pwd = getpwuid(getuid());
    strcpy(username, pwd->pw_name);
}

void getHostname() { // 获取主机名
    gethostname(hostname, BUF_SZ);
}

int getCurWorkDir() { // 获取当前的工作目录
	memset(CWD,0,BUF_SZ);
    char* result = getcwd(CWD, BUF_SZ);

    //cout<<CWD<<endl;
    if (result == NULL)
        return 0;
    else return 1;
}
