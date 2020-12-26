#include<stdio.h>
#include"poly.h"
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
int n,m;
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd()+1,m=rd()+1;
	poly x(n),y(m);
	for(register int i=0;i<n;++i)x[i]=rd();
	for(register int i=0;i<m;++i)y[i]=rd();
	(x*y).print();
	return 0;
}
