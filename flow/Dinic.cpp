#include<stdio.h>
#include<queue>
namespace Flow{
	const int N=100001,M=200001,INF=2e9;
	inline int Min(register int x,register int y){return x<y?x:y;}
	struct E{int v,w,nxt;}e[M];
	int n,s,t,head[N],d[N],cur[N],en=1,u,v,ans;std::queue<int>q;
	void add(int u,int v,int w){e[++en]=(E){v,w,head[u]},head[u]=en;}
	void adds(int u,int v,int w){add(u,v,w),add(v,u,0);}
	bool bfs(){
		for(register int i=1;i<=n;++i)d[i]=INF,cur[i]=head[i];
		d[s]=0,q.push(s);
		while(!q.empty()){
			u=q.front(),q.pop();
			for(register int i=head[u];i;i=e[i].nxt){
				v=e[i].v;
				if(e[i].w&&d[v]==INF)d[v]=d[u]+1,q.push(v);
			}
		}
		return d[t]<INF;
	}
	int dfs(int u,int lim){
		if(u==t||!lim)return lim;
		int flow=0,f,v,i=cur[u];
		for(;i;i=e[i].nxt){
			cur[u]=i,v=e[i].v;
			if(d[v]==d[u]+1){
				f=dfs(v,Min(lim-flow,e[i].w));
				if(f)flow+=f,e[i].w-=f,e[i^1].w+=f;
				if(flow==lim)break;
			}
		}
		return flow;
	}
	int flow(int _n,int _s,int _t){
		ans=0,n=_n,s=_s,t=_t;
		while(bfs())ans+=dfs(s,INF);
		return ans;
	}
}
int main(){
	return 0;
}
