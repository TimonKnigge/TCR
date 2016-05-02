#include "../header.h"
#include "numbertheory.cpp"
ll SIZE; vector<bool> bs; vector<ll> primes, mf;// mf[i]==i when prime

void sieve(ll size = 1e6) { // call at start in main!
	SIZE = size; bs.assign(SIZE+1,1);
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}
bool is_prime(ll n) { // for N <= SIZE^2
	if (n <= SIZE) return bs[n];
	for(const auto &prime : primes)
	   	if (n % prime == 0) return false;
	return true;
}
struct Factor{ll p; ll exp;}; using FS = vector<Factor>;
FS factor(ll n) { FS fs;
	for(const auto &p: primes){ ll exp=0;
		if(n==1 || p*p > n) break;
		while(n % p == 0) n/=p, exp++;
		if(exp>0) fs.push_back({p,exp});
	}
	if (n != 1) fs.push_back({n,1});
	return fs;
}

void sieve2(ll size=1e6) {	// call at start in main!
	SIZE = size; mf.assign(SIZE+1,-1);
	mf[0] = mf[1] = 1;
	for (ll i = 2; i <= SIZE; i++) if (mf[i] < 0) {
		mf[i] = i;
		for (ll j = i * i; j <= SIZE; j += i)
			if(mf[j] < 0) mf[j] = i;
		primes.push_back(i);
	}
}
bool is_prime2(ll n) { assert(n<=SIZE); return mf[n]==n; }
FS factor2(ll n){ FS fs;
	for(; n>1; n/=mf[n])
		if(!fs.empty() && fs.back().p== mf[n]) fs.back().exp++;
		else fs.push_back({mf[n],1});
	return fs;
}

vector<ll> divisors(const FS &fs){ vector<ll> ds{1};
	ll s=1; for(auto &f:fs) s*=f.exp+1; ds.reserve(s);
	for(auto f : fs) for(auto d : ds) for(ll i=0; i<f.exp; ++i)
		ds.push_back(d*=f.p);
	return ds;
}
ll num_div(  const FS &fs) { ll d = 1;
	for(auto &f : fs) d *= f.exp+1; return d; }
ll sum_div(  const FS &fs) { ll s = 1;
	for(auto &f : fs) s *= (pow(f.p,f.exp+1)-1)/(f.p-1); return s; }
ll phi(ll n, const FS &fs) { ll p = n;
	for(auto &f : fs) p -= p/f.p; return p; }
ll ord(ll n, ll m, const FS &fs){ ll o = phi(m,fs);	// n^ord(n,m)=1 mod m
	for(auto f : factor(o)) while(f.exp-- && powmod(n,o/f.p,m)==1) o/=f.p;
	return o; }

