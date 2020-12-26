#include<stdio.h>
#include<algorithm>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
const int N=100001;
struct P{int a,b,c,w,f;}q[N],b[N];
bool cmp(const P&x,const P&y){return x.a!=y.a?x.a<y.a:x.b!=y.b?x.b<y.b:x.c<y.c;}
int n,m,pn=1,t[N<<1],ans[N];
void Add(int x,int s){while(x<=m)t[x]+=s,x+=x&(-x);}
int Query(int x){int s=0;while(x)s+=t[x],x&=(x-1);return s;}
void CDQ(int l,int r){
	if(l==r)return;
	int p=(l+r)>>1,i=l,j=p+1,k=l;CDQ(l,p),CDQ(p+1,r);
	while(k<=r){
		if(r<j||(i<=p&&q[i].b<=q[j].b))Add(q[i].c,q[i].w),b[k++]=q[i++];
		else q[j].f+=Query(q[j].c),b[k++]=q[j++];
	}
	for(k=l;k<=p;++k)Add(q[k].c,-q[k].w);
	for(k=l;k<=r;++k)q[k]=b[k];
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)q[i]={rd(),rd(),rd(),1};
	std::sort(q+1,q+n+1,cmp);
	for(int i=2;i<=n;++i){
		if(q[i].a==q[pn].a&&q[i].b==q[pn].b&&q[i].c==q[pn].c)++q[pn].w;
		else q[++pn]=q[i];
	}
	CDQ(1,pn);
	for(int i=1;i<=pn;++i)ans[q[i].f+q[i].w-1]+=q[i].w;
	for(int i=0;i<n;++i)printf("%d\n",ans[i]);
	return 0;
}
