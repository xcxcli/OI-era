#include<stdio.h>
#ifndef _poly
#define _poly "v0.1.0"
#define _poly_author "xcx"
#include<vector>
namespace poly_tool{
using std::vector;
typedef long long ll;
typedef vector<int> Vi;
int M=998244353,G=3,invG=332748118,inv2=499122177;Vi r,rt;
inline int down(register int x){return x<M?x:x-M;}
inline int up(register int x){return x<0?x+M:x;}
inline int nega(register int x){return x?M-x:0;}
inline int add(register int x,register int y){x+=y;return x<M?x:x-M;}
inline int sub(register int x,register int y){x-=y;return x<0?x+M:x;}
inline void vadd(register int&x,register int y){x+=y,x=x<M?x:x-M;}
inline void vsub(register int&x,register int y){x-=y,x=x<0?x+M:x;}
inline int Max(register int x,register int y){return x>y?x:y;}
inline int Min(register int x,register int y){return x<y?x:y;}
inline int Pow(register int x,register int a){
	int s=1;
	while(a){
		if(a&1)s=(ll)s*x%M;
		x=(ll)x*x%M,a>>=1;
	}
	return s;
}
inline int Inv(register int x){return Pow(x,M-2);}
inline void setMod(register int mod,register int g){M=mod,G=g,invG=Inv(G),inv2=Inv(2);}
inline int getLen(register int l){
	register int len=1;
	while(len<l)len<<=1;
	return len;
}
}
namespace poly_{
using namespace poly_tool;
inline void initNTT(int len){
	r.resize(len),rt.resize(len),r[0]=0;
	for(register int i=1;i<len;++i)r[i]=(r[i>>1]>>1)|((i&1)?len>>1:0);
	for(int i=1;i<len;i<<=1){
		int e=i<<1,v=Pow(G,(M-1)/e);rt[i]=1;
		for(register int j=i+1;j<e;++j)rt[j]=(long long)rt[j-1]*v%M;
	}
}
struct poly{
	Vi V;
	poly(){}
	poly(const int len){V.resize(len);}
	poly(const int len,const int*x){
		V.resize(len);
		for(register int i=0;i<len;++i)V[i]=x[i];
	}
	poly(const Vi &x){
		int len=x.size();V.resize(len);
		for(register int i=0;i<len;++i)V[i]=x[i];
	}
	poly(const poly&x){
		int len=x.V.size();V.resize(len);
		for(register int i=0;i<len;++i)V[i]=x.V[i];
	}
	void print()const{
		int len=V.size();
		for(register int i=0;i<len;++i)printf("%d ",V[i]);putchar('\n');
	}
	int*toArray()const{
		int len=V.size(),*x=new int[len];
		for(register int i=0;i<len;++i)x[i]=V[i];
		return x;
	}
	size_t size()const{return V.size();}
	int operator[](const int x)const{return V[x];}
	int&operator[](const int x){return V[x];}

	poly operator+()const{return poly(*this);}
	poly&cnega(){
		int len=V.size();
		for(register int i=0;i<len;++i)V[i]=poly_tool::nega(V[i]);
		return*this;
	}
	poly nega()const{poly x(*this);x.cnega();return x;}
	poly operator-()const{poly x(*this);x.cnega();return x;}

	poly&add(const poly&x){
		int xlen=x.V.size();
		if(V.size()<xlen)V.resize(xlen);
		for(register int i=0;i<xlen;++i)vadd(V[i],x.V[i]);
		return*this;
	}
	poly cadd(const poly&x)const{return poly(*this).add(x);}
	poly&operator+=(const poly&x){return this->add(x);}
	poly operator+(const poly&x)const{return poly(*this).add(x);}

	poly&sub(const poly&x){
		int xlen=x.V.size();
		if(V.size()<xlen)V.resize(xlen);
		for(register int i=0;i<xlen;++i)vsub(V[i],x.V[i]);
		return*this;
	}
	poly csub(const poly&x)const{return poly(*this).sub(x);}
	poly&operator-=(const poly&x){return this->sub(x);}
	poly operator-(const poly&x)const{return poly(*this).sub(x);}

	poly&times(const int x){
		int len=V.size();
		for(register int i=0;i<len;++i)V[i]=(ll)V[i]*x%M;
		return*this;
	}
	poly ctimes(const int x){return poly(*this).times(x);}
	poly&operator*=(const int x){return this->times(x);}
	poly operator*(const int x)const{return poly(*this).times(x);}

	void NTT(const int f){
		int len=V.size();
		if(f)for(register int i=1,j=len-1;i<j;++i,--j)std::swap(V[i],V[j]);
		for(register int i=0;i<len;++i)if(i<r[i])std::swap(V[i],V[r[i]]);
		for(int i=1;i<len;i<<=1)
			for(int j=0;j<len;j+=(i<<1))
				for(register int k=0,t=j,v;k<i;++k,++t)
					v=(long long)rt[i+k]*V[i+t]%M,V[i+t]=up(V[t]-v),vadd(V[t],v);
	}
	poly&times(const poly&x,int lim=-1){
		poly y(x);
		int len=V.size()+y.V.size()-1,L=getLen(len),invL=Inv(L);
		V.resize(L),y.V.resize(L),initNTT(L),this->NTT(1),y.NTT(1);
		for(register int i=0;i<L;++i)V[i]=(ll)V[i]*y.V[i]%M;
		this->NTT(0);
		for(register int i=0;i<L;++i)V[i]=(ll)V[i]*invL%M;
		V.resize(lim>=0?lim:len);return*this;
	}
	poly ctimes(const poly&x,int lim=-1){return poly(*this).times(x,lim);}
	poly&operator*=(const poly&x){return this->times(x,V.size()+x.V.size()-1);}
	poly operator*(const poly&x)const{return poly(*this).times(x,V.size()+x.V.size()-1);}
};
}
using poly_::poly;
#endif
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return k;
}
int n,m;
int main(){
	freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	n=rd()+1,m=rd()+1;
	poly x(n),y(m);
	for(register int i=0;i<n;++i)x[i]=rd();
	for(register int i=0;i<m;++i)y[i]=rd();
	(x*y).print();
	return 0;
}
