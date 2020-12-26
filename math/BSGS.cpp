#include<stdio.h>
#include<math.h>
#include<string.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int M=1000003;
struct E{int v,w,nxt;}e[5000001];
int h[M],en,x,y,p;
void Insert(int x,int t){int s=x%M;e[++en]=(E){x,t,h[s]},h[s]=en;}
int Query(int x){
	for(int i=h[x%M];i;i=e[i].nxt)if(e[i].v==x)return e[i].w;
	return -1;
}
void Clear(){memset(h,0,sizeof(h)),en=0;}
int Pow(int x,int a){
	int s=1;
	while(a){
		if(a&1)s=(ll)s*x%p;
		x=(ll)x*x%p,a>>=1;
	}
	return s;
}
int BSGS(int x,int y){
	if(!x)return y?-1:1;
	if(y==1)return 0;
	int q=ceil(sqrt(x)),mi=Pow(x,q);H::cls();
	for(int i=0,t=y;i<q;++i,t=(ll)t*x%p)H::ins(t,i);
	for(int i=1,t=1,k;i<=q;++i){
		t=(ll)t*mi%p,k=H::q(t);
		if(k>=0)return ((ll)i*q-k+p)%p;
	}
	return -1;
}
int main(){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	x=rd(),y=rd(),p=rd(),printf("%d\n",BSGS(x,y));
	return 0;
}
