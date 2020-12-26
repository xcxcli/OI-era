#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define db double
#define P pair<db,db>
#define X first
#define Y second
const int N=100001;
int n,S[N],T,K;db s;P p[N];
P operator-(P a,P b){return{a.X-b.X,a.Y-b.Y};}
db operator*(P a,P b){return a.X*b.Y-a.Y*b.X;}
db Area(int a,int b,int c){return(p[a]-p[b])*(p[a]-p[c]);}
db F(db x){return x*x;}
db D(P a,P b){return sqrt(F(a.X-b.X)+F(a.Y-b.Y));}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%lf%lf",&p[i].X,&p[i].Y);
	sort(p,p+n),S[T=1]=1;
	for(int i=2;i<n;++i){
		while(T>0&&Area(S[T-1],S[T],i)<=0)--T;
		S[++T]=i;
	}
	K=T;
	for(int i=n-2;i>=0;--i){
		while(T>K&&Area(S[T-1],S[T],i)<=0)--T;
		S[++T]=i;
	}
	for(int i=0;i<T;++i)s+=D(p[S[i]],p[S[i+1]]);
	printf("%.2f\n",s);
	return 0;
}
