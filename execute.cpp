#include "ashell.h"
	char* allert=(char*)malloc(16);
	Command::Command(){}
	Command::Command(char*_arg0,vector<string>_argv){
		arg0=_arg0;
		argv=_argv;
		argn=argv.size();
		setActNum();
	};
	bool nextWordTo(vector<char>::iterator& itr,vector<char>::iterator& end, string& des,char goal=0){
		vector<char>::iterator left;
		if(itr==end)return 0;
		while(*itr==' ')itr++;
		if(itr==end||(goal==0&&(*itr=='|'||*itr=='>'))||*itr==goal)return 0;
		left=itr;
		while(itr!=end&&((goal==0&&*itr!=' '&&*itr!='|'&&*itr!='>'&&*itr!='<')||(goal&&*itr!=goal))){
			itr++;
		}
		des.assign(left,itr);
		return 1;
	}
	Command::Command(vector<char>::iterator itr,vector<char>::iterator end){
		next=NULL;
		argn=0;
		string tmp;
		
		

		out=savedOut;
		if(itr!=end){
			//cout<<"\nhave args\n"<<*itr;
			while(nextWordTo(itr,end,tmp)){
				argv.push_back(tmp);
				argn++;
			}
			if(*itr=='|'){
	

				next=new Command(++itr,end);
				
			}
			else if(*itr=='>'){
				nextWordTo(++itr,end,outf,' ');
				write(1,"\n",1);
				
			}
			else if(*itr=='<'){
				nextWordTo(++itr,end,inf,' ');
			
			}
			setActNum();
			arg0=argv[0];
		}
		//cout<<endl<<argv[0]<<endl;
		//cout<<"form "<<inf<<"\nto"<<outf<<endl;
	};
	
	void Command::setActNum(){
		const char* tmp=argv[0].c_str();
		if(!strcmp(tmp,"cd"))
			cmdNum=1;
		else if(!strcmp(tmp,"ls"))
			cmdNum=2;
		else if(!strcmp(tmp,"pwd"))
			cmdNum=3;
		else if(!strcmp(tmp,"ff"))
			cmdNum=4;
		else if(!strcmp(tmp,"exit"))
			cmdNum=-1;
	};
	int childNum;
	bool Command::execute(int inflow=0){
		if(next){
			inflow=pipeline(this,cmdNum,argv,inf,outf,inflow);
			next->execute(inflow);
		}else {
			pipeline(this,cmdNum,argv,inf,outf,inflow,1);
			for(;childNum>0;childNum--)
				wait(NULL);
			dup2(savedIn,0);
			dup2(savedOut,1);
			close(inflow);
		}
		return 1;
	}
	
	int pipeline(Command* cmd,int&cmdNum,vector<string>&argv,string&inf,string&outf,int&inflow,bool direct){
		int io[2];
		if(direct){io[0]=0;io[1]=1;}
		else pipe(io);
		int argn=argv.size();
		switch(cmdNum){
			case(-1):
				callexit();
				if(*allert)cmd->doAllert();
				return(inflow);
			case(1)://"cd"
				write(1,"\n",1);
				cd(argn,argv);	
				if(*allert)cmd->doAllert();
				return(inflow);
		}
		int pid = fork();
		
		if(pid<0)return 0;
		if(pid == 0){
			
			if(inf!="")dup2(open(inf.c_str(),O_RDONLY),0);
			else if(inflow)dup2(inflow,0);
			//cout<<endl<<inf<<endl;
			
			if(outf!="")dup2(open(outf.c_str(),O_WRONLY|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO ),1);
			else dup2(io[1],1);
			//cout<<endl<<outf<<endl;
			if(!direct)close(io[0]);
			//execlp( "ls", "ls", "-1", NULL );
			exc(cmd,cmdNum,argv);
			exit(1);
		}
		else{
			childNum++;
			if(inflow)close(inflow); 
			if(!direct)close(io[1]);  
			//execlp( "wc", "wc", "-l", NULL );	
			//wait(NULL);
			return io[0];
		}
	}	
	
	void exc(Command* cmd,int&cmdNum,vector<string>&argv){
		int argn=argv.size();
		write(1,"\n",1);
		switch(cmdNum){
			case(2)://"ls"
				ls(argn,argv);
				break;
			case(3)://"pwd"
				pwd(argn,argv);
				break;
			case(4)://"ff"
				ff(argn,argv);
				break;
			default:
				char *arguments[argv.size()];
				int i=0;
				for(;i<argn;i++){
					arguments[i]=const_cast<char*>(argv[i].c_str());
				}arguments[i]=NULL;
				
				if(execvp(arguments[0],arguments)<0){
					strcpy(allert,"command not found");
					cmd->doAllert();
					exit(0);
				}else{
					execlp(arguments[0], arguments[0], arguments, (char *)0);
				
				}
		}
		
		if(*allert)cmd->doAllert();
		
	}
		
		
		
		
		
		
		
		
		
	

	//Command::~Command(){
	//	delete arg0;
	//	delete argn;
	 ///	delete cmdNum;
	//	delete argv;
	//	if(next)next->~Command();
	//}

	void Command::doAllert(){
		write(2,arg0.c_str(),arg0.length());
		write(2,": ",2);
		write(2,allert,strlen(allert));
		write(2,"\n",1);
		//for(auto c:argv)cout<<c<<endl;
	}


void cd(int argn,vector<string> argv) { // 执行cd命令

	if (argn <2) {
		strcpy(allert,"arg false");
	}
	else{
		if(chdir(argv[1].c_str()))strcpy(allert,"fail to cd");
	   	else getCurWorkDir();
	}
}

void show_file_info(int filenameSize,char *filename, struct stat *info_p);
void mode_to_letters(int mode, char str[]);



int ls(int argc, vector<string> argv)//https://www.cnblogs.com/wanghao-boke/p/11959330.html
{
	char* dirname;
	if (argc == 1)
	{
		strcpy(dirname,".");
	}	
	else
	{
		strcpy(dirname,argv[1].c_str());
	}
	
	DIR *dir_ptr;
	struct dirent *direntp;

	if ((dir_ptr = opendir(dirname)) == NULL)
	{
		strcpy(allert,"fail to open dir");
		return 0;
	}
	else
	{
		while((direntp = readdir(dir_ptr)) != NULL)
		{
			char *filename=direntp->d_name;
			int filenameSize=direntp->d_reclen-19;
			struct stat info;
			if (stat(filename, &info) == -1)
			{
			perror(filename);
			}
			else
			{
			show_file_info(filenameSize,filename, &info);
			}
		}
		closedir(dir_ptr);
	}
	return 1;
}

void show_file_info(int filenameSize,char *filename, struct stat *info_p)
{
	char modestr[11];

	mode_to_letters(info_p->st_mode, modestr);

	write(1,modestr,11);
	write(1,filename,filenameSize);
	write(1,"\n",1);
}

void mode_to_letters(int mode, char str[])
{
	strcpy(str, "-----------");

	if (S_ISDIR(mode))	str[0] = 'd';
	if (S_ISCHR(mode))	str[0] = 'c';
	if (S_ISBLK(mode))	str[0] = 'b';

	if (mode & S_IRUSR)	str[1] = 'r';
	if (mode & S_IWUSR) str[2] = 'w';
	if (mode & S_IXUSR)	str[3] = 'x';

	if (mode & S_IRGRP)	str[4] = 'r';
	if (mode & S_IWGRP)	str[5] = 'w';
	if (mode & S_IXGRP) str[6] = 'x';

	if (mode & S_IROTH) str[7] = 'r';
	if (mode & S_IWOTH)	str[8] = 'w';
	if (mode & S_IXOTH)	str[9] = 'x';
	str[10] = ' ';
}




void pwd(int argn,vector<string> argv){
	write(1,CWD,32);
	write(1,"\n",1);
}
void  do_ff(string target,string dirname){
	//cout<<dirname<<endl;
	DIR *dir_ptr;
	struct dirent *direntp;

	if ((dir_ptr = opendir(dirname.c_str())) == NULL){
	strcpy(allert,("fail to open dir"+dirname).c_str());
	}
	else{
		while((direntp = readdir(dir_ptr)) != NULL){
			char *filename=direntp->d_name;
			string tmp=filename;
			string out=dirname+"/"+tmp+"\n";
			if(tmp==target){
				write(1,out.c_str(),out.length());
			}
			struct stat info;
			if (stat((dirname+"/"+filename).c_str(), &info) == -1){}
			else{
				if(tmp!="."&&tmp!=".."&&S_ISDIR(info.st_mode)){
					
					do_ff(target,dirname+"/"+filename);
				}
			}			
		}	
		closedir(dir_ptr);
	}	
}
int ff(int argc,vector<string> argv){
	string target;
		if (argc ==1){
			return 0;
		}	
		
		target=argv[1].c_str();
		do_ff(target,".");
		return 1;
}


void callexit(){
		pid_t pid = getpid();
		if (kill(pid, SIGTERM) == -1) 
			strcpy(allert,"fail to exit");
}

void other(){
	strcpy(allert,"fail to execute");
}
