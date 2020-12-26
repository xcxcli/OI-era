#include<stdio.h>
#include<bitset>
using namespace std;
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
int n,p;bitset<103>a[103];bool ans[103];
int main(){
	n=rd();
	for(int i=1;i<=n;++i)for(int j=1;j<=n+1;++j)a[i][j]=rd();
	for(int i=1;i<=n;++i){
		p=i;
		for(int j=i+1;j<=n;++j)if(a[j][i]){p=j;break;}
		swap(a[i],a[p]);
		for(int j=i+1;j<=n;++j)if(a[j][i])a[j]^=a[i];
	}
	ans[n]=a[n][n+1];
	for(int i=n-1;i;--i){
		ans[i]=a[i][n+1];
		for(int j=i+1;j<=n;++j)if(a[i][j])ans[i]^=ans[j];
	}
	for(int i=1;i<=n;++i)printf("%d\n",ans[i]);
	return 0;
}