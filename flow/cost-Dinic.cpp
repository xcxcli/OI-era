#include<stdio.h>
#include<string.h>
#include<queue>
namespace Flow{
	const int N=10001,M=100001,INF=2e9;
	int Min(int x,int y){return x<y?x:y;}
	struct E{int v,w,c,nxt;}e[M];
	int n,s,t,u,v,w,c,head[N],en=1,d[N],ans,cost;bool I[N];std::queue<int>q;
	void add(int u,int v,int w,int c){e[++en]=(E){v,w,c,head[u]},head[u]=en;}
	void adds(int u,int v,int w,int c){add(u,v,w,c),add(v,u,0,-c);}
	bool spfa(){
		for(int i=1;i<=n;++i)d[i]=INF,I[i]=0;
		q.push(s),d[s]=0;
		while(!q.empty()){
			u=q.front(),q.pop(),I[u]=0;
			for(int i=head[u];i;i=e[i].nxt){
				v=e[i].v,c=e[i].c;
				if(e[i].w&&d[v]>d[u]+c){
					d[v]=d[u]+c;
					if(!I[v])I[v]=1,q.push(v);
				}
			}
		}
		return d[t]<INF;
	}
	int dfs(int u,int lim){
		I[u]=1;
		if(u==t||!lim)return lim;
		int flow=0,f,i=head[u],v,c;
		for(;i;i=e[i].nxt){
			v=e[i].v,c=e[i].c;
			if(e[i].w&&d[v]==d[u]+c&&(!I[v]||v==t)){
				f=dfs(v,Min(lim-flow,e[i].w));
				if(f)flow+=f,cost+=f*c,e[i].w-=f,e[i^1].w+=f;
				if(flow==lim)break;
			}
		}
		return flow;
	}
	void flow(int _n,int _s,int _t){
		n=_n,s=_s,t=_t,ans=cost=0;
		while(spfa()){
			I[t]=1;
			while(I[t])memset(I,0,sizeof(I)),ans+=dfs(s,INF);
		}
	}
}
using Flow::adds,Flow::flow;
int main(){
	return 0;
}
