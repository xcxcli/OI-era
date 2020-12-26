#include<stdio.h>
#include<algorithm>
using namespace std;
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
const int N=5001;
int Abs(int x){return x<0?-x:x;}
struct T{int sum,num,v;bool lf,rf;}t[N<<3];
struct L{int x,l,r,f;}l[N<<1];
bool cmp(L a,L b){return a.x<b.x||a.x==b.x&&a.f>b.f;}
int n,a[N<<1],A,B,x1,y1,x2,y2,ans,pre; 
#define ls (x<<1)
#define rs (x<<1|1)
void Up(int x,int l,int r){
	if(t[x].sum)t[x].num=t[x].lf=t[x].rf=1,t[x].v=a[r+1]-a[l];
	else if(l==r)t[x].num=t[x].v=t[x].lf=t[x].rf=0;
	else{
		t[x].num=t[ls].num+t[rs].num-(t[ls].rf&&t[rs].lf);
		t[x].v=t[ls].v+t[rs].v,t[x].lf=t[ls].lf,t[x].rf=t[rs].rf;
	}
}
void Update(int x,int l,int r,int L,int R,int f){
	if(L<=l&&r<=R){t[x].sum+=f,Up(x,l,r);return;}
	int p=(l+r)>>1;
	if(L<=p)Update(ls,l,p,L,R,f);
	if(p<R)Update(rs,p+1,r,L,R,f);
	Up(x,l,r);
}
int main(){
	n=rd();
	for(int i=1;i<=n;++i){
		x1=rd(),y1=rd(),x2=rd(),y2=rd();
		l[++B]=(L){x1,y1,y2,1},a[B]=y1,l[++B]=(L){x2,y1,y2,-1},a[B]=y2;
	}
	sort(l+1,l+B+1,cmp),sort(a+1,a+B+1),A=unique(a+1,a+B+1)-a-2;
	for(int i=1;i<=B;++i)l[i].l=lower_bound(a+1,a+A,l[i].l)-a,l[i].r=lower_bound(a+1,a+A,l[i].r)-a-1;
	for(int i=1;i<=B;++i){
		Update(1,1,A,l[i].l,l[i].r,l[i].f);
		while(l[i].x==l[i+1].x&&l[i].f==l[i+1].f)++i,Update(1,1,A,l[i].l,l[i].r,l[i].f);
		ans+=Abs(pre-t[1].v),pre=t[1].v,ans+=2*t[1].num*(l[i+1].x-l[i].x);
	}
	printf("%d\n",ans);
	return 0;
}
