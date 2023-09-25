#define ll long long
template <ll mod>
class mll{

    ll v;
    void norm(){ v %= mod; if(v<0) v += mod; }
    mll<mod> inv() const { return *this ^ (mod-2); }
    mll<mod> pow(const ll& exp) const {
        if (!exp) return 1;
        mll<mod> t = pow(exp/2);
        if (exp%2) return t*t*v;
        return t*t;
    }
    static vector<mll<mod> > fact, ifact;

public:
    mll<mod>(ll val = 0){ v = val; norm(); }
    bool operator==(const ll& a) const { return v == a; }
    bool operator!=(const ll& a) const { return v != a; }
    bool operator<(const ll& a) const { return v < a; }
    bool operator<=(const ll& a) const { return v <= a; }
    bool operator>(const ll& a) const { return v > a; }
    bool operator>=(const ll& a) const { return v >= a; }

    mll<mod> operator+(const ll& a) const { return mll<mod>(v+a); }
    mll<mod> operator-(const ll& a) const { return mll<mod>(v-a); }
    mll<mod> operator*(const ll& a) const { return mll<mod>(v*a); }
    mll<mod> operator/(const ll& a) const { return *this * mll<mod>(a).inv(); }
    mll<mod> operator=(const ll& a) { v = a; norm(); return *this; }
    mll<mod> operator+=(const ll& a) { v += a; norm(); return *this; }
    mll<mod> operator-=(const ll& a) { v -= a; norm(); return *this; }
    mll<mod> operator*=(const ll& a) { v *= a; norm(); return *this; }
    mll<mod> operator/=(const ll& a) { v /= a; norm(); return *this; }
    mll<mod> operator^(const ll& a) const { return pow(a); }
    mll<mod> operator^=(const ll& a) { v = pow(a).v; return *this; }
    mll<mod> operator++() { v++; return *this; }
    mll<mod> operator++(int) { mll<mod> temp = *this; v++; return temp; }
    mll<mod> operator--() { v--; return *this; }
    mll<mod> operator--(int) { mll<mod> temp = *this; v--; return temp; }

    operator ll&() { return v; }
    operator ll() const { return v; }

    static void init_fact(int mx){
        mll<mod>::fact.resize(mx+1);
        mll<mod>::ifact.resize(mx+1);
        mll<mod>::fact[0] = mll<mod>::fact[1] = 1;
        mll<mod>::ifact[0] = mll<mod>::ifact[1] = 1;
        for (int i = 2; i <= mx; i++) mll<mod>::fact[i] = mll<mod>::fact[i-1] * i;
        mll<mod>::ifact[mx] = mll<mod>::fact[mx].inv();
        for (int i = mx-1; i > 1; i--) mll<mod>::ifact[i] = mll<mod>::ifact[i+1] * (i+1);
    }
    static mll<mod> nck(const ll& n, const ll& k){ if (k>n) return 0; return mll<mod>::fact[n] * mll<mod>::ifact[k] * mll<mod>::ifact[(n-k)]; }
    static mll<mod> Fact(const ll& f){ if (f < 0) return LONG_MIN; return mll<mod>::fact[f]; }
};
const ll MOD = /*set your modulo*/;
#define mod mll<MOD>
template<> vector<mod> mod::fact = vector<mod>();
template<> vector<mod> mod::ifact = vector<mod>();
