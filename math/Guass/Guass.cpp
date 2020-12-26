#include<stdio.h>
#include<math.h>
int n,p;double a[103][103],t,ans[103];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)for(int j=1;j<=n+1;++j)scanf("%lf",&a[i][j]);
	for(int i=1;i<=n;++i){
		p=i;
		for(int j=i+1;j<=n;++j)if(fabs(a[j][i])>fabs(a[p][i]))p=j;
		if(fabs(a[p][i])<1e-8){puts("No Solution");return 0;}
		if(i!=p)for(int j=1;j<=n+1;++j)t=a[i][j],a[i][j]=a[p][j],a[p][j]=t;
		t=a[i][i];
		for(int j=i;j<=n+1;++j)a[i][j]/=t;
		for(int j=i+1;j<=n;++j){
			t=a[j][i];
			for(int k=i;k<=n+1;++k)a[j][k]-=t*a[i][k];
		}
	}
	ans[n]=a[n][n+1];
	for(int i=n-1;i>0;--i){
		ans[i]=a[i][n+1];
		for(int j=n;j>i;--j)ans[i]-=ans[j]*a[i][j];
	}
	for(int i=1;i<=n;++i)printf("%.2lf\n",ans[i]);
	return 0;
}