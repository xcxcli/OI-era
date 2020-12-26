#ifndef _poly
#define _poly "v0.1.0"
#define _poly_author "xcx"
#include<vector>
namespace poly_{
using std::vector;
typedef vector<int> V;
typedef long long ll;
int M=998244353,G=3,invG=332748118,inv2=499122177;V r,rt;
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
inline void initNTT(int len){
	r.resize(len),rt.resize(len),r[0]=0;
	for(register int i=1;i<len;++i)r[i]=(r[i>>1]>>1)|((i&1)?len>>1:0);
	for(int i=1;i<len;i<<=1){
		int e=i<<1,v=Pow(G,(M-1)/e);rt[i]=1;
		for(register int j=i+1;j<e;++j)rt[j]=(long long)rt[j-1]*v%M;
	}
}
class poly:public V{
public:
	poly(){}
	poly(const int len){this->resize(len);}
	poly(const int len,const int*x){
		this->resize(len);
		for(register int i=0;i<len;++i)(*this)[i]=x[i];
	}
	poly(const vector&x){
		int len=x.size();this->resize(len);
		for(register int i=0;i<len;++i)(*this)[i]=x[i];
	}
	void print()const{
		int len=this->size();
		for(register int i=0;i<len;++i)printf("%d ",(*this)[i]);putchar('\n');
	}
	int*toArray()const{
		int len=this->size(),*x=new int[this->size()];
		for(register int i=0;i<len;++i)x[i]=(*this)[i];
		return x;
	}

	poly operator+()const{return poly(*this);}
	poly&cnega(){
		int len=this->size();
		for(register int i=0;i<len;++i)(*this)[i]=-(*this)[i];
		return *this;
	}
	poly nega()const{poly x(*this);x.cnega();return x;}
	poly operator-()const{poly x(*this);x.cnega();return x;}

	poly&add(const poly&x){
		int len=Max(this->size(),x.size());this->resize(len);
		for(register int i=0;i<len;++i)vadd((*this)[i],x[i]);
		return*this;
	}
	poly cadd(const poly&x)const{return poly(*this).add(x);}
	poly&operator+=(const poly&x){return this->add(x);}
	poly operator+(const poly&x)const{return poly(*this).add(x);}

	poly&sub(const poly&x){
		int len=Max(this->size(),x.size());this->resize(len);
		for(register int i=0;i<len;++i)vsub((*this)[i],x[i]);
		return*this;
	}
	poly csub(const poly&x)const{return poly(*this).sub(x);}
	poly&operator-=(const poly&x){return this->sub(x);}
	poly operator-(const poly&x)const{return poly(*this).sub(x);}

	poly&times(const int x){
		int len=this->size();
		for(register int i=0;i<len;++i)(*this)[i]=(ll)(*this)[i]*x%M;
		return*this;
	}
	poly ctimes(const int x){return poly(*this).times(x);}
	poly&operator*=(const int x){return this->times(x);}
	poly operator*(const int x)const{return poly(*this).times(x);}

	void NTT(const int f){
		int len=this->size();
		if(f)for(register int i=1,j=len-1;i<j;++i,--j)std::swap((*this)[i],(*this)[j]);
		for(register int i=0;i<len;++i)if(i<r[i])std::swap((*this)[i],(*this)[r[i]]);
		for(int i=1;i<len;i<<=1)
			for(int j=0;j<len;j+=(i<<1))
				for(register int k=0,t=j,v;k<i;++k,++t)
					v=(long long)rt[i+k]*(*this)[i+t]%M,(*this)[i+t]=up((*this)[t]-v),vadd((*this)[t],v);
	}
	poly&times(const poly&x,int lim=-1){
		poly y(x);
		int len=this->size()+y.size()-1,L=getLen(len),invL=Inv(L);
		this->resize(L),y.resize(L),initNTT(L),this->NTT(1),y.NTT(1);
		for(register int i=0;i<L;++i)(*this)[i]=(ll)(*this)[i]*y[i]%M;
		this->NTT(0);
		for(register int i=0;i<L;++i)(*this)[i]=(ll)(*this)[i]*invL%M;
		this->resize(lim>=0?lim:len);return*this;
	}
	poly ctimes(const poly&x,int lim=-1){return poly(*this).times(x,lim);}
	poly&operator*=(const poly&x){return this->times(x,this->size()+x.size()-1);}
	poly operator*(const poly&x)const{return poly(*this).times(x,this->size()+x.size()-1);}
};
}
using poly_::poly;
#endif
