#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
int _,N,M,t,w;
int Pow(int x,int a){
	int s=1;
	while(a){
		if(a&1)s=(ll)s*x%M;
		x=(ll)x*x%M,a>>=1;
	}
	return s;
}
struct Com{int x,y;};
Com operator*(const Com&a,const Com&b){return(Com){(int)(((ll)a.x*b.x+(ll)a.y*b.y%M*w)%M),(int)(((ll)a.x*b.y+(ll)a.y*b.x)%M)};}
Com Pow(Com x,int a){
	Com s={1,0};
	while(a){
		if(a&1)s=s*x;
		x=x*x,a>>=1;
	}
	return s;
}
int Calc(int n){
	if(Pow(n,t)+1==M)return -1;
	int a;
	while(1){
		a=rand(),w=((ll)a*a-n+M)%M;
		if(Pow(w,t)+1==M)break;
	}
	return Pow((Com){a,1},t+1).x;
}
int main(){
	freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	_=rd();
	while(_--){
		N=rd(),M=rd(),t=(M-1)>>1;
		if(!N){puts("0");continue;}
		N=Calc(N);
		if(N<0){puts("No Solution!");continue;}
		if((N<<1)<M)printf("%d %d\n",N,M-N);
		else printf("%d %d\n",M-N,N);
	}
	return 0;
}
