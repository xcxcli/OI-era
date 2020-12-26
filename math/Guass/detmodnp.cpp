#include<stdio.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
const int N=501,M=31011;
void Swap(int&x,int&y){int t=x;x=y,y=t;}
int n,a[N][N],s=1,v,ii,ij,ji,jj;
void calc(int x,int y){
	ii=jj=1,ij=ji=0;
	while(y){
		ii=(ii-x/y*ji%M+M)%M,ij=(ij-x/y*jj%M+M)%M;
		x%=y,Swap(x,y),Swap(ii,ji),Swap(ij,jj),v^=1;
	}
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd();
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)a[i][j]=rd();
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			calc(a[i][i],a[j][i]);
			for(int k=i;k<=n;++k){
				v=(a[i][k]*ii+a[j][k]*ij)%M;
				a[j][k]=(a[i][k]*ji+a[j][k]*jj)%M;
				a[i][k]=v;
			}
		}
		s=s*a[i][i]%M;
	}
	if(v&&s)s=M-s;
	printf("%d\n",s);
	return 0;
}
