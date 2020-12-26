#ifndef _poly_
namespace _poly{
#include<string.h>
int M=998244353,G=3,invG=332748118,inv2=499122177,*r,*rt;
inline void swap(register int&x,register int&y){int t=x;x=y,y=t;}
inline int down(register int x){return x<M?x:x-M;}
inline int up(register int x){return x<0?x+M:x;}
inline int nega(register int x){return x?M-x:0;}
inline int Max(register int x,register int y){return x>y?x:y;}
inline int Min(register int x,register int y){return x<y?x:y;}
inline int Pow(register int x,register int a){
	int s=1;
	while(a){
		if(a&1)s=(long long)s*x%M;
		x=(long long)x*x%M,a>>=1;
	}
	return s;
}
inline int Inv(register int x){return Pow(x,M-2);}
inline int getLen(register int l){
	register int len=1;
	while(len<l)len<<=1;
	return len;
}
inline void initNTT(int len){
	if(r!=NULL)delete[]r,delete[]rt;
	r=new int[len],rt=new int[len],r[0]=0;
	for(register int i=1;i<len;++i)r[i]=(r[i>>1]>>1)|((i&1)?len>>1:0);
	for(register int i=0;i<len;++i)printf("%d %d\n",r[i],rt[i]);
	for(int i=1;i<len;i<<=1){
		int e=i<<1,v=Pow(G,(M-1)/e);rt[i]=1;
		for(register int j=i+1;j<e;++j)rt[j]=(long long)rt[j-1]*v%M;
	}
	for(register int i=0;i<len;++i)printf("%d %d\n",r[i],rt[i]);
}
struct poly{
	int*p,l;
	poly(register int len=0){p=new int[l=len],memset(p,0,l<<2);//printf("new %d\n",p);
	}
	poly(const poly&x){p=new int[l=x.l],memcpy(p,x.p,l<<2);//printf("new %d\n",p);
	}
	~poly(){delete[]p;//printf("delete %d\n",p);
	}
//functions
	poly&resize(int len){
		if(len==l)return*this;
		int*t=new int[len];memcpy(t,p,Min(l,len)<<2);//printf("new %d\n",t);
		if(len>l)memset(t+l,0,(len-l+1)<<2);//printf("delete %d\n",p);
		delete[]p,p=t,l=len;return*this;
	}
	void print()const{
		for(register int i=0;i<l;++i)printf("%d ",p[i]);puts("");
	}
	/*poly slice(){return poly(*this);}
	poly slice(int start){return slice(start,l);}
	poly slice(int start,int end){
		start=start<0?l+start:start,end=end<0?l+end:end;
		if(start>end)swap(start,end);
		poly y(end-start);memcpy(y.p,p+start,(end-start)<<2);
		return y;
	}*/
	poly add(const poly&x){
		if(x.l>l)this->resize(x.l);
		for(register int i=0;i<l;++i)p[i]=down(p[i]+x.p[i]);
		return*this;
	}
	poly sub(const poly&x){
		if(x.l>l)this->resize(x.l);
		for(register int i=0;i<l;++i)p[i]=up(p[i]-x.p[i]);
		return*this;
	}
	poly mul(int x){
		for(register int i=0;i<l;++i)p[i]=(long long)p[i]*x%M;
		return*this;
	}
	void NTT(bool f){
		if(f)for(register int i=1,j=l-1;i<j;++i,--j)swap(p[i],p[j]);
		for(register int i=0;i<l;++i)if(i<r[i])swap(p[i],p[r[i]]);
		for(int i=1;i<l;i<<=1)
			for(int j=0;j<l;j+=(i<<1))
				for(register int k=0,t=j,v;k<i;++k,++t)
					v=(long long)rt[i+k]*p[i+t]%M,p[i+t]=up(p[t]-v),p[t]=down(p[t]+v);
	}
	poly mul(const poly&x,int lim){
		int L=getLen(l+x.l-1);poly y=x;
		initNTT(L),this->resize(L),y.resize(L),this->NTT(true),y.NTT(true);
		this->print(),y.print();
		//for(register int i=0;i<L;++i)this->p[i]=(long long)y.p[i]*(this->p[i])%M;
		//this->NTT(false),this->resize(lim);return this->mul(Inv(L));
	}
	poly mul(const poly&x){return this->mul(x,l+x.l-1);}
	poly inv(){
		int L=getLen(l);poly g(1);g.p[0]=Inv(p[0]);
		for(register int i=2;i<=L;i<<=1){poly b=g;b.mul(2),g.mul(g,i),g=b.sub(g.mul(*this,i));}
		return*this=g.resize(l);
	}
//operators
	poly&operator=(const poly&x){
		if(&x!=this){
			//printf("delete %d\n",p);
			delete[]p,p=new int[l=x.l],memcpy(p,x.p,l<<2);//printf("new %d\n",p);
		}
		return*this;
	}
	int&operator[](int x)const{return p[x];}
	bool operator==(const poly&x)const{
		if(l!=x.l)return false;
		for(register int i=0;i<l;++i)if(p[i]!=x.p[i])return false;
		return true;
	}
	bool operator!=(const poly&x)const{
		if(l!=x.l)return true;
		for(register int i=0;i<l;++i)if(p[i]!=x.p[i])return true;
		return false;
	}
	poly operator-()const{
		poly z(l);
		for(register int i=0;i<l;++i)z.p[i]=nega(p[i]);
		return z;
	}
	poly&operator+=(const poly&x){this->add(x);return*this;}
	poly operator+(const poly&x)const{poly y=*this;y.add(x);return y;}
	poly&operator-=(const poly&x){this->sub(x);return*this;}
	poly operator-(const poly&x)const{poly y=*this;y.sub(x);return y;}
	poly&operator*=(int x){this->mul(x);return*this;}
	poly operator*(int x)const{poly y=*this;y.mul(x);return y;}
	poly&operator*=(const poly&x){this->mul(x,l+x.l-1);return*this;}
	poly operator*(const poly&x)const{poly y=*this;y.mul(x);return y;}
};
//poly operator*(int x,const poly&y){return y*x;}
inline void setMod(register int mod,register int g){M=mod,G=g,invG=Inv(G),inv2=Inv(2);}
}
inline int getMod(){return _poly::M;}
inline int getG(){return _poly::G;}
using _poly::poly;
using _poly::initNTT;
using _poly::setMod;
#define _poly_ "v0.1.0"
#define _poly_author_ "xcx"
#endif
