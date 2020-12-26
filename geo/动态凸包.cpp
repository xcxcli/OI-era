#include<stdio.h>
#include<math.h>
#include<set>
using namespace std;
#define pi pair<int,int>
#define X first
#define Y second
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=1000001;
pi operator-(pi a,pi b){return{b.X-a.X,b.Y-a.Y};}
int operator*(pi a,pi b){return a.X*b.Y-a.Y*b.X;}
int Area(pi a,pi b,pi c){return(a-b)*(a-c);}
double Abs(pi a){return sqrt(a.X*a.X+a.Y*a.Y);}
int n,x,y,m,Q;pi p[N],q[N<<1];bool f[N];set<pi>S;set<pi>::iterator t,l,r;double s,ans[N<<1];
void Insert(pi u){
	l=r=S.lower_bound(u),--l;
	if(Area(*l,u,*r)>=0)return;
	s-=Abs(*l-*r);
	while(r!=S.end()){
		t=r,++r;
		if(r==S.end()||Area(u,*t,*r)<0)break;
		s-=Abs(*t-*r),S.erase(t);
	}
	while(l!=S.begin()){
		t=l,--l;
		if(Area(*l,*t,u)<0)break;
		s-=Abs(*t-*l),S.erase(t);
	}
	S.insert(u),l=r=S.find(u),--l,++r,s+=Abs(*l-u)+Abs(*r-u);
}
int main(){
	
	return 0;
}
