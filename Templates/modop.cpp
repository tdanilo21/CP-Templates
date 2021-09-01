#define ll long long
namespace modop{
    const int mod = (1 ? 1e9+7 : 998244353);
    vector<ll> fact, ifact;
    ll norm(ll a){ a%=mod; if(a<0)a+=mod; return a; }
    ll add(ll a, ll b){ norm(a);norm(b); a+=b; return norm(a); }
    ll mul(ll a, ll b){ norm(a);norm(b); return ((ll)(a*b))%mod; }
    ll mpow(ll base, ll exp){
        if (!exp) return 1;
        ll t = mpow(base, exp/2);
        if (exp%2) return mul(mul(t, t), base);
        return mul(t, t);
    }
    ll inv(ll a){ norm(a); return mpow(a, mod-2); }
    ll dvs(ll a, ll b){ norm(a); norm(b); return mul(a, inv(b)); }
    ll nck(ll n, ll k){ norm(n); norm(k); if (k>n) return 0; return mul(fact[n], mul(ifact[k], ifact[n-k])); }
    #define sadd(a, b) a = add(a, b)
    #define smul(a, b) a = mul(a, b)
    #define sdvs(a, b) a = dvs(a, b)
    void init_fact(int mx){
        fact = ifact = vector<ll>(mx+10);
        fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
        for (int i = 2; i < mx; i++) fact[i] = mul(fact[i-1], i);
        ifact[mx-1] = inv(fact[mx-1]);
        for (int i = mx-2; i > 1; i--) ifact[i] = mul(i+1, ifact[i+1]);
    }
};
