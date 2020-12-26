#include<stdio.h>
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=(k<<3)+(k<<1)+c-'0',c=getchar();
	return k*f;
}
const int N=1000011,INF=0x7fffffff;
int T,o,p,rt=1,cnt=2,f[N],ch[N][2],size[N],v[N],sum[N];
bool Ch(int x){return ch[f[x]][1]==x;}
void Up(int x){size[x]=size[ch[x][0]]+size[ch[x][1]]+sum[x];}
void Rotate(int x){
	int y=f[x],z=f[y],d=Ch(x),w=ch[x][d^1];
	if(z)ch[z][Ch(y)]=x;
	if(w)f[w]=y;ch[y][d]=w,ch[x][d^1]=y,f[y]=x,f[x]=z,Up(y),Up(x);
}
void Splay(int x,int goal=0){
	while(f[x]!=goal){
		int y=f[x];
		if(f[y]!=goal)Rotate(Ch(x)^Ch(y)?x:y);
		Rotate(x);
	}
	if(!goal)rt=x;
}
void Find(int w){
	int x=rt;
	while(ch[x][w>v[x]]&&v[x]!=w)x=ch[x][w>v[x]];
	Splay(x);
}
void Insert(int w){
	if(!rt){rt=++cnt,v[cnt]=w,size[cnt]=sum[cnt]=1;return;}
	int x=rt,p=0;
	while(1){
		if(v[x]==w){++sum[x];break;}
		p=x,x=ch[x][w>v[x]];
		if(!x){x=++cnt,v[x]=w,size[x]=sum[x]=1,f[x]=p,ch[p][w>v[p]]=x;break;}
	}
	Splay(x),Up(x);
}
int Rank(int w){
	Find(w);
	if(v[rt]>=w)return size[ch[rt][0]];
	return size[ch[rt][0]]+sum[rt];
}
int Kth(int k){
	int x=rt;
	while(1){
		if(k<=size[ch[x][0]])x=ch[x][0];
		else if(k>size[ch[x][0]]+sum[x])k-=size[ch[x][0]]+sum[x],x=ch[x][1];
		else return x;
	}
}
int Pre(int w){
	Find(w);
	if(w>v[rt])return rt;
	int x=ch[rt][0];
	while(ch[x][1])x=ch[x][1];
	return x;
}
int Nxt(int w){
	Find(w);
	if(w<v[rt])return rt;
	int x=ch[rt][1];
	while(ch[x][0])x=ch[x][0];
	return x;
}
void Delete(int w){
	int pre=Pre(w),nxt=Nxt(w);
	Splay(pre),Splay(nxt,pre);
	int d=ch[nxt][0];
	if(sum[d]>1)--sum[d],Splay(d);
	else ch[nxt][0]=0,Splay(nxt);
}
int main(){
	T=rd(),v[1]=-INF,v[2]=INF,ch[1][1]=size[1]=2,f[2]=size[2]=sum[1]=sum[2]=1;
	while(T--){
		o=rd(),p=rd();
		if(o==1)Insert(p);
		if(o==2)Delete(p);
		if(o==3)printf("%d\n",Rank(p));
		if(o==4)printf("%d\n",v[Kth(p+1)]);
		if(o==5)printf("%d\n",v[Pre(p)]);
		if(o==6)printf("%d\n",v[Nxt(p)]);
	}
	return 0;
}