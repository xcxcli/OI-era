#include<stdio.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=20000001; 
int n,m,s,a[N],l[N],r[N],S[10000],T,L,R,x;
int main(){
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=n;++i){
		while(T&&a[S[T]]<=a[i])l[i]=S[T--];
		r[S[T]]=i,S[++T]=i;
	}
	while(m--){
		L=rd(),R=rd();
		if(L>R)x=L,L=R,R=x;
		x=S[1];
		while(L>x||R<x)x=R<x?l[x]:r[x];
		printf("%d\n",a[x]);
	}
	return 0;
}
