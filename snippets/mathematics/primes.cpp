#include "../header.h"
#include "numbertheory.cpp"
ll SIZE;
vector<bool> bs;
vector<ll> primes;

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

struct Factor{ll prime; ll exp;}; using Fs = vector<Factor>;
Fs factor(ll n) {
	Fs factors;
	for(const auto &prime : primes){
		if(n==1 || prime*prime > n) break;
		ll exp=0;
		while(n % prime == 0)
		   	n/=prime, exp++;
		if(exp>0)
			factors.push_back({prime,exp});
	}
	if (n != 1) factors.push_back({n,1});
	return factors;
}

vector<ll> divisors(const Fs &fs){
	vector<ll> ds{1};
	ds.reserve(accumulate(fs.begin(),fs.end(),1,
		[](ll a,auto f){return a*(f.exp+1);}));
	for(auto f : fs) for(auto d : ds) for(ll i = 0; i < f.exp; ++i)
				ds.push_back(d*=f.prime);
	return ds;
}

vector<ll> mf;				// mf[i]==i when prime
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
Fs factor2(ll n){
	Fs factors;
	while(n>1){
		if(!factors.empty() && factors.back().prime == mf[n])
			factors.back().exp++;
		else factors.push_back({mf[n],1});
		n/=mf[n];
	}
	return factors;
}

ll num_div(  const Fs &fs) { ll d = 1;
	for(auto &f : fs) d *= f.exp+1; return d; }
ll sum_div(  const Fs &fs) { ll s = 1;
	for(auto &f : fs) s *= (pow(f.prime,f.exp+1)-1)/(f.prime-1); return s; }
ll phi(ll n, const Fs &fs) { ll p = n;
	for(auto &f : fs) p -= p/f.prime; return p; }

vector<ll> test_primes = {2,3,5,7,11,13,17,19,23};	// <= 3.8e18
vector<ll> test_primes2= {2,13,23,1662803};			// <= 1.1e12
//using ll = __int128
bool miller_rabin(const ll n){	// true when prime
	if(n<2) return false;		
	if(n%2==0) return n==2;
	ll s = 0, d = n-1; // n-1 = 2^s * d
	while(~d&1) s++, d/=2;
	for(auto a : test_primes){
		if(a > n-2) break;
		ll x = powmod(a,d,n);
		if(x == 1 || x == n-1) continue;
		REP(i,s-1){
			x = x*x%n;
			if(x==1) return false;
			if(x==n-1) goto next_it;
		}
		return false;
next_it:;
	}
	return true;
}
