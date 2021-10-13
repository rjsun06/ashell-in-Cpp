#include <cstdio>




#include <string.h>
typedef struct charChain{
		int value;
		charChain *next;
		charChain *former;
		charChain(int _value, charChain*_former=NULL,charChain*_next=NULL){
			value=_value;
			former=_former;
			next=_next;	
		}
}chain;
		
class Chain{
	public:
	chain* head;
	chain* pos;
	Chain(){
		head=new chain(0);
		pos=head;
	}
	void insert(int newChar){
		chain* former=pos;chain*next=pos->next;
		pos=new chain(newChar,former,next);
		former->next=pos;
		if(next)next->former=pos;
	}
	void del(){
		chain* former=pos;chain*next=pos->next;
		pos->value=0;
		if(next){
			next->former=former;
			pos=next;
		}
		if(former){
			former->next=next;
			pos=former;
		}
	}
	void back(){
		if(pos->former)pos=pos->former;
	}
	void fore(){
		if(pos->next)pos=pos->next;
	}
	char** print(){
		char**ret=new char*[32];
		char charList[128];
		char* str=charList;
		while(head){
			*(str++)=head->value;
			head=head->next;
		}
		str=charList;
		printf(str);
		const char * split = " ";
		char * p;
		p = strtok (str,split);
		int i=0;
		while(p!=NULL) {
			ret[i++]=p;
			p = strtok(NULL,split);
		}
		return ret;
	}
};
