#include<stdio.h>
#include<algorithm>
using namespace std;
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
const int N=200001;
struct Q{int o,l,r,p,v;}q[N<<1],q1[N<<1],q2[N<<1];
int n,m,len,s,a[N],b[N],ans[N],t[N],x,y,k;
void Add(int x,int s){while(x<=n)t[x]+=s,x+=x&(-x);}
int Query(int x){int s=0;while(x)s+=t[x],x-=x&(-x);return s;}
void solve(int l,int r,int L,int R){
	if(L>R)return;
	if(l==r){
		for(int i=L;i<=R;++i)if(q[i].o==2)ans[q[i].p]=l;
		return;
	}
	int p=(l+r)>>1,s1=0,s2=0,x;
	for(int i=L;i<=R;++i){
		if(q[i].o==1){
			if(q[i].v<=p)Add(q[i].p,1),q1[++s1]=q[i];
			else q2[++s2]=q[i];
		}
		else{
			x=Query(q[i].r)-Query(q[i].l-1);
			if(q[i].v<=x)q1[++s1]=q[i];
			else q[i].v-=x,q2[++s2]=q[i];
		}
	}
	for(int i=1;i<=s1;++i)if(q1[i].o==1)Add(q1[i].p,-1);
	for(int i=1;i<=s1;++i)q[L+i-1]=q1[i];
	for(int i=1;i<=s2;++i)q[L+i+s1-1]=q2[i];
	solve(l,p,L,L+s1-1),solve(p+1,r,L+s1,R);
}
int main(){
	s=n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=b[i]=rd();
	sort(b+1,b+n+1),len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;++i)q[i]=(Q){1,0,0,i,lower_bound(b+1,b+len+1,a[i])-b};
	for(int i=1;i<=m;++i)x=rd(),y=rd(),k=rd(),q[++s]=(Q){2,x,y,i,k};
	solve(1,len,1,s);
	for(int i=1;i<=m;++i)printf("%d\n",b[ans[i]]);
	return 0;
}