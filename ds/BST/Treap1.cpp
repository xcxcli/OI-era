#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=(k<<3)+(k<<1)+c-'0',c=getchar();
	return k*f;
}
const int N=100011,INF=0x7fffffff;
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
struct Treap{int ch[2],v,sum,size,rnd;}t[N];
int T,cnt,o,v,rt;
void Up(int x){t[x].size=t[t[x].ch[0]].size+t[t[x].ch[1]].size+t[x].sum;}
void Rotate(int&x,bool d){
	int s=t[x].ch[d];
	t[x].ch[d]=t[s].ch[d^1],t[s].ch[d^1]=x,Up(x),Up(s),x=s;
}
void Insert(int&x){
	if(!x){x=++cnt,t[x].size=t[x].sum=1,t[x].v=v,t[x].rnd=rand();return;}
	++t[x].size;
	if(v==t[x].v){++t[x].sum;return;}
	bool d=v>t[x].v;Insert(t[x].ch[d]);
	if(t[x].rnd>t[t[x].ch[d]].rnd)Rotate(x,d);
}
void Delete(int&x){
	if(!x)return;
	if(v==t[x].v){
		if(t[x].sum>1){--t[x].sum,--t[x].size;return;}
		bool d=t[t[x].ch[0]].rnd>t[t[x].ch[1]].rnd;
		if(!t[x].ch[0]||!t[x].ch[1])x=t[x].ch[0]|t[x].ch[1];
		else Rotate(x,d),Delete(x);
	}
	else --t[x].size,Delete(t[x].ch[v>t[x].v]);
}
int Findn(int x){
	if(v==t[x].v)return t[t[x].ch[0]].size;
	if(v<t[x].v)return Findn(t[x].ch[0]);
	return Findn(t[x].ch[1])+t[t[x].ch[0]].size+t[x].sum;
}
int Findk(int x,int k){
	if(t[t[x].ch[0]].size>=k)return Findk(t[x].ch[0],k);
	if(t[t[x].ch[0]].size+t[x].sum>=k)return t[x].v;
	return Findk(t[x].ch[1],k-t[t[x].ch[0]].size-t[x].sum);
}
int Findpre(int x){
	if(!x)return -INF;
	if(v<=t[x].v)return Findpre(t[x].ch[0]);
	return Max(Findpre(t[x].ch[1]),t[x].v);
}
int Findnxt(int x){
	if(!x)return INF;
	if(v>=t[x].v)return Findnxt(t[x].ch[1]);
	return Min(Findnxt(t[x].ch[0]),t[x].v);
}
int main(){
	T=rd();
	while(T--){
		o=rd(),v=rd();
		if(o==1)Insert(rt);
		if(o==2)Delete(rt);
		if(o==3)printf("%d\n",Findn(rt)+1);
		if(o==4)printf("%d\n",Findk(rt,v));
		if(o==5)printf("%d\n",Findpre(rt));
		if(o==6)printf("%d\n",Findnxt(rt));
	}
	return 0;
}