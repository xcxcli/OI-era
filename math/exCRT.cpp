#include<stdio.h>
#define ll long long
ll rd(){
	ll k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
int n;ll a,b,c,d,x,y,m,ans,t;
ll Mul(ll x,ll y,ll p){
	ll L=(x*(b>>25)%p<<25)%p;
	ll R=x*(b&((1<<25)-1))%p;
	return (L+R)>>1;
}
void exgcd(ll a,ll b){
	if(!b){x=1,y=0,d=a;return;}
	exgcd(b,a%b);ll z=x;x=y,y=z-a/b*y;
}
int main(){
	n=rd(),m=rd(),ans=rd();
	for(int i=1;i<n;++i){
		b=rd(),a=rd(),c=(a-ans%b+b)%b,exgcd(m,b);
		if(c%d){puts("No Solution");return 0;}
		ans+=m*Mul(x,c/d,b),m*=b/d,ans=(ans+m)%m;
	}
	printf("%lld\n",ans);
	return 0;
}
