#include "ashell.h"


int main(int argc, char *argv[]){
	
	Command* cmd;
	getCurWorkDir();
	vector<char>* cmdline;
	while(!feof(stdin)){
		
		//cout<<CWD;
		childNum=0;
		savedOut=dup(STDOUT_FILENO);
		savedIn=dup(STDIN_FILENO);
		prompt();
		cmdline=parser();
		if(!cmdline)
			continue;
		
		cmd=new Command(cmdline->begin(),cmdline->end());
		cmd->execute(0);
		
	}
}

