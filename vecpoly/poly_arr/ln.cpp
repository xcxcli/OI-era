#include<stdio.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=500001,M=998244353,G=3,invG=332748118;
int n,m=1,a[N],c[N],s[N],b[N],t[N],r[N],l,p,invl;
int Pow(int x,int a){
	int s=1;
	while(a){
		if(a&1)s=(ll)s*x%M;
		x=(ll)x*x%M,a>>=1;
	}
	return s;
}
void df(int*x,int len){
	for(int i=1;i<len;++i)x[i-1]=(ll)x[i]*i%M;
	x[len-1]=0;
}
void sf(int*x,int len){
	for(int i=len;i;--i)x[i]=(ll)x[i-1]*Pow(i,M-2)%M;
	x[0]=0;
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
	n=rd();
	for(int i=0;i<n;++i)a[i]=rd();
	inv(a,c,n),df(a,n),times(a,c,n,n),sf(a,n-1);
	for(int i=0;i<n;++i)printf("%d ",a[i]);puts("");
	return 0;
}
