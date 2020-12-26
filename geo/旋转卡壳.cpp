#include<stdio.h>
#include<algorithm>
using namespace std;
#define ll long long
#define P pair<int,int>
#define X first
#define Y second
int rd(){
	int k=0;bool f=0;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return f?-k:k;
}
const int N=100001;
int n,S[N],T,K;ll ans;P p[N];
ll Max(ll x,ll y){return x>y?x:y;}
P operator-(P a,P b){return{a.X-b.X,a.Y-b.Y};}
ll operator*(P a,P b){return(ll)a.X*b.Y-(ll)a.Y*b.X;}
ll Area(int a,int b,int c){return(p[a]-p[b])*(p[a]-p[c]);}
ll F(int x){return(ll)x*x;}
ll D(P a,P b){return F(a.X-b.X)+F(a.Y-b.Y);}
int main(){
	n=rd();
	for(int i=0;i<n;++i)p[i].X=rd(),p[i].Y=rd();
	sort(p,p+n);
	for(int i=1;i<n;++i){
		while(T>0&&Area(S[T-1],S[T],i)>=0)--T;
		S[++T]=i;
	}
	K=T;
	for(int i=n-2;i>=0;--i){
		while(T>K&&Area(S[T-1],S[T],i)>=0)--T;
		S[++T]=i;
	}
	for(int i=0,j=1;i<T;++i){
		while(Area(S[i],S[i+1],S[j])>Area(S[i],S[i+1],S[j+1]))j=(j+1)%T;
		ans=Max(ans,Max(D(p[S[i]],p[S[j]]),D(p[S[i+1]],p[S[j]])));
	}
	printf("%lld\n",ans);
	return 0;
}
