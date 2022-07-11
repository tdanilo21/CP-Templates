#define ll long long
template <ll mod>
class mll{

    ll v;
    void norm(){ v %= mod; if(v<0) v += mod; }
    mll<mod> inv() const { return  *this ^ (mod-2); }
    mll<mod> pow(const ll& exp) const {
        if (!exp) return 1;
        mll<mod> t = pow(exp/2);
        if (exp%2) return t*t*v;
        return t*t;
    }
    static vector<mll<mod> > fact, ifact;

public:
    mll<mod>(ll val = 0){ v = val; norm(); }
    bool operator==(const mll<mod>& a) const { return v == a.v; }
    bool operator!=(const mll<mod>& a) const { return v != a.v; }
    bool operator<(const mll<mod>& a) const { return v < a.v; }
    bool operator<=(const mll<mod>& a) const { return v <= a.v; }
    bool operator>(const mll<mod>& a) const { return v > a.v; }
    bool operator>=(const mll<mod>& a) const { return v >= a.v; }

    mll<mod> operator+(const mll<mod>& a) const { return mll<mod>(v+a.v); }
    mll<mod> operator-(const mll<mod>& a) const { return mll<mod>(v-a.v); }
    mll<mod> operator*(const mll<mod>& a) const { return mll<mod>(v*a.v); }
    mll<mod> operator/(const mll<mod>& a) const { return *this * a.inv(); }
    mll<mod> operator=(const mll<mod>& a) { v = a.v; norm(); return *this; }
    mll<mod> operator+=(const mll<mod>& a) { v += a.v; norm(); return *this; }
    mll<mod> operator-=(const mll<mod>& a) { v -= a.v; norm(); return *this; }
    mll<mod> operator*=(const mll<mod>& a) { v *= a.v; norm(); return *this; }
    mll<mod> operator/=(const mll<mod>& a) { v /= a.v; norm(); return *this; }
    mll<mod> operator^(const ll& a) const { return pow(a); }
    mll<mod> operator^=(const ll& a) { v = pow(a).v; return *this; }

    friend istream& operator>>(istream& is, mll<mod>& a){ is >> a.v; return is; }
    friend ostream& operator<<(ostream& os, const mll<mod>& a){ os << a.v; return os; }

    static void init_fact(int mx){
        mll<mod>::fact.resize(mx+1);
        mll<mod>::ifact.resize(mx+1);
        mll<mod>::fact[0] = mll<mod>::fact[1] = 1;
        mll<mod>::ifact[0] = mll<mod>::ifact[1] = 1;
        for (int i = 2; i <= mx; i++) mll<mod>::fact[i] = mll<mod>::fact[i-1] * i;
        mll<mod>::ifact[mx] = mll<mod>::fact[mx].inv();
        for (int i = mx-1; i > 1; i--) mll<mod>::ifact[i] = mll<mod>::ifact[i+1] * (i+1);
    }
    static mll<mod> nck(const mll<mod>& n, const mll<mod>& k){ if (k>n) return 0; return mll<mod>::fact[n.v] * mll<mod>::ifact[k.v] * mll<mod>::ifact[(n-k).v]; }
    static mll<mod> Fact(const mll<mod>& f){ if (f < 0) return LONG_MIN; return mll<mod>::fact[f.v]; }
};
#define mod mll</*set your modulo*/>
template<> vector<mod> mod::fact = vector<mod>();
template<> vector<mod> mod::ifact = vector<mod>();
