#include<stdio.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=300001;
void Swap(int&x,int&y){int t=x;x=y,y=t;}
int n,m,o,x,y,T,f[N],ch[N][2],v[N],s[N],st[N];bool r[N];
#define ls ch[x][0]
#define rs ch[x][1]
bool Ch(int x){return ch[f[x]][1]==x;}
bool nroot(int x){return ch[f[x]][0]==x||Ch(x);}
void Up(int x){s[x]=s[ls]^s[rs]^v[x];}
void Rev(int x){Swap(ls,rs),r[x]^=1;}
void Down(int x){if(r[x]){if(ls)Rev(ls);if(rs)Rev(rs);r[x]=0;}}
void Rotate(int x){
	int y=f[x],z=f[y],d=Ch(x),w=ch[x][!d];
	if(nroot(y))ch[z][Ch(y)]=x;
	if(w)f[w]=y;ch[x][!d]=y,ch[y][d]=w,f[y]=x,f[x]=z,Up(y);
}
void Splay(int x){
	int y=x;st[T=1]=y;
	while(nroot(y))st[++T]=y=f[y];
	while(T)Down(st[T--]);
	while(nroot(x)){
		if(nroot(y=f[x]))Rotate(Ch(x)^Ch(y)?x:y);
		Rotate(x);
	}
	Up(x);
}
void Access(int x){for(int y=0;x;x=f[y=x])Splay(x),rs=y,Up(x);}
void MakeRoot(int x){Access(x),Splay(x),Rev(x);}
int FindRoot(int x){
	Access(x),Splay(x);
	while(ls)Down(x),x=ls;
	Splay(x);return x;
}
void Split(int x,int y){MakeRoot(x),Access(y),Splay(y);}
void Link(int x,int y){
	MakeRoot(x);
	if(FindRoot(y)!=x)f[x]=y;
}
void Cut(int x,int y){
	MakeRoot(x);
	if(FindRoot(y)==x&&f[x]==y&&!ch[y][0])f[y]=rs=0,Up(x);
}
int main(){
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)v[i]=rd();
	while(m--){
		o=rd(),x=rd(),y=rd();
		if(o==0)Split(x,y),printf("%d\n",s[y]);
		if(o==1)Link(x,y);
		if(o==2)Cut(x,y);
		if(o==3)Splay(x),v[x]=y;
	}
	return 0;
}
