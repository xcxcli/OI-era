#include<stdio.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=100001;
int n,m,o,x,y,l[N],r[N],f[N],d[N],v[N];
int F(int a){
	while(a!=f[a])a=f[a];
	return a;
}
void Swap(int&a,int&b){int t=a;a=b,b=t;}
int Merge(int a,int b){
	if(!a||!b)return a+b;
	if(v[a]>v[b]||v[a]==v[b]&&a>b)Swap(a,b);
	r[a]=Merge(r[a],b),f[r[a]]=a;
	if(d[l[a]]==0||d[l[a]]<d[r[a]])Swap(l[a],r[a]);
	d[a]=d[r[a]]+1;return a;
}
int main(){
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)v[i]=rd(),f[i]=i;
	while(m--){
		o=rd(),x=rd();
		if(o==1){
			y=rd();
			if(v[x]<0||v[y]<0)continue;
			x=F(x),y=F(y);
			if(x!=y)Merge(x,y);
		}
		else{
			if(v[x]<0)puts("-1");
			else x=F(x),printf("%d\n",v[x]),v[x]=-1,f[l[x]]=l[x],f[r[x]]=r[x],Merge(l[x],r[x]);
		}
	}
	return 0;
}