#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
const int N=100001;
int rt,x,y,z,pn,sz[N],ch[N][2],v[N],rnd[N];
#define ls ch[t][0]
#define rs ch[t][1]
void Up(int t){sz[t]=sz[ls]+sz[rs]+1;}
void SplitW(int t,int&a,int&b,int w){
	if(!t){a=b=0;return;}
	if(w>=v[t])a=t,SplitW(rs,rs,b,w);
	else b=t,SplitW(ls,a,ls,w);
	Up(t);
}
void SplitS(int t,int&a,int&b,int k){
	if(!t){a=b=0;return;}
	if(k>=sz[ls]+1)a=t,SplitS(rs,rs,b,k-sz[ls]-1);
	else b=t,SplitS(ls,a,ls,k);
	Up(t);
}
int Merge(int a,int b){
	if(!a||!b)return a|b;
	if(rnd[a]<rnd[b]){ch[a][1]=Merge(ch[a][1],b),Up(a);return a;}
	ch[b][0]=Merge(a,ch[b][0]),Up(b);return b;
}
void List(int t){
	if(!t)return;
	List(ls),printf("%d ",v[t]),List(rs);
}
int n=10,m=8;
int main(){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	srand(time(0));
	for(int i=1;i<=n;++i)sz[i]=1,v[i]=i<<1,rnd[i]=rand(),rt=Merge(rt,i);
	return 0;
}
