#include<stdio.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=2000003;
struct L{int n,nxt;ll mu;}l[N];
int T,P[N],s,mu[N],head[N],cnt;bool p[N];
void Insert(int n,ll mu){int s=n%N;l[++cnt]=(L){n,head[s],mu},head[s]=cnt;}
bool Query(int n,ll&mu){
	for(int i=head[n%N];i;i=l[i].nxt)if(l[i].n==n){mu=l[i].mu;return 1;}
	return 0;
}
ll SumMu(ll n){
	if(n<N)return mu[n];
	ll s=1,l=2,r;
	if(Query(n,s))return s;
	for(;l<=n;l=r+1)r=n/(n/l),s-=(r-l+1)*SumMu(n/l);
	Insert(n,s);return s;
}
int main(){
	T=rd(),mu[1]=1;
	for(int i=2;i<N;++i){
		if(!p[i])P[++s]=i,mu[i]=-1;
		for(int j=1,k;j<=s&&(k=P[j]*i)<N;++j){
			p[k]=1;
			if(i%P[j])mu[k]=-mu[i];
			else break;
		}
	}
	for(int i=2;i<N;++i)mu[i]+=mu[i-1];
	while(T--)printf("%lld\n",SumMu(rd()));
	return 0;
}