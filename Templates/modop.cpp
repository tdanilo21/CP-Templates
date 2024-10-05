#define ll long long
template <ll mod>
class Mint{

    ll v;
    void norm(){ v %= mod; if(v<0) v += mod; }
    Mint<mod> inv() const { return *this ^ (mod-2); }
    Mint<mod> pow(const ll& exp) const {
        if (!exp) return 1;
        Mint<mod> t = pow(exp/2);
        if (exp%2) return t*t*v;
        return t*t;
    }
    static vector<Mint<mod> > fact, ifact;

public:
    Mint<mod>(ll val = 0){ v = val; norm(); }
    bool operator==(const ll& a) const { return v == a; }
    bool operator!=(const ll& a) const { return v != a; }
    bool operator<(const ll& a) const { return v < a; }
    bool operator<=(const ll& a) const { return v <= a; }
    bool operator>(const ll& a) const { return v > a; }
    bool operator>=(const ll& a) const { return v >= a; }

    Mint<mod> operator+(const ll& a) const { return Mint<mod>(v+a); }
    Mint<mod> operator-(const ll& a) const { return Mint<mod>(v-a); }
    Mint<mod> operator*(const ll& a) const { return Mint<mod>(v*a); }
    Mint<mod> operator/(const ll& a) const { return *this * Mint<mod>(a).inv(); }
    Mint<mod> operator=(const ll& a) { v = a; norm(); return *this; }
    Mint<mod> operator+=(const ll& a) { v += a; norm(); return *this; }
    Mint<mod> operator-=(const ll& a) { v -= a; norm(); return *this; }
    Mint<mod> operator*=(const ll& a) { v *= a; norm(); return *this; }
    Mint<mod> operator/=(const ll& a) { v *= Mint<mod>(a).inv(); norm(); return *this; }
    Mint<mod> operator^(const ll& a) const { return pow(a); }
    Mint<mod> operator^=(const ll& a) { v = pow(a).v; return *this; }
    Mint<mod> operator++() { v++; return *this; }
    Mint<mod> operator++(int) { Mint<mod> temp = *this; v++; return temp; }
    Mint<mod> operator--() { v--; return *this; }
    Mint<mod> operator--(int) { Mint<mod> temp = *this; v--; return temp; }

    operator ll&() { return v; }
    operator ll() const { return v; }

    static void init_fact(int mx){
        Mint<mod>::fact.resize(mx+1);
        Mint<mod>::ifact.resize(mx+1);
        Mint<mod>::fact[0] = Mint<mod>::fact[1] = 1;
        Mint<mod>::ifact[0] = Mint<mod>::ifact[1] = 1;
        for (int i = 2; i <= mx; i++) Mint<mod>::fact[i] = Mint<mod>::fact[i-1] * i;
        Mint<mod>::ifact[mx] = Mint<mod>::fact[mx].inv();
        for (int i = mx-1; i > 1; i--) Mint<mod>::ifact[i] = Mint<mod>::ifact[i+1] * (i+1);
    }
    static Mint<mod> nck(const ll& n, const ll& k){ if (k>n) return 0; return Mint<mod>::fact[n] * Mint<mod>::ifact[k] * Mint<mod>::ifact[(n-k)]; }
    static Mint<mod> Fact(const ll& f){ if (f < 0) return LONG_MIN; return Mint<mod>::fact[f]; }
    static Mint<mod> IFact(const ll& f){ if (f < 0) return LONG_MIN; return Mint<mod>::ifact[f]; }
};
const ll _MOD_ = /*set your modulo*/;
#define mint Mint<_MOD_>
template<> vector<mod> mint::fact = vector<mint>();
template<> vector<mod> mint::ifact = vector<mint>();
