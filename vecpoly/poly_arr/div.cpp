#include<stdio.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=500001,M=998244353,G=3,invG=332748118;
int n,q,z,m=1,f[N],g[N],a[N],c[N],d[N],b[N],t[N],r[N],l,p,invl;
int Pow(int x,int a){
	int s=1;
	while(a){
		if(a&1)s=(ll)s*x%M;
		x=(ll)x*x%M,a>>=1;
	}
	return s;
}
void rev(int*x,int len){for(int i=0;i<(len>>1);++i)p=x[i],x[i]=x[len-i-1],x[len-i-1]=p;}
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
void times(int*x,int*y,int len,int lim){
	l=1;
	while(l<(len<<1))l<<=1;
	for(int i=0;i<len;++i)t[i]=y[i];
	for(int i=len;i<l;++i)t[i]=0;
	for(int i=0;i<l;++i)r[i]=(r[i>>1]>>1)|((i&1)?l>>1:0);
	NTT(x,G),NTT(t,G),invl=Pow(l,M-2);
	for(int i=0;i<l;++i)x[i]=(ll)x[i]*t[i]%M;
	NTT(x,invG);
	for(int i=0;i<lim;++i)x[i]=(ll)x[i]*invl%M;
	for(int i=lim;i<l;++i)x[i]=0; 
}
void inv(int*f,int*g,int len){
	while(m<len)m<<=1;
	for(int i=0;i<len;++i)g[i]=b[i]=0;
	g[0]=Pow(f[0],M-2);
	for(int i=2;i<=m;i<<=1){
		for(int j=0;j<(i>>1);++j)b[j]=(g[j]<<1)%M;
		times(g,g,i>>1,i),times(g,f,i,i);
		for(int j=0;j<i;++j)g[j]=(b[j]-g[j]+M)%M;
	}
	for(int i=len;i<m;++i)g[i]=0;
}
int main(){
	n=rd()+1,q=rd()+1,z=n-q+1;
	for(int i=0;i<n;++i)f[i]=rd();
	rev(f,n);
	for(int i=0;i<z;++i)a[i]=f[i];
	rev(f,n);
	for(int i=0;i<q;++i)g[i]=rd();
	rev(g,q);
	for(int i=0;i<z;++i)d[i]=g[i];
	rev(g,q),inv(d,c,z),times(a,c,z,z),rev(a,z);
	for(int i=0;i<z;++i)printf("%d ",a[i]);puts("");
	times(a,g,n,q);
	for(int i=0;i<q-1;++i)a[i]=(f[i]-a[i]+M)%M;
	for(int i=0;i<q-1;++i)printf("%d ",a[i]);puts("");
	return 0;
}
