#include<stdio.h>
const int N=2000001;
int lst;
struct SAM{
	int pn=1;
	struct T{int f,len,s[26];}t[N];
	int Ins(int c,int lst){
		int p=lst;
		if(t[p].s[c]&&t[t[p].s[c]].len==t[p].len+1)return t[p].s[c];
		int np=++pn;t[np].len=t[p].len+1;
		for(;p&&!t[p].s[c];p=t[p].f)t[p].s[c]=np;
		if(!p){t[np].f=1;return np;}
		int q=t[p].s[c];
		if(t[q].len==t[p].len+1){t[np].f=q;return np;}
		int nq=++pn;t[nq]=t[q],t[nq].len=t[p].len+1,t[np].f=t[q].f=nq;
		for(;p&&t[p].s[c]==q;p=t[p].f)t[p].s[c]=nq;
		return p==lst?nq:np;
	}
	int Ins(char*s){int lst=1;for(int i=0;s[i]!='\0';++i)lst=Ins(s[i]-'0',lst);return lst;}
}S;
int main(){
	return 0;
}
