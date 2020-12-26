#include<stdio.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=2000003;
struct L{int n,nxt;ll phi;}l[N];
int T,P[N],s,head[N],cnt;ll phi[N];bool p[N];
void Insert(int n,ll phi){int s=n%N;l[++cnt]=(L){n,head[s],phi},head[s]=cnt;}
bool Query(int n,ll&phi){
	for(int i=head[n%N];i;i=l[i].nxt)if(l[i].n==n){phi=l[i].phi;return 1;}
	return 0;
}
ll SumPhi(ll n){
	if(n<N)return phi[n];
	ll s=n*(n+1)>>1,l=2,r;
	if(Query(n,s))return s;
	for(;l<=n;l=r+1)r=n/(n/l),s-=(r-l+1)*SumPhi(n/l);
	Insert(n,s);return s;
}
int main(){
	T=rd(),phi[1]=1;
	for(int i=2;i<N;++i){
		if(!p[i])P[++s]=i,phi[i]=i-1;
		for(int j=1,k;j<=s&&(k=P[j]*i)<N;++j){
			p[k]=1;
			if(i%P[j])phi[k]=phi[i]*(P[j]-1);
			else{phi[k]=phi[i]*P[j];break;}
		}
	}
	for(int i=2;i<N;++i)phi[i]+=phi[i-1];
	while(T--)printf("%lld\n",SumPhi(rd()));
	return 0;
}