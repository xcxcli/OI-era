#include<stdio.h>
#include<math.h>
#define db double
const db pi=acos(-1.0);const int N=2100001;
struct Com{db x,y;Com(db a=0,db b=0){x=a,y=b;}}a[N],p;
Com operator+(const Com&a,const Com&b){return Com(a.x+b.x,a.y+b.y);}
Com operator-(const Com&a,const Com&b){return Com(a.x-b.x,a.y-b.y);}
Com operator*(const Com&a,const Com&b){return Com(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
int n,m,l=1,r[N],v;
void FFT(Com*x,int f){
	for(int i=0;i<l;++i)if(i<r[i])p=x[i],x[i]=x[r[i]],x[r[i]]=p;
	for(int i=1;i<l;i<<=1){
		Com T(cos(pi/i),sin(pi/i)*f);
		for(int j=0;j<l;j+=(i<<1)){
			Com t(1,0);	
			for(int k=j;k<i+j;++k,t=t*T)p=t*x[i+k],x[i+k]=x[k]-p,x[k]=x[k]+p;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)scanf("%d",&v),a[i].x=v;
	for(int i=0;i<m;++i)scanf("%d",&v),a[i].y=v;
	while(l<n+m-1)l<<=1;
	for(int i=0;i<l;++i)r[i]=(r[i>>1]>>1)|((i&1)?l>>1:0);
	FFT(a,1);
	for(int i=0;i<l;++i)a[i]=a[i]*a[i];
	FFT(a,-1);
	for(int i=0;i<n+m-1;++i)printf("%d ",(int)(a[i].y/l/2+0.5));
	puts("");
	return 0;
}
