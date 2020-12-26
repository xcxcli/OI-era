//luoguP4169 [Violet]天使玩偶/SJY摆棋子
#include<stdio.h>
#include<algorithm>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
const int N=1000001;const double alpha=0.75;
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
int Abs(int x){return x<0?-x:x;}
struct T{int l,r,sz,d[2],mn[2],mx[2];}t[N];
int h[N],pn,len,D,n,m,rt,o,a[2],ans;
bool cmp(int x,int y){return t[x].d[D]<t[y].d[D];}
#define ls t[x].l
#define rs t[x].r
void Up(int x){
	t[x].sz=t[ls].sz+t[rs].sz+1;
	for(int i=0;i<2;++i){
		if(ls)t[x].mn[i]=Min(t[x].mn[i],t[ls].mn[i]),t[x].mx[i]=Max(t[x].mx[i],t[ls].mx[i]);
		if(rs)t[x].mn[i]=Min(t[x].mn[i],t[rs].mn[i]),t[x].mx[i]=Max(t[x].mx[i],t[rs].mx[i]);
	}
}
void Make(int&x,int l,int r,int k){
	if(l>r)return;int p=(l+r)>>1;
	D=k,std::nth_element(h+l,h+p+1,h+r+1,cmp),x=h[p];
	for(int i=0;i<2;++i)t[x].mn[i]=t[x].mx[i]=t[x].d[i];
	Make(ls,l,p-1,k^1),Make(rs,p+1,r,k^1),Up(x);
}
void Destroy(int&x){
	if(!x)return;
	Destroy(ls),h[++pn]=x,Destroy(rs),x=0;
}
void Rebuild(int&x,int k){
	h[pn=1]=++len,t[len].sz=1;
	for(int i=0;i<2;++i)t[len].d[i]=a[i];
	Destroy(x),Make(x,1,pn,k);
}
void Insert(int&x,int k){
	if(!x){
		t[x=++len].sz=1;
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
int Dis(T x){return Abs(x.d[0]-a[0])+Abs(x.d[1]-a[1]);}
int GetDis(T x){
	int s=0;
	for(int i=0;i<2;++i)s+=Max(0,a[i]-x.mx[i])+Max(0,x.mn[i]-a[i]);
	return s;
}
void Query(int x){
	ans=Min(ans,Dis(t[x]));int dl=2e9,dr=2e9;
	if(ls)dl=GetDis(t[ls]);
	if(rs)dr=GetDis(t[rs]);
	if(dl<dr){
		if(dl<ans)Query(ls);
		if(dr<ans)Query(rs);
	}
	else{
		if(dr<ans)Query(rs);
		if(dl<ans)Query(ls);
	}
}
int main(){
	n=len=rd(),m=rd();
	for(int i=1;i<=n;++i){
		h[i]=i;
		for(int j=0;j<2;++j)t[i].d[j]=t[i].mn[j]=t[i].mx[j]=rd();
	}
	Make(rt,1,n,0);
	while(m--){
		o=rd(),a[0]=rd(),a[1]=rd();
		if(o==1)Insert(rt,0);
		else ans=2e9,Query(rt),printf("%d\n",ans);
	}
	return 0;
}
