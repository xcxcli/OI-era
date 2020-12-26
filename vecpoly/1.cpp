#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int R(int x){return rand()%x+1;}
int n=100000,m=100000;
int main(){
	freopen("data.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,m);
	for(int i=0;i<=n;++i)printf("%d ",rand()*rand());puts("");
	for(int i=0;i<=n;++i)printf("%d ",rand()*rand());puts("");
	return 0;
}
