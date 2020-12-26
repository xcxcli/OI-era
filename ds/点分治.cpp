//P4178
#include<stdio.h>
#include<algorithm>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
const int N=100001;
struct E{int v,w,nxt;}e[N<<1];
int Max(int x,int y){return x>y?x:y;}
int n,m,u,v,w,en,Sz,rt,ans,qn,d[N],head[N],mp[N],sz[N],vis[N],q[N];
void add(int u,int v,int w){e[++en]=(E){v,w,head[u]},head[u]=en;}
void getrt(int u,int f){
	sz[u]=1,mp[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=f&&!vis[v])getrt(v,u),sz[u]+=sz[v],mp[u]=Max(mp[u],sz[v]);
	}
	mp[u]=Max(mp[u],Sz-sz[u]);
	if(mp[u]<mp[rt])rt=u;
}
void getD(int u,int f){
	q[++qn]=d[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=f&&!vis[v])d[v]=d[u]+e[i].w,getD(v,u);
	}
}
int Calc(int u,int w){
	qn=0,d[u]=w,getD(u,0),std::sort(q+1,q+qn+1);
	int s=0,l=1,r=qn;
	while(l<r){
		while(l<r&&q[l]+q[r]>m)--r;
		if(l<r)s+=r-l;
		++l;
	}
	return s;
}
void Solve(int u){
	vis[u]=1,ans+=Calc(u,0);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(!vis[v])ans-=Calc(v,e[i].w),rt=0,Sz=sz[v],getrt(v,0),Solve(rt);
	}
}
int main(){
	freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	mp[0]=Sz=n=rd();
	for(int i=1;i<n;++i)u=rd(),v=rd(),w=rd(),add(u,v,w),add(v,u,w);
	m=rd(),getrt(1,0),Solve(rt),printf("%d\n",ans);return 0;
	return 0;
}
