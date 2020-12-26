#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
#define db double
const int N=100001;
struct P{db x,y;}p[N],o;
db F(db x){return x*x;}
db D(P a,P b){return sqrt(F(a.x-b.x)+F(a.y-b.y));}
int n;db r;
void calc(P p1,P p2,P p3){
	db a=p2.y-p1.y,b=p3.y-p1.y,c=p2.x-p1.x,d=p3.x-p1.x,e=F(p2.x)+F(p2.y)-F(p1.x)-F(p1.y),f=F(p3.x)+F(p3.y)-F(p1.x)-F(p1.y);
	o=(P){(a*f-b*e)/(a*d-b*c)/2,(d*e-c*f)/(a*d-b*c)/2},r=D(o,p1);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lf%lf",&p[i].x,&p[i].y);
	random_shuffle(p+1,p+n+1),o=p[1];
	for(int i=2;i<=n;++i){
		if(D(o,p[i])<=r)continue;
		o=p[i],r=0;
		for(int j=1;j<i;++j){
			if(D(o,p[j])<=r)continue;
			o=(P){(p[i].x+p[j].x)/2,(p[i].y+p[j].y)/2},r=D(o,p[j]);
			for(int k=1;k<j;++k)if(D(o,p[k])>r)calc(p[i],p[j],p[k]);
		}
	}
	printf("%.10lf\n%.10lf %.10lf\n",r,o.x,o.y);
	return 0;
}