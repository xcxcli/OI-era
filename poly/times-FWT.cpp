#include<stdio.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=1000001,M=998244353,inv2=499122177;
int n,m,a[N],b[N],c[N],d[N];
void OR(int*x,int f){
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=j;k<i+j;++k)
				x[k+i]=((x[i+k]+x[k]*f)%M+M)%M;
}
void AND(int*x,int f){
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=j;k<i+j;++k)
				x[k]=((x[k]+x[i+k]*f)%M+M)%M;
}
void XOR(int*x,int f){
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=j;k<i+j;++k){ 
				x[k]=(x[k]+x[i+k])%M,x[i+k]=(x[k]-(x[i+k]<<1)%M+M)%M;
				if(f<0)x[k]=(ll)x[k]*inv2%M,x[i+k]=(ll)x[i+k]*inv2%M; 
			}
}
void FWT_OR(int*f,int*g){
	for(int i=0;i<n;++i)c[i]=f[i],d[i]=g[i];
	OR(c,1),OR(d,1);
	for(int i=0;i<n;++i)c[i]=(ll)c[i]*d[i]%M;
	OR(c,-1);
	for(int i=0;i<n;++i)printf("%d ",c[i]);puts("");
}
void FWT_AND(int*f,int*g){
	for(int i=0;i<n;++i)c[i]=f[i],d[i]=g[i];
	AND(c,1),AND(d,1);
	for(int i=0;i<n;++i)c[i]=(ll)c[i]*d[i]%M;
	AND(c,-1);
	for(int i=0;i<n;++i)printf("%d ",c[i]);puts("");
}
void FWT_XOR(int*f,int*g){
	for(int i=0;i<n;++i)c[i]=f[i],d[i]=g[i];
	XOR(c,1),XOR(d,1);
	for(int i=0;i<n;++i)c[i]=(ll)c[i]*d[i]%M;
	XOR(c,-1);
	for(int i=0;i<n;++i)printf("%d ",c[i]);puts("");
}
int main(){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	n=1<<rd();
	for(int i=0;i<n;++i)a[i]=rd();
	for(int i=0;i<n;++i)b[i]=rd();
	FWT_OR(a,b),FWT_AND(a,b),FWT_XOR(a,b);
	return 0;
}
