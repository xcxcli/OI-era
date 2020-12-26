#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=(k<<3)+(k<<1)+c-'0',c=getchar();
	return k*f;
}
const int N=1000011,INF=0x7fffffff;
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
int T,o,w,cnt,rt,ch[N][2],v[N],sum[N],sz[N],rnd[N];
void Up(int x){sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+sum[x];}
void Rotate(int&x,bool d){
	int s=ch[x][d];
	ch[x][d]=ch[s][d^1],ch[s][d^1]=x,Up(x),Up(s),x=s;
}
void Insert(int&x){
	if(!x){x=++cnt,v[x]=w,sz[x]=sum[x]=1,rnd[x]=rand();return;}
	++sz[x];
	if(w==v[x]){++sum[x];return;}
	bool d=w>v[x];Insert(ch[x][d]);
	if(rnd[x]>rnd[ch[x][d]])Rotate(x,d);
}
void Delete(int&x){
	if(!x)return;
	if(w==v[x]){
		if(sum[x]>1){--sum[x],--sz[x];return;}
		bool d=rnd[ch[x][0]]>rnd[ch[x][1]];
		if(!ch[x][0]||!ch[x][1])x=ch[x][0]|ch[x][1];
		else Rotate(x,d),Delete(x);
	}
	else --sz[x],Delete(ch[x][w>v[x]]);
}
int Findn(int x){
	if(w==v[x])return sz[ch[x][0]];
	if(w<v[x])return Findn(ch[x][0]);
	return Findn(ch[x][1])+sz[ch[x][0]]+sum[x];
}
int Findk(int x,int k){
	if(sz[ch[x][0]]>=k)return Findk(ch[x][0],k);
	if(sz[ch[x][0]]+sum[x]>=k)return v[x];
	return Findk(ch[x][1],k-sz[ch[x][0]]-sum[x]);
}
int Findpre(int x){
	if(!x)return -INF;
	if(w<=v[x])return Findpre(ch[x][0]);
	return Max(Findpre(ch[x][1]),v[x]);
}
int Findnxt(int x){
	if(!x)return INF;
	if(w>=v[x])return Findnxt(ch[x][1]);
	return Min(Findnxt(ch[x][0]),v[x]);
}
int main(){
	T=rd();
	while(T--){
		o=rd(),w=rd();
		if(o==1)Insert(rt);
		if(o==2)Delete(rt);
		if(o==3)printf("%d\n",Findn(rt)+1);
		if(o==4)printf("%d\n",Findk(rt,w));
		if(o==5)printf("%d\n",Findpre(rt));
		if(o==6)printf("%d\n",Findnxt(rt));
	}
	return 0;
}
