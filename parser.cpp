#include "ashell.h"
class History{
	private: static const int size=11;
	public:
	vector<char>buffer;
	vector<char>list[size];
	int pos;
	int tmp;
	int num=0;
	History(){
		for(auto c:list)c.clear();
		pos=0;
	}
	void open(){
		if(++pos==size)pos=0;
		reset();
		list[pos].clear();
		buffer.clear();
		if(num<pos)num++;
	}
	void push(){
		list[pos]=buffer;
	}
	void moveUp(){
		if(tmp!=(pos+1)%num){
			tmp=(tmp-1)%num;
			show();
		}
	}
	void moveDown(){
		if(tmp!=pos){
			tmp=(tmp+1)%size;
			show();
		}
	}
	vector<char>* now(){
		return list+tmp;
	}
	void show(){
		//write(1,"  ",2);
		for(auto c:buffer)write(1,"\b",1);
		for(auto c:buffer)write(1," ",1);
		for(auto c:buffer)write(1,"\b",1);
		buffer=list[tmp];
		for(auto c:buffer)write(1,&c,1);
	}
	void reset(){
		tmp=pos;
	}
};
History history;
void ResetCanonicalMode(int fd, struct termios *savedattributes){
    tcsetattr(fd, TCSANOW, savedattributes);
}

void SetNonCanonicalMode(int fd, struct termios *savedattributes){
    struct termios TermAttributes;
    char *name;
    
    // Make sure stdin is a terminal. 
    if(!isatty(fd)){
        fprintf (stderr, "Not a terminal.\n");
        exit(0);
    }
    
    // Save the terminal attributes so we can restore them later. 
    tcgetattr(fd, savedattributes);
    
    // Set the funny terminal modes. 
    tcgetattr (fd, &TermAttributes);
    TermAttributes.c_lflag &= ~(ICANON | ECHO); // Clear ICANON and ECHO. 
    TermAttributes.c_cc[VMIN] = 1;
    TermAttributes.c_cc[VTIME] = 0;
    tcsetattr(fd, TCSAFLUSH, &TermAttributes);
}

void backSpace(){
	write(1,"\b \b",3);//\033[D
}
void print(vector<char>& buffer){
	cout <<"\n---------\n";
	for (const auto &c : buffer) cout << c;
	cout <<"\\0\n---------\n";
}
vector<char>* parser(){

	vector<char>& buffer=history.buffer;
	history.open();
    struct termios SavedTermAttributes;
    char RXChar;
    SetNonCanonicalMode(0, &SavedTermAttributes);
    while(1){
		read(0, &RXChar, 1);
		switch(RXChar){
			case(0x04):
				break;
			case(0x7F)://back
				if(!buffer.empty()){
					buffer.pop_back();
					backSpace();
				}else write(1,"\a",1);
				break;
			case(0x0A)://enter
				ResetCanonicalMode(0, &SavedTermAttributes);
				history.push();
				return &buffer;
			case(0x1B):
				read(0, &RXChar, 1);
				read(0, &RXChar, 1);
				//cout<<'\n'<<RXChar<<endl;
				switch(RXChar){
					case('A')://up
						history.moveUp();
						break;
					case('B')://down
						history.moveDown();
						break;
					case('C')://right
						break;
					case('D')://left
						break;
				}
				continue;
			default:
				buffer.push_back(RXChar);
				write(1,&RXChar,1);
		}
		
	}
    
    ResetCanonicalMode(0, &SavedTermAttributes);
    return 0;
}


