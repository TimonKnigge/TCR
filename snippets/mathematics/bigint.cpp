#include "../header.h"
using ll = long long;

class BI{
public:
	static const ll B = 10, P = 9, M = 1e9;		// base, power, mod
	vector<ll> v;			// number
	ll sign;				// {-1,1}
	BI() : v(), sign(1) {}
	BI(ll n) : BI() {
		sign = n>0 ? 1 : -1;
		while(n) v.push_back(n%M), n/=M;
	}
	BI(string s) : BI() { // string should be represented in base `base`
		sign = s[0]=='-' ? -1 : 1;
		auto it = s.rbegin();
		while(it != s.rend() && *it != '-'){
			ll cur = 0;
			ll pow = 1;
			REP(i,P){
				if(it == s.rend() || *it == '-'){
					v.push_back(cur); return;
				}
				cur += (*it - '0') * pow;
				pow *= B;
				it++;
			}
			v.push_back(cur);
		}
	}
	string tostring(){
		shrink();
		if(v.size() == 0) return "0";
		string s;
		if(sign < 0) s = '-';
		for(auto it = v.rbegin(); it!=v.rend(); it++){
			string x = to_string(*it);
			if(it!=v.rbegin()) s += string(P-x.size(),'0');
			//s += '\'';
			s += x;
		}
		return s;
	}
	void shrink(){
		int i = v.size()-1;
		while(i >= 0 && v[i] == 0) i--;
		v.erase(v.begin() + i+1, v.end());
		if(v.size()==0) sign=1;
	}

	bool compare_abs(const BI &r) const{
		if(r.v.size() != v.size()) // assume reduced input
			return (v.size() < r.v.size());
		else
			for(int i = v.size()-1; i>=0; i--)
				if(v[i] != r.v[i]){
					return (v[i] < r.v[i]);
				}
		return false;
	}

	bool operator<(const BI &r) const{
		if(sign!=r.sign) return sign < 0;
		return (sign < 0) ^ compare_abs(r);
	}

	BI &operator+=(BI r){
		auto op = sign * r.sign; // -1 for subtraction
		if(op < 0 && compare_abs(r)) sign *=-1, swap(*this, r);
		v.resize(max(v.size(),r.v.size())+1,0);
		ll carry = 0;
		REP(i, r.v.size()){
			v[i] += op*(r.v[i] + carry);
			carry = op > 0 ? v[i] >= M : v[i] < 0;
			v[i] -= op*(carry * M);
		}
		if(carry) v[r.v.size()]+= op * carry;

		shrink();
		return *this;
	}

	BI &operator-=(const BI &r){
		sign *=-1; *this+=r; sign*=-1; return *this;
	}
	// just O(d^2) multiplication
	BI operator*(const BI &r) const{
		BI w; w.sign = sign * r.sign;
		w.v.resize(v.size() + r.v.size(),0);
		REP(i,v.size())
			REP(j,r.v.size()){
				w.v[i+j] += v[i] * r.v[j];
				auto carry = w.v[i+j]/M;
				w.v[i+j] -= M*carry, w.v[i+j+1]+=carry;
			}
		w.shrink();
		return w;
	}
	BI operator+(const BI &r) const{
		BI a = *this; a += r; return a;
	}
	BI operator-(const BI &r) const{
		BI a = *this; a -= r; return a;
	}
	BI operator*=(const BI &r){
		*this = (*this) * r;
		return *this;
	}
};

#include <random>
#include <chrono>

mt19937_64 rng;

int main(){
	rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
	auto start = chrono::high_resolution_clock::now();
	REP(i,10000){
		string a,b,c;
		int l1 = rng() % 1000, l2 = rng() % 1000, l3 = rng() % 1000;
		REP(j,l1) a.push_back('0'+(rng() % 10));
		REP(j,l2) b.push_back('0'+(rng() % 10));
		REP(j,l3) c.push_back('0'+(rng() % 10));
		BI x(a), y(b), z(c);
		//cout << x.tostring() << endl << y.tostring() << endl << z.tostring();
		auto r = (x - y) + (y - z) + (z - x);
		if(r.tostring()!="0"){
			cout << r.tostring() << endl;
		}
	}
	cout << "time: " << (chrono::high_resolution_clock::now() - start).count() << endl;

}
