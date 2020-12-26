#include<stdio.h>
#include<string.h>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
int Abs(int x){return x>0?x:-x;}
int a[15],len,L,R,f[15][15];
int dfs(int pos,int pre,bool st,bool lim){
	if(pos>len)return 1;
	if(!lim&&f[pos][pre]!=-1)return f[pos][pre];
	int ret=0,res=lim?a[len-pos+1]:9;
	for(int i=0;i<=res;++i){
		if(Abs(i-pre)<2)continue;
		if(st&&i==0)ret+=dfs(pos+1,-2,1,lim&&i==res);
		else ret+=dfs(pos+1,i,0,lim&&i==res);
	}
	if(!lim&&!st)f[pos][pre]=ret;
	return ret;
}
int part(int x){
	len=0,memset(f,-1,sizeof(f));
	while(x)a[++len]=x%10,x/=10;
	return dfs(1,-2,1,1);
}
int main(){
	L=rd(),R=rd(),printf("%d\n",part(R)-part(L-1));
	return 0;
}
