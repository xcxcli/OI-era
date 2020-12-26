#include<stdio.h>
typedef long long ll;
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int M=1000000007;
int n,m,p;ll a[401][801],t,r;
ll Pow(ll x,ll p){
	ll s=1;
	while(p){
		if(p&1)s=s*x%M;
		x=x*x%M,p>>=1;
	}
	return s;
}
int main(){
	n=rd(),m=n<<1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)a[i][j]=rd();
		a[i][n+i]=1;
	}
	for(int i=1;i<=n;++i){
		p=i;
		for(int j=i;j<=n;++j)if(a[j][i]){p=j;break;}
		if(!a[i][i]){puts("No Solution");return 0;}
		for(int j=1;j<=m;++j)t=a[i][j],a[i][j]=a[p][j],a[p][j]=t;
		r=Pow(a[i][i],M-2);
		for(int j=i;j<=m;++j)a[i][j]=a[i][j]*r%M;
		for(int j=1;j<=n;++j)if(i!=j){
			r=a[j][i];
			for(int k=i;k<=m;++k)a[j][k]=(a[j][k]-r*a[i][k]%M+M)%M;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=n+1;j<=m;++j)printf("%lld ",a[i][j]);
		puts("");
	}
	return 0;
}