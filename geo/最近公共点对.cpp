#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
#define db double
const int N=200001;
struct P{db x,y;}p[N];
bool cmp(P a,P b){return a.x!=b.x?a.x<b.x:a.y<b.y;}
bool Cmp(int a,int b){return p[a].y<p[b].y;}
db F(db x){return x*x;}
db D(int i,int j){return sqrt(F(p[i].x-p[j].x)+F(p[i].y-p[j].y));}
db Min(db a,db b){return a<b?a:b;}
int n,a[N];
db Merge(int l,int r){
	if(l==r)return 2e9;
	if(l+1==r)return D(l,r);
	int m=(l+r)>>1,t=0;db d=Min(Merge(l,m),Merge(m+1,r));
	for(int i=l;i<=r;++i)if(fabs(p[m].x-p[i].x)<d)a[++t]=i;
	sort(a+1,a+t+1,Cmp);
	for(int i=1;i<=t;++i)for(int j=i+1;j<=t&&p[a[j]].y-p[a[i]].y<d;++j)d=Min(d,D(a[i],a[j]));
	return d;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lf%lf",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp),printf("%.4lf\n",Merge(1,n));
	return 0;
}