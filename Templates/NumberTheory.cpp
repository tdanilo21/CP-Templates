#define ll long long
namespace NumberTheory{
    vector<int> sito, primes;
    bool _precomputed_sito_ = 0;
    ll gcd(ll a, ll b, ll* x = nullptr, ll* y = nullptr){
        if (!b){
            if (x){ *x = 1; *y = 0; }
            return a;
        }
        ll x1, y1;
        ll g = gcd(b, a%b, &x1, &y1);
        if (x){ *x = y1; *y = x1 - (a/b) * y1; }
        return g;
    }
    array<ll, 2> Crt(const vector<array<ll, 2> >& v){
        queue<array<ll, 2> > q;
        ll nzd = 0;
        for (auto x : v){
            x[0] %= x[1]; if (x[0]<0) x[0] += x[1];
            nzd = gcd(nzd, x[1]);
            q.push(x);
        }
        if (nzd^1) return {-1, -1};
        while (1){
            auto s1 = q.front(); q.pop();
            auto s2 = q.front(); q.pop();
            if (s2[0]-s1[0] < 0) swap(s1, s2);
            ll x, y;
            gcd(s1[1], s2[1], &x, &y);
            ll m = s1[1]*s2[1];
            x %= s2[1]; if (x<0) x += s2[1];
            ll c = (x * (s2[0] - s1[0])) % m;
            array<ll, 2> s3 = {(c * s1[1] + s1[0]) % m, m};
            if (q.empty()) return s3;
            q.push(s3);
        }
    }
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
