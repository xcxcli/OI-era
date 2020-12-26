#include<stdio.h>
#include<string.h>
const int N=500001;
char s[N];int n,m,rk[N],sa[N],tax[N],tp[N],h[N],p;
void Sort(){
	memset(tax,0,sizeof(tax));
	for(int i=1;i<=n;++i)++tax[rk[i]];
	for(int i=1;i<=m;++i)tax[i]+=tax[i-1];
	for(int i=n;i;--i)sa[tax[rk[tp[i]]]--]=tp[i];
}
int main(){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;++i)rk[i]=s[i],m=m>rk[i]?m:rk[i],tp[i]=i;
	Sort();
	for(int k=1;p<n;k<<=1,m=p){
		p=0;
		for(int i=1;i<=k;++i)tp[++p]=n-k+i;
		for(int i=1;i<=n;++i)if(sa[i]>k)tp[++p]=sa[i]-k;
		Sort(),memcpy(tp,rk,sizeof(tp)),rk[sa[1]]=p=1;
		for(int i=2;i<=n;++i)rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+k]==tp[sa[i-1]+k])?p:++p;
	}
	for(int i=1,j,k=0;i<=n;++i){
		if(k)--k;
		j=sa[rk[i]-1];
		while(s[i+k]==s[j+k])++k;
		h[rk[i]]=k;
	}
	for(int i=1;i<=n;++i)printf("%d ",sa[i]);
	puts("");
	for(int i=1;i<=n;++i)printf("%d ",h[i]);
	puts("");
	for(int i=1;i<=n;++i)printf("%d ",h[rk[i]]);
	puts("");
	return 0;
}
