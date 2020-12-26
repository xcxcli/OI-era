#include<stdio.h>
#include<math.h>
#include<algorithm>
#define db double
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return f?k:-k;
}
const int N=502;
struct P{
	db x,y;
	P operator+(const P&a)const{return{x+a.x,y+a.y};}
	P operator-(const P&a)const{return{x-a.x,y-a.y};}
	P operator*(const db&a)const{return{x*a,y*a};}
	db operator*(const P&a)const{return x*a.y-y*a.x;}
	db k(){return atan2(y,x);}
}a[52],e[N];
db Area(const P&a,const P&b,const P&c){return(a-c)*(b-c);}
struct L{
	P a,b;db k;
	bool operator<(const L&c)const{return k==c.k?Area(a,c.b,b)>0:k<c.k;}
	P operator*(const L&c)const{P u=c.b-c.a,v=b-a;return v*((u*(a-c.a))/(v*u))+a;}
}p[N],q[N];
bool ok(const L&a,const L&b,const L&c){return Area(a*b,c.b,c.a)>0;}
int pn,n=1,L=1,R=2;db ans;
int main(){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	
	std::sort(p+1,p+pn+1);
	for(int i=2;i<=pn;++i)if(p[i].k!=p[i-1].k)p[++n]=p[i];
	q[1]=p[1],q[2]=p[2];
	for(int i=3;i<=n;++i){
		while(L<R&&ok(q[R-1],q[R],p[i]))--R;
		while(L<R&&ok(q[L+1],q[L],p[i]))++L;
		q[++R]=p[i];
	}
	while(L<R&&ok(q[R-1],q[R],q[L]))--R;
	while(L<R&&ok(q[L+1],q[L],q[R]))++L;
	n=0;
	for(int i=L;i<=R;++i)e[++n]=q[i]*q[i==R?L:i+1];
	if(n<3){puts("0.000");return 0;}
	for(int i=1;i<=n;++i)ans+=e[i]*e[i==n?1:i+1];
	printf("%.3f\n",ans/2);
	return 0;
}
