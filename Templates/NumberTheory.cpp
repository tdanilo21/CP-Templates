#define ll long long
namespace NumberTheory{
    vector<int> sito, primes;
    bool _precomputed_sito_ = 0;
    ll gcd(ll a, ll b){ if (!b) return a; return gcd(b, a % b); }
    void PrecomputeSito(const int mx){
        _precomputed_sito_ = 1;
        sito = vector<int>(mx+10);
        for (int i = 2; i < mx; i++)
            sito[i] = i;
        for (ll i = 2; i < mx; i++)
            if (sito[i] == i)
                for (ll j = i*i; j < mx; j += i)
                    sito[j] = i;
    }
    bool IsPrime(int x){
        if (_precomputed_sito_) return sito[x] == x;
        if (x <= 1) return 0;
        for (int i = 2; i*i <= x; i++)
            if (x % i == 0)
                return 0;
        return 1;
    }
    void GetPrimes(){
        if (!_precomputed_sito_){
            cerr << "Precompute sito u idiot." << endl;
            exit(1);
        }
        for (int i = 2; i < sito.size(); i++)
            if (sito[i]==i)
                primes.pb(i);
    }
    vector<int> Factor(int x){
        if (!_precomputed_sito_){
            cerr << "Precompute sito u idiot." << endl;
            exit(1);
        }
        vector<int> f;
        while (x^1){
            f.pb(sito[x]);
            x /= sito[x];
        }
        return f;
    }
    vector<int> GetDivs(ll x){
        vector<int> divs;
        for (int i = 2; i*i <= x; i++){
            if (x % i == 0){
                divs.pb(i);
                if (i*i < x) divs.pb(x / i);
            }
        }
        return divs;
    }
};
