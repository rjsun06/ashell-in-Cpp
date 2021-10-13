#include<sys/types.h>
#include<sys/wait.h>
#include <cstdio>
#include <unistd.h> 
#include <string>
#include <unistd.h>

#include <termios.h>
#include <ctype.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <pwd.h> 
#include <dirent.h>
#include<sys/stat.h>
#include<grp.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#define	DEFAULT_HOME		"/tmp"
#define	DEFAULT_PATH		"/bin:/usr/bin:/usr/local/bin:."
#define	DEFAULT_CDPATH		".:.."
using namespace std;
class Command;
extern char	*HOME, *PATH, *CDPATH;
extern char* CWD;
extern int savedOut,savedIn;
extern int childNum;
void prompt();
void bell();
int getCurWorkDir();

vector<char>* parser();

void cd(int argn,vector<string> argv);
int ls(int argn,vector<string> argv);
void pwd(int argn,vector<string> argv);
int ff(int argn,vector<string> argv);
void callexit();
void other();

void execute(Command*);
int pipeline(Command* cmd,int&cmdNum,vector<string>&argv,string&inf,string&outf,int&inflow,bool direct=0);
void exc(Command* cmd,int&cmdNum,vector<string>&argv);
class Command{
	public:
	string arg0;
	int argn;
	int cmdNum;
	vector<string> argv;
	int in,out;
	string inf,outf;
	Command* next;
	Command();
	Command(char*_arg0,vector<string>_argv);
	Command(vector<char>::iterator itr,vector<char>::iterator end);
	//~Command();
	void doAllert();
	void setActNum();
	bool execute(int);
	
};

