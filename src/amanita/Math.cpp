
#include "_config.h"
#include <stdlib.h>
#include <stdio.h>
#include <amanita/Math.h>

namespace a {

const int prime[] = {
	2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,
	131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,
	263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,
	409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
0};

const int fibonacci[] = {
	0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,
	10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,
	2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,
	165580141,267914296,433494437,701408733,1134903170,1836311903,
0};


unsigned short sqrt(unsigned long n) {
	if(n<2) return n;
	size_t l2 = 0;
	unsigned long u = n,v,u2,v2,uv2,n1;
	while(u>>=1) l2++;
	l2 >>= 1,u = 1ul<<l2,u2 = u<<l2;
	while(l2--) {
		v = 1ul<<l2;
		v2 = v<<l2;
		uv2 = u<<(l2+1);
		n1 = u2+uv2+v2;
		if(n1<=n) u += v,u2 = n1;
	}
	return (unsigned short)u;
}

unsigned long sqrt(unsigned long long n) {
	if(n<2) return n;
// unsigned long i1 = n>>32,i2 = n;
// printf("sqrt(n=%lX%lX)\n",i1,i2);
	size_t l2 = 0;
	unsigned long long u = n,v,u2,v2,uv2,n1;
	while(u>>=1) l2++;
	l2 >>= 1,u = 1ull<<l2,u2 = u<<l2;

// i1 = u>>32,i2 = u;
// printf("sqrt(l2=%d,u=%lX%08lX",l2,i1,i2);
// i1 = u2>>32,i2 = u2;
// printf(",u2=%lX%08lX)\n",i1,i2);

	while(l2--) {
		v = 1ull<<l2;
		v2 = v<<l2;
		uv2 = u<<(l2+1);
		n1 = u2+uv2+v2;
		if(n1<=n) u += v,u2 = n1;

// i1 = n>>32,i2 = n;
// printf("sqrt(l2=%d,n=%lX%08lX",l2,i1,i2);
// i1 = u>>32,i2 = u;
// printf(",u=%lX%08lX",i1,i2);
// i1 = u2>>32,i2 = u2;
// printf(",u2=%lX%08lX",i1,i2);
// i1 = v>>32,i2 = v;
// printf(",v=%lX%08lX",i1,i2);
// i1 = v2>>32,i2 = v2;
// printf(",v2=%lX%08lX",i1,i2);
// i1 = uv2>>32,i2 = uv2;
// printf(",uv2=%lX%08lX",i1,i2);
// i1 = n1>>32,i2 = n1;
// printf(",n1=%lX%08lX)\n",i1,i2);
	}
	return (unsigned long)u;
}

long ceil(double d) {
	long n = (long)d;
	return n+(d-n>0.? 1 : 0);
}

long round(double d) {
	long n = (long)d;
	return n+(d-n>=.5? 1 : 0);
}

int log10(long n) {
	int i;
	for(i=0,n/=10; n; i++) n /= 10;
	return i;
}

int log10(long long n) {
	int i;
	for(i=0,n/=10; n; i++) n /= 10;
	return i;
}

double angle(double x,double y) {
	double tan = x==0.? y : (y==0.? x : pythagoras(x,y));
	if(tan==0.) return 0.;
	return x==0.? acos(y/tan) : asin(x/tan);
}

int32_t distance(int32_t x1,int32_t y1,int32_t x2,int32_t y2) {
	int32_t x = abs(x1-x2),y = abs(y1-y2);
	return x==0? y : (y==0? x : pythagoras(x,y));
}

double distance(double x1,double y1,double x2,double y2) {
	double x = fabs(x1-x2),y = fabs(y1-y2);
	return x==0? y : (y==0? x : pythagoras(x,y));
}

double distance(double x1,double y1,double z1,double x2,double y2,double z2) {
	double d = distance(x1,y1,x2,y2),z = fabs(z1-z2);
	return d==0.? z : (z==0.? d : pythagoras(d,z));
}

long sum(long min,long max) {
	if(min==max) return min;
	if(min>max) min ^= max,max ^= min,min ^= max;
	if(min<=0 && max<=0) return -sum(-max,-min);
	return (1+max)*(max>>1)+(max&1? ((1+max)>>1) : 0)-(min>1? sum(0l,min-1) : (min<0? sum(0l,-min) : 0));
}

long sum(const char arr[],long l) {
	long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

unsigned long sum(const unsigned char arr[],long l) {
	unsigned long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

long sum(const short arr[],long l) {
	long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

unsigned long sum(const unsigned short arr[],long l) {
	unsigned long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

long sum(const int arr[],long l) {
	long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

unsigned long sum(const unsigned int arr[],long l) {
	unsigned long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

long sum(const long arr[],long l) {
	long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

unsigned long sum(const unsigned long arr[],long l) {
	unsigned long s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

double sum(const double arr[],long l) {
	double s = 0;
	while(--l>=0) s += arr[l];
	return s;
}

size_t bits(long long n) {
	size_t i = 0;
	while(n) n >>= 1,++i;
	return i;
}

long gcd(long a,long b) {
	long t;
	if(!a || !b) return a|b;
	while(b) t = b,b = a%b,a = t;
	return a;
}

long long gcd(long long a,long long b) {
	long long t;
	if(!a || !b) return a|b;
	while(b) t = b,b = a%b,a = t;
	return a;
}

long gcd(long a,long b,long &x,long &y) {
	long x1 = 0,y1 = 1,q,t;
	x = 1,y = 0;
	while(b) {
		t = b,q = a/b,b = a%b,a = t;
		t = x1,x1 = x-q*x1,x = t;
		t = y1,y1 = y-q*y1,y = t;
	}
	return a;
}

long long gcd(long long a,long long b,long long &x,long long &y) {
	long long x1 = 0,y1 = 1,q,t;
	x = 1,y = 0;
	while(b) {
		t = b,q = a/b,b = a%b,a = t;
		t = x1,x1 = x-q*x1,x = t;
		t = y1,y1 = y-q*y1,y = t;
	}
	return a;
}

long modpow(long n,long e,long m) {
	long long a = 1,b = n%m;
	while(e) {
		if(e&1) a = (a*b)%m;
		b = (b*b)%m,e >>= 1;
	}
	return (long)a;
}

long long mulmod(long long n,long long e,long long m){
	long long a = 0,b = n%m;
	while(e) {
		if(e&1) a = (a+b)%m;
		b = (b<<1)%m,e >>= 1;
	}
	return a%m;
}

long long modpow(long long n,long long e,long long m) {
	long long a = 1,b = n%m;
	while(e) {
		if(e&1) a = mulmod(a,b,m);
		b = mulmod(b,b,m),e >>= 1;
	}
	return a;
}


long long factor(long long n) {
	if(n<=2ll && n>=-2ll) return n;
	long long f = 0,p;
	int i;
	for(i=0; (p=prime[i]) && p<=n; i++) if(!(n%p)) { f = p;do n /= p;while(!(n%p)); }
	if(!p) for(p=prime[i-1]+2; p<=n; p+=2) if(!(n%p)) { f = p;do n /= i;while(!(n%p)); }
	return f;
}


static bool isprime_trial_division(long long n) {
	long long m = (long long)sqrt((unsigned long long)n)+1,i;
// printf("isprime_trial_division(n=%I64d,m=%I64d)",n,m);
	for(i=3; i<=m; i+=2) if(!(n%i)) return false;
	return true;
}

static bool isprime_fermat(long long n,int k) {
// printf("isprime_fermat(%I64d)\n",n);
	if(n<11) return isprime_trial_division(n);
	long long n1 = n-1;
	if(k<=0) k = 4;
	for(int a=0; a<k; a++) if(modpow((long long)prime[a],n1,n)!=1) return false;
	return true;
}

static bool isprime_miller_rabin(long long n,int k) {
	if(n<19) return isprime_trial_division(n);
// printf("isprime_miller_rabin(%I64d)\n",n);
	long long n1 = n-1,d = n1,d1,a,m;
	int i = 0,r,s = 0;
	if(k<=0) k = 4;
	for(; !(d&1); d>>=1,s++);
	for(i=0; i<k; i++) {
		a = prime[i];
		if(gcd(a,n)!=1) return false;
		m = modpow(a,d,n);
		if(m==1) return true;//continue;
// printf("n1=%I64d,i=%d,d=%I64d,s=%d,a=%I64d,m=%I64d\n",n1,i,d,s,a,m);
		for(r=0,d1=d<<1; ; r++,d1<<=1) {
// printf("r=%d,d1=%I64d,m=%I64d\n",r,d1,m);
			if(m==n1) break;
			else if(r==s-1) return false;
			m = modpow(a,d1,n);
		}
	}
	return true;
}

/* Not implemented. Too slow.
bool isprime_Lucas(long long n,int k) {
// printf("isprime_Lucas(%I64d)\n",n);
	int i = 0,p = 0,a = 0,s = 5,r = 0,qn = 0;
	long long n1 = n-1,f = n1,q = 0,m = 0,*_q = (long long *)malloc(s*sizeof(long long));
	do {
		if(q*q>=f) q = f;
		else {
			do q = prime[a]? prime[a++] : q+2;while((f%q) && q<=f);
			do f /= q;while(!(f%q));
		}
// printf("q=%I64d,f=%I64d\n",q,f);
		if(i==s) s <<= 1,_q = (long long *)realloc(_q,s*sizeof(long long));
		_q[i++] = q,qn++;
	} while(q<f);

	if(k<=0) k = 4;
	for(a=2; a<n; a++) {
		if(modpow(a,n1,n)==1) {
			for(p++,i=0,r=0; i<qn; i++) {
				m = modpow(a,n1/_q[i],n);
// printf("n=%I64d,n1=%I64d,f=%I64d,q=%I64d,a=%d,n1/q=%I64d = %I64d\n",n,n1,f,_q[i],a,n1/_q[i],m);
				if(m!=1) r++;
				else if(r) break;
			}
			if(r==qn) return true;
		}
	}
	return false;
}*/

/** Not implemented.
bool isprime_Baillie_PSW(unsigned long n) {
	unsigned long n1 = n-1,d = n1,d1,a;
	int r,s = 0;
	while(!(d&1)) d >>= 1,s++;
	if(modpow(2ul,d,n)!=1) {
		for(r=0,d1=d; r<s; r++,d<<=1) if(modpow(2ul,d1,n)==n1) break;
		if(r==s) goto baillie_psw_test2;
	}
	return true;
baillie_psw_test2:
	
}*/

/** Not implemented.
bool isprime_Solovay_Strassen(unsigned long n) {
}*/

/** Not implemented. Is slower than isprime_trial_division, so, it has no real use.
bool isprime_AKS(long long n) {
	long long q,r,s,m,log2n = (long long)(log(n)/log(2));
	s = sqrt((unsigned long long)n);
	if(s*s==n) return false;
	if(n<11813ll) return isprime_trial_division(n);
	for(r=3ll; r<n; r+=2ll) {
		if(isprime_trial_division(r)) {
			if(!(m=(n%r))) return false;
			q = factor(r-1ll);
			if(modpow(m,(r-1ll)/q,r)<=1ll) continue;
			if(q>=4ll*sqrt((unsigned long long)r)*log2n) {printf("[%I64d]",r);return true;}
		}
	}
	return false;
}*/

bool isprime(long long n,int a,int k) {
//printf("isprime(%lu)\n",n);
	//if(n<k*k) return _isprime(n);
	if(n<0) n = -n;
	if(n<2 || (n>3 && !(n&1))) return false;
	if(n<4) return true;
	if(a==1) return isprime_fermat(n,k);
	if(a==2) return isprime_miller_rabin(n,k);
	//if(a==3) return isprime_Lucas(n,k);
	//if(a==4) return isprime_AKS(n);
	return isprime_trial_division(n);
}


long long prevprime(long long n) {
	if(n<0) n = -n;
	if(n<3) return 0;
	if(n&1) --n;
	if(n>2) for(--n; n>2; n-=2) if(/*isprime_fermat(n,4) && */isprime_trial_division(n)) return n;
	return 2;
}

long long nextprime(long long n) {
// printf("nextPrime\n");
	if(n<0) n = -n;
	if(n<2) return 2;
	if(n==2) return 3;
	if(n<0x7ffffffffffffffell && (n&1)) ++n;
	for(++n; n<0x7ffffffffffffffell; n+=2) if(/*isprime_fermat(n,4) && */isprime_trial_division(n)) return n;
	return 0;
}

}; /* namespace a */



