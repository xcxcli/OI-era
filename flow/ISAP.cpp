#include<stdio.h>
#include<queue>
using namespace std;
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
const int N=10001,M=100001,INF=0x7fffffff;
int Min(int x,int y){return x<y?x:y;}
struct edge{int v,w,nxt;}e[M<<1];
int n,m,s,t,u,v,head[N],d[N],gap[N],cur[N],cnt,ans;queue<int>q;
void add(int u,int v,int w){e[cnt].v=v,e[cnt].w=w,e[cnt].nxt=head[u],head[u]=cnt++;}
int dfs(int u,int lim){
	if(u==t){ans+=lim;return lim;}
	int flow=0,f,i=cur[u],v;
	for(;i>=0;i=e[i].nxt){
		v=e[i].v,cur[u]=i;
		if(e[i].w&&d[v]+1==d[u]){
			f=dfs(v,Min(lim-flow,e[i].w));
			if(f)e[i].w-=f,e[i^1].w+=f,flow+=f;
			if(flow==lim)return lim;
		}
	}
	if(--gap[d[u]]==0)d[s]=n+1;
	++gap[++d[u]];return flow;
}
int main(){
	n=rd(),m=rd(),s=rd(),t=rd();
	for(int i=1;i<=n;++i)head[i]=d[i]=-1;
	for(int i=1;i<=m;++i)u=rd(),v=rd(),add(u,v,rd()),add(v,u,0);
	d[t]=0,gap[0]=1,q.push(t);
	while(!q.empty()){
		u=q.front(),q.pop();
		for(int i=head[u];i>=0;i=e[i].nxt){
			v=e[i].v;
			if(d[v]<0)q.push(v),d[v]=d[u]+1,++gap[d[v]];
		}
	}
	while(d[s]<n){
		for(int i=0;i<=n;++i)cur[i]=head[i];
		dfs(s,INF);
	}
	printf("%d\n",ans);
	return 0;
}
