#include<stdio.h>
#include<algorithm>
using namespace std;
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k; 
}
const int N=500001;
struct L{int x,l,r,f;}l[N];
bool cmp(L a,L b){return a.x<b.x;}
int n,c[N<<3],A,B,v[N<<3],b[N<<1],x1,y1,x2,y2;ll ans;
void Up(int x,int l,int r){
	if(c[x])v[x]=b[r+1]-b[l];
	else if(l==r)v[x]=0;
	else v[x]=v[x<<1]+v[x<<1|1];
}
void Update(int x,int l,int r,int L,int R,int f){
	if(L<=l&&r<=R){c[x]+=f,Up(x,l,r);return;}
	int p=(l+r)>>1;
	if(L<=p)Update(x<<1,l,p,L,R,f);
	if(p<R)Update(x<<1|1,p+1,r,L,R,f);
	Up(x,l,r);
}
int main(){
	n=rd();
	for(int i=1;i<=n;++i){
		x1=rd(),y1=rd(),x2=rd(),y2=rd();
		l[++B]=(L){x1,y1,y2,1},b[B]=y1,l[++B]=(L){x2,y1,y2,-1},b[B]=y2;
	}
	sort(l+1,l+B+1,cmp),sort(b+1,b+B+1),A=unique(b+1,b+B+1)-b-1;
	for(int i=1;i<=B;++i){
		Update(1,1,A,lower_bound(b+1,b+A+1,l[i].l)-b,lower_bound(b+1,b+A+1,l[i].r)-b-1,l[i].f);
		ans+=(ll)v[1]*(l[i+1].x-l[i].x);
	}
	printf("%lld\n",ans);
	return 0;
}
