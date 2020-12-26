#include<stdio.h>
#include<string.h>
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=(k<<3)+(k<<1)+c-'0',c=getchar();
	return k*f;
}
const int N=255001,M=501;
int n,m,cnt,l[N],r[N],u[N],d[N],s[M],h[M],ans[M],row[N],col[N];
void link(int i,int j){
	++s[j],row[++cnt]=i,col[cnt]=u[cnt]=j,d[cnt]=d[j],u[d[j]]=cnt,d[j]=cnt;
	if(h[i]<0)h[i]=r[cnt]=l[cnt]=cnt;
	else r[cnt]=h[i],l[cnt]=l[h[i]],r[l[h[i]]]=cnt,l[h[i]]=cnt;
}
void remove(int c){
	r[l[c]]=r[c],l[r[c]]=l[c];
	for(int i=d[c];i!=c;i=d[i])
		for(int j=r[i];j!=i;j=r[j])
			u[d[j]]=u[j],d[u[j]]=d[j],--s[col[j]];
}
void resume(int c){
	for(int i=u[c];i!=c;i=u[i])
		for(int j=l[i];j!=i;j=l[j])
			u[d[j]]=j,d[u[j]]=j,++s[col[j]];
	r[l[c]]=c,l[r[c]]=c;
}
bool dance(int deep){
	if(r[0]==0){
		for(int i=0;i<deep;++i)printf("%d ",ans[i]);
		puts("");return 1;
	}
	int c=r[0];
	for(int i=r[0];i!=0;i=r[i])if(s[i]<s[c])c=i;
	remove(c);
	for(int i=d[c];i!=c;i=d[i]){
		ans[deep]=row[i];
		for(int j=r[i];j!=i;j=r[j])remove(col[j]);
		if(dance(deep+1))return 1;
		for(int j=l[i];j!=i;j=l[j])resume(col[j]);
	}
	resume(c);return 0;
}
int main(){
	n=rd(),m=rd();
	for(int i=0;i<=m;++i)r[i]=i+1,l[i]=i-1,u[i]=d[i]=i;
	r[m]=0,l[0]=m,cnt=m,memset(h,-1,sizeof(h));
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)if(rd())link(i,j);
	if(!dance(0))puts("No Solution!");
	return 0;
}
