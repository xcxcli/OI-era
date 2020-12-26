#include<stdio.h>
const int N=1000001,M=N<<1;
struct SAM{
	int pn=1,tn=1,en,head[M];
	struct T{int f,s[26],len;}t[M];
	struct E{int v,nxt;}e[M];
	void add(int u,int v){e[++en].v=v,e[en].nxt=head[u],head[u]=en;}
	void dfs(int u){}
	void Make(){for(int i=2;i<=pn;++i)add(t[i].f,i);dfs(1);}
	void Ins(int c){
		int p=tn,np=tn=++pn;t[np].len=t[p].len+1;
		for(;p&&!t[p].s[c];p=t[p].f)t[p].s[c]=np;
		if(!p){t[np].f=1;return;}
		int q=t[p].s[c];
		if(t[q].len==t[p].len+1){t[np].f=q;return;}
		int nq=++pn;t[nq]=t[q],t[nq].len=t[p].len+1,t[q].f=t[np].f=nq;
		for(;p&&t[p].s[c]==q;p=t[p].f)t[p].s[c]=nq;
	}
	void Ins(char*s){for(int i=0;s[i]!='\0';++i)Ins(s[i]-'0');}
};
int main(){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	return 0;
}
