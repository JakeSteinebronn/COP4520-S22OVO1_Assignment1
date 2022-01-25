#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
typedef long long ll;

// Code taken from 
// https://github.com/kth-competitive-programming/kactl/tree/main/content/number-theory
// This is a competitive programming "Hackpack" that I use regularly with open-source code.
// Here I use the Miller-Rabin Primality test. The time complexity for this is O(log(x))
// to check the primality of a single x.

typedef unsigned long long ull;
inline ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
inline ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

// Miller-rabin
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll bound = 1e8;
    bool *isComp = (bool*)calloc(bound, sizeof(bool));
    vector<ll> primes(1, 2);
    int numThreads = 8;

    auto findPrimes = [&](int start, int offset)->void{
        for(int i = start; i*i <= bound; i += offset) 
            if(isPrime(i)){
                for(int j = 2*i; j < bound; j += i) isComp[j] = 1;
            }
    };

    auto start = chrono::system_clock::now();
    vector<thread*> threads;    
    for(int i = 3; i < 3+2*numThreads; i+=2)
        threads.push_back(new thread(findPrimes, i, numThreads*2));

    for(auto th : threads) th->join();
    auto stop = chrono::system_clock::now();

    for(int i = 3; i < bound; i+=2) if(!isComp[i]) primes.push_back(i);

    ofstream out("primes.txt");

    out << "Prime-finding with " << numThreads << " threads finished in " 
         << ((chrono::duration<double>)(stop-start)).count() << " seconds" << endl
         << primes.size() << " primes < " << bound << ", which sum to " << accumulate(all(primes), 0LL) << endl
         << "The largest 10 of these are: " << endl;
    for(int i = primes.size()-10; i < primes.size(); i++) 
        out << primes[i] << " "; 
    out << endl;

    return 0;
}
