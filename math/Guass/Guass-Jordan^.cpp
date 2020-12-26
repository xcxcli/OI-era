#include<stdio.h>
#include<bitset>
using namespace std;
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
int n,p;bitset<103>f[103];
int main(){
	n=rd();
	for(int i=1;i<=n;++i)for(int j=1;j<=n+1;++j)f[i][j]=rd();
	for(int i=1;i<=n;++i){
		p=i;
		for(int j=i+1;j<=n;++j)if(f[j][i]){p=j;break;}
		swap(f[i],f[p]);
		for(int j=1;j<=n;++j)if(i!=j&&f[j][i])f[j]^=f[i];
	}
	for(int i=1;i<=n;++i)printf("%d\n",p=f[i][n+1]);
	return 0;
}