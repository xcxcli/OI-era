#include<stdio.h>
#include<queue>
using namespace std;
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=12001,M=1200001,INF=0x7fffffff;
int Min(int x,int y){return x<y?x:y;}
int n,m,s,t,u,v,f,cnt=1,head[N],h[N],e[N],gap[N];bool I[N];
struct Edge{int v,w,nxt;}a[M];
struct Cmp{bool operator ()(int a,int b)const{return h[a]<h[b];}};
queue<int>Q;priority_queue<int,vector<int>,Cmp>q;
void Add(int u,int v,int w){a[++cnt].v=v,a[cnt].w=w,a[cnt].nxt=head[u],head[u]=cnt;}
int main(){
	n=rd(),m=rd(),s=rd(),t=rd();
	for(int i=1;i<=m;++i)u=rd(),v=rd(),Add(u,v,rd()),Add(v,u,0);
	for(int i=1;i<=n;++i)h[i]=INF;
	h[t]=0,Q.push(t);
	while(!Q.empty()){
		u=Q.front(),Q.pop();
		for(int i=head[u];i;i=a[i].nxt){
			v=a[i].v;
			if(a[i^1].w&&h[v]>h[u]+1)h[v]=h[u]+1,Q.push(v);
		}
	}
	if(h[s]==INF){puts("0");return 0;}
	h[s]=n;
	for(int i=1;i<=n;++i)if(h[i]!=INF)++gap[h[i]];
	for(int i=head[s];i;i=a[i].nxt)
		if(a[i].w){
			f=a[i].w,v=a[i].v,a[i].w-=f,a[i^1].w+=f,e[s]-=f,e[v]+=f;
			if(v!=s&&v!=t&&!I[v])q.push(v),I[v]=1;
		}
	while(!q.empty()){
		u=q.top(),q.pop(),I[u]=0;
		for(int i=head[u];i;i=a[i].nxt){
			v=a[i].v;
			if(a[i].w&&h[v]+1==h[u]){
				f=Min(e[u],a[i].w);a[i].w-=f,a[i^1].w+=f,e[u]-=f,e[v]+=f;
				if(v!=s&&v!=t&&!I[v])q.push(v),I[v]=1;
				if(!e[u])break;
			}
		}
		if(e[u]){
			--gap[h[u]];
			if(!gap[h[u]])
				for(int i=1;i<=n;++i)
					if(i!=s&&i!=t&&h[i]>h[u]&&h[i]<n+1)h[i]=n+1;
			h[u]=INF;
			for(int i=head[u];i;i=a[i].nxt){
				v=a[i].v;
				if(a[i].w&&h[v]+1<h[u])h[u]=h[v]+1;
			}
			++gap[h[u]],q.push(u),I[u]=1;
		}
	}
	printf("%d\n",e[t]);
	return 0;
}