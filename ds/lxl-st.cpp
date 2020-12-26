#include<stdio.h>
#include<math.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=20000001,S=100001;
int Max(int x,int y){return x>y?x:y;}
int n,m,p,pn,a[N],lg[S]={-1},t[N],l[S],r[S],v[S],lm[N],rm[N],st[S][20],L,R,bl,br;
int Query(int l,int r){
	if(l>r)return 0;
	int d=lg[r-l+1];return Max(st[l][d],st[r-(1<<d)+1][d]);
}
int main(){
	n=rd(),m=rd(),p=sqrt(n),pn=n/p,pn+=(pn*p!=n);
	for(int i=1;i<=n;++i)t[i]=(i-1)/p+1,a[i]=rd();
	for(int i=1;i<=pn;++i)r[i]=i*p,l[i]=r[i]-p+1,lg[i]=lg[i>>1]+1;
	r[pn]=n,p=0;
	for(int i=1,j=1;i<=n;++i){
		lm[i]=p=Max(p,a[i]);
		if(i==r[j])st[j++][0]=p,p=0;
	}
	for(int i=n,j=pn;i;--i){
		rm[i]=p=Max(p,a[i]);
		if(i==l[j])p=0,--j;
	}
	for(int j=1,k=2;k<=pn;++j,k<<=1)for(int i=1;i+k<=pn+1;++i)st[i][j]=Max(st[i][j-1],st[i+(k>>1)][j-1]);
	while(m--){
		L=rd(),R=rd(),bl=t[L],br=t[R];
		if(bl!=br)printf("%d\n",Max(Max(rm[L],lm[R]),Query(bl+1,br-1)));
		else{
			p=0;
			for(int i=L;i<=R;++i)p=Max(p,a[i]);
			printf("%d\n",p);
		}
	}
	return 0;
}
