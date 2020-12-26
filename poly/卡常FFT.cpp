#include<stdio.h>
#include<math.h>
#include<algorithm>
typedef double db;
#define ri register int
#define N 2100001
const db pi=3.1415926535897932384;
inline int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
struct Com{db x,y;}a[N],p,rt[N];
inline Com operator+(const Com&a,const Com&b){return(Com){a.x+b.x,a.y+b.y};}
inline Com operator-(const Com&a,const Com&b){return(Com){a.x-b.x,a.y-b.y};}
inline Com operator*(const Com&a,const Com&b){return(Com){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
int n,m,len,l=1,r[N];
inline void FFT(){
	for(ri i=0;i<l;++i)if(i<r[i])std::swap(a[i],a[r[i]]);
	for(int i=1;i<l;i<<=1)
		for(ri j=0;j<l;j+=(i<<1))
			for(ri k=0,t=j;k<i;++t,++k)
				p=rt[i+k]*a[i+t],a[i+t]=a[t]-p,a[t]=a[t]+p;
}
int main(){
	freopen("data.in","r",stdin);
	freopen("vali.out","w",stdout);
	n=rd(),m=rd(),len=n+m-1;
	for(ri i=0;i<n;++i)a[i].x=(int)rd();
	for(ri i=0;i<m;++i)a[i].y=(int)rd();
	while(l<len)l<<=1;
	for(ri i=0;i<l;++i)r[i]=(r[i>>1]>>1)|((i&1)?l>>1:0);
	for(int i=1;i<l;i<<=1){
		int e=i<<1;Com v={cos(pi/i),sin(pi/i)};
		rt[i]={1,0};
		for(int j=i+1;j<e;++j)rt[j]=rt[j-1]*v;
	}
	FFT();
	for(ri i=0;i<l;++i)a[i]=a[i]*a[i];
	std::reverse(a+1,a+l),FFT();
	for(ri i=0;i<len;++i)printf("%d ",(int)(a[i].y/l/2+0.5));
	return 0;
}
