#include<stdio.h>
#include<queue>
using namespace std;
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=1201,M=120001,INF=0x7fffffff;
int Min(int x,int y){return x<y?x:y;}
int n,m,s,t,cnt=1,head[N],h[N],e[N],gap[N];bool I[N];
struct Edge{int v,w,nxt;}a[M];
struct Cmp{bool operator()(int a,int b){return h[a]<h[b];}};
queue<int>Q;priority_queue<int,vector<int>,Cmp>q;
void Add(int u,int v,int w){a[++cnt].v=v,a[cnt].w=w,a[cnt].nxt=head[u],head[u]=cnt;}
bool BFS(){
	for(int i=1;i<=n;++i)h[i]=INF;
	h[t]=0,Q.push(t);
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		for(int i=head[u];i;i=a[i].nxt){
			int v=a[i].v;
			if(a[i^1].w&&h[v]>h[u]+1)h[v]=h[u]+1,Q.push(v);
		}
	}
	return h[s]<INF;
}
void Push(int u){
	for(int i=head[u];i;i=a[i].nxt){
		int v=a[i].v,f;
		if(a[i].w&&h[v]+1==h[u]){
			f=Min(e[u],a[i].w),a[i].w-=f,a[i^1].w+=f,e[u]-=f,e[v]+=f;
			if(v!=s&&v!=t&&!I[v])q.push(v),I[v]=1;
			if(!e[u])return;
		}
	}
}
void Relabel(int u){
	h[u]=INF;
	for(int i=head[u];i;i=a[i].nxt){
		int v=a[i].v;
		if(a[i].w&&h[v]+1<h[u])h[u]=h[v]+1;
	}
}
void HLPP(){
	if(!BFS()){puts("0");return;}
	h[s]=n;
	for(int i=1;i<=n;++i)if(h[i]!=INF)++gap[h[i]];
	for(int i=head[s];i;i=a[i].nxt){
		int v=a[i].v,f=a[i].w;
		if(f){
			a[i].w-=f,a[i^1].w+=f,e[s]-=f,e[v]+=f;
			if(v!=s&&v!=t&&!I[v])q.push(v),I[v]=1;
		}
	}
	while(!q.empty()){
		int u=q.top();q.pop(),I[u]=0,Push(u);
		if(e[u]){
			if(--gap[h[u]]==0)
				for(int v=1;v<=n;++v)
					if(v!=s&&v!=t&&h[v]>h[u]&&h[v]<=n)h[v]=n+1;
			Relabel(u),++gap[h[u]],q.push(u),I[u]=1;
		}
	}
	printf("%d\n",e[t]);
}
int main(){
	n=rd(),m=rd(),s=rd(),t=rd();
	for(int i=1,u,v;i<=m;++i)u=rd(),v=rd(),Add(u,v,rd()),Add(v,u,0);
	HLPP();
	return 0;
}