//luoguP4148 简单题
#include<stdio.h>
#include<algorithm>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
const int N=200001;const double alpha=0.75;
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
struct T{int l,r,v,s,sz,d[2],mn[2],mx[2];}t[N];
int rt,len,D,h[N],pn,a[2],b[2],o,A,ans;
bool cmp(int x,int y){return t[x].d[D]<t[y].d[D];}
#define ls t[x].l
#define rs t[x].r
void Up(int x){
	t[x].sz=t[ls].sz+t[rs].sz+1,t[x].s=t[ls].s+t[rs].s+t[x].v;
	for(int i=0;i<2;++i){
		if(ls)t[x].mn[i]=Min(t[x].mn[i],t[ls].mn[i]),t[x].mx[i]=Max(t[x].mx[i],t[ls].mx[i]);
		if(rs)t[x].mn[i]=Min(t[x].mn[i],t[rs].mn[i]),t[x].mx[i]=Max(t[x].mx[i],t[rs].mx[i]);
	}
}
void Make(int&x,int l,int r,int k){
	if(l>r)return;int p=(l+r)>>1;
	D=k,std::nth_element(h+l,h+p+1,h+r+1,cmp),x=h[p],t[x].s=t[x].v;
	for(int i=0;i<2;++i)t[x].mn[i]=t[x].mx[i]=t[x].d[i];
	Make(ls,l,p-1,k^1),Make(rs,p+1,r,k^1),Up(x);
}
void Destroy(int&x){
	if(!x)return;
	h[++pn]=x,Destroy(ls),Destroy(rs),x=0;
}
void Rebuild(int&x,int k){
	h[pn=1]=++len,t[len].sz=1,t[len].v=t[len].s=A;
	for(int i=0;i<2;++i)t[len].d[i]=a[i];
	Destroy(x),Make(x,1,pn,k);
}
void Insert(int&x,int k){
	if(!x){
		t[x=++len].sz=1,t[x].v=t[x].s=A;
		for(int i=0;i<2;++i)t[x].d[i]=t[x].mn[i]=t[x].mx[i]=a[i];
		return;
	}
	if(a[k]<t[x].d[k]){
		if(t[ls].sz>t[x].sz*alpha)Rebuild(x,k);
		else Insert(ls,k^1);
	}
	else{
		if(t[rs].sz>t[x].sz*alpha)Rebuild(x,k);
		else Insert(rs,k^1);
	}
	Up(x);
}
bool CheckRange(int x){
	if(!x)return 0;
	for(int i=0;i<2;++i)if(t[x].mn[i]<a[i]||b[i]<t[x].mx[i])return 0;
	return 1;
}
bool CheckPoint(int x){
	if(!x)return 0;
	for(int i=0;i<2;++i)if(t[x].d[i]<a[i]||b[i]<t[x].d[i])return 0;
	return 1;
}
bool Check(int x){
	if(!x)return 0;
	for(int i=0;i<2;++i)if(t[x].mn[i]>b[i]||t[x].mx[i]<a[i])return 0;
	return 1;
}
void Query(int x){
	if(CheckRange(x)){ans+=t[x].s;return;}
	if(CheckPoint(x))ans+=t[x].v;
	if(Check(ls))Query(ls);
	if(Check(rs))Query(rs);
}
int main(){
	rd();
	while(1){
		o=rd();
		if(o==3)return 0;
		if(o==1)a[0]=rd()^ans,a[1]=rd()^ans,A=rd()^ans,Insert(rt,0);
		else a[0]=rd()^ans,a[1]=rd()^ans,b[0]=rd()^ans,b[1]=rd()^ans,ans=0,Query(rt),printf("%d\n",ans);
	}
}
