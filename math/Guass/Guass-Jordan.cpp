#include<stdio.h>
#include<math.h>
int n,p;double f[103][103],t;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)for(int j=1;j<=n+1;++j)scanf("%lf",&f[i][j]);
	for(int i=1;i<=n;++i){
		p=i;
		for(int j=i;j<=n;++j)if(fabs(f[j][i])>fabs(f[p][i]))p=j;
		if(fabs(f[p][i])<1e-8){puts("No Solution");return 0;}
		if(p!=i)for(int j=1;j<=n+1;++j)t=f[i][j],f[i][j]=f[p][j],f[p][j]=t;
		for(int j=i+1;j<=n+1;++j)f[i][j]/=f[i][i];
		for(int j=1;j<=n;++j)if(i!=j)for(int k=i+1;k<=n+1;++k)f[j][k]-=f[j][i]*f[i][k];
	}
	for(int i=1;i<=n;++i)printf("%.2lf\n",f[i][n+1]);
	return 0;
}
