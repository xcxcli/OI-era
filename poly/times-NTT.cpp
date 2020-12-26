#include<stdio.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=1000001,M=998244353,G=3,invG=332748118;
int n,m,l=1,r[N],p,a[N],b[N],invl;
int Pow(int x,int a){
	int s=1;
	while(a){
		if(a&1)s=(ll)s*x%M;
		x=(ll)x*x%M,a>>=1;
	}
	return s;
}
void NTT(int*x,int g){
	for(int i=0;i<l;++i)if(i<r[i])p=x[i],x[i]=x[r[i]],x[r[i]]=p;
	for(int i=1;i<l;i<<=1){
		int T=Pow(g,(M-1)/i/2);
		for(int j=0;j<l;j+=(i<<1)){
			int t=1;
			for(int k=j;k<i+j;++k,t=(ll)t*T%M)p=(ll)t*x[i+k]%M,x[i+k]=(x[k]-p+M)%M,x[k]=(x[k]+p)%M;
		}
	}
}
int main(){
	n=rd(),m=rd();
	for(int i=0;i<n;++i)a[i]=rd();
	for(int i=0;i<m;++i)b[i]=rd();
	while(l<n+m-1)l<<=1;
	for(int i=0;i<l;++i)r[i]=(r[i>>1]>>1)|((i&1)?l>>1:0);
	NTT(a,G),NTT(b,G),invl=Pow(l,M-2);
	for(int i=0;i<l;++i)a[i]=(ll)a[i]*b[i]%M;
	NTT(a,invG);
	for(int i=0;i<n+m-1;++i)printf("%lld ",(ll)a[i]*invl%M);
	puts("");
	return 0;
}
