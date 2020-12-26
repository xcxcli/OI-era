#include<stdio.h>
#include<algorithm>
#define ll long long
inline int rd(){
	register int k=0;register char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=2100001,M=998244353,G=3,invG=332748118;
int n,m,l=1,r[N],p,a[N],b[N],invl,rt[N];
inline int f(register int x){return x<M?x:x-M;}
inline int h(register int x){return x<0?x+M:x;}
inline int Pow(register int x,register int a){
	int s=1;
	while(a){
		if(a&1)s=(ll)s*x%M;
		x=(ll)x*x%M,a>>=1;
	}
	return s;
}
inline void NTT(int*x,int g){
	for(int i=0;i<l;++i)if(i<r[i])p=x[i],x[i]=x[r[i]],x[r[i]]=p;
	for(int i=1;i<l;i<<=1)
		for(register int j=0;j<l;j+=(i<<1))
			for(register int k=0,t=j;k<i;++k,++t)
				p=(ll)rt[i+k]*x[i+t]%M,x[i+t]=h(x[t]-p),x[t]=f(x[t]+p);
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd(),m=rd();
	for(register int i=0;i<n;++i)a[i]=rd();
	for(register int i=0;i<m;++i)b[i]=rd();
	while(l<n+m-1)l<<=1;
	for(register int i=0;i<l;++i)r[i]=(r[i>>1]>>1)|((i&1)?l>>1:0);
	for(int i=1;i<l;i<<=1){
		int e=i<<1,v=Pow(G,(M-1)/e);
		rt[i]=1;
		for(int j=i+1;j<e;++j)rt[j]=(ll)rt[j-1]*v%M;
	}
	NTT(a,G),NTT(b,G),invl=Pow(l,M-2);
	for(register int i=0;i<l;++i)a[i]=(ll)a[i]*b[i]%M;
	std::reverse(a+1,a+l),NTT(a,invG);
	for(register int i=0;i<n+m-1;++i)printf("%d ",(ll)a[i]*invl%M);
	return 0;
}
