#include<stdio.h>
const int N=1000001;
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
char s[N],c;int n=1,i,m,r,a[N],ans;
int main(){
	s[0]=s[1]='-',c=getchar();
	while(c>='a'&&c<='z')s[++n]=c,s[++n]='-',c=getchar();
	for(int i=1;i<n;++i){
		a[i]=r>i?Min(r-i,a[m*2-i]):1;//a[m]+m=r
		while(s[i-a[i]]==s[i+a[i]])++a[i];
		if(i+a[i]>r)r=i+a[i],m=i;
		ans=Max(ans,a[i]);
	}
	printf("%d\n",ans-1);
	return 0;
}
