#include<stdio.h>
#include<queue>
using namespace std;
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=5001,M=50001,INF=0x7fffffff;
int Min(int x,int y){return x<y?x:y;}
struct edge{int v,w,nxt,c;}e[M*2];
struct P{int e,f;}pre[N];
int n,m,s,t,u,v,w,c,ans,cost,up,head[N],d[N],cnt=1;queue<int>q;bool I[N];
void add(int u,int v,int w,int c){e[cnt].v=v,e[cnt].w=w,e[cnt].c=c,e[cnt].nxt=head[u],head[u]=cnt++;}
bool spfa(){
	for(int i=1;i<=n;++i)d[i]=INF,pre[i].e=pre[i].f=-1;
	q.push(s),I[s]=1,d[s]=0;
	while(!q.empty()){
		u=q.front(),q.pop(),I[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			v=e[i].v,c=e[i].c;
			if(e[i].w&&d[v]>d[u]+c){
				d[v]=d[u]+c,pre[v].f=u,pre[v].e=i;
				if(!I[v])q.push(v),I[v]=1;
			}
		}
	}
	return d[t]<INF;
}
int main(){
	n=rd(),m=rd(),s=rd(),t=rd();
	for(int i=1;i<=m;++i)u=rd(),v=rd(),w=rd(),c=rd(),add(u,v,w,c),add(v,u,0,-c);
	for(int i=1;i<=n;++i)printf("%d ",head[i]);
	puts("");
	for(int i=0;i<cnt;++i)printf("%d %d %d %d\n",e[i].v,e[i].w,e[i].c,e[i].nxt);
	while(spfa()){
		up=INF;
		for(int i=t;i!=s;i=pre[i].f)up=Min(up,e[pre[i].e].w);
		for(int i=t;i!=s;i=pre[i].f)e[pre[i].e].w-=up,e[pre[i].e^1].w+=up;
		ans+=up,cost+=up*d[t];
	}
	printf("%d %d\n",ans,cost);
	return 0;
}