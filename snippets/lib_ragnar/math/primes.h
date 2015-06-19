#include <bitset>
#include <vector>
using namespace std;
using ll = long long;
constexpr ll SIZE = 1e6;
bitset<SIZE+1> bs;
vector<ll> primes;

void sieve() { // call at start in main!
	bs.set();                                           
	bs[0] = bs[1] = 0;                                    
	for (ll i = 2; i <= SIZE; i++) if (bs[i]) {
		for (ll j = i * i; j <= SIZE; j += i) bs[j] = 0;
		primes.push_back(i);
	}
}                                         

bool isPrime(ll n) { // for N <= SIZE^2
	if (n <= SIZE) return bs[n];                   
	for(const auto& prime : primes)
	   	if (n % prime == 0) return false;
	return true;            
}

struct Factor{ll prime; ll exp;};
vector<Factor> factor(ll n) {
	vector<Factor> factors;
	for(const auto& prime : primes){
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

ll numDiv(ll n) {
	ll divisors = 1;
	for(auto&& p : factor(n))
		divisors *= p.exp + 1;
	return divisors;
}

ll pow(ll b, ll e){
	ll p = e==0 ? 1 : pow(b*b,e>>1);
	return p * p * (e&1 ? b : 1);
}

ll sumDiv(ll n) {
	ll sum = 1;
	for(const auto& p : factor(n))
		sum *= (pow(p.prime, p.exp+1) - 1) / (p.prime - 1);
	return sum;
}

ll EulerPhi(ll n) {
	ll ans = n;
	for(const auto& p : factor(n))
		ans -= ans / p.prime;
	return ans;
}
