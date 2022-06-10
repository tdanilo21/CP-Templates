#include <bits/stdc++.h>
using namespace std;

#define ll long long

template <ll mod>
class mint{

    ll v;
    void norm(){ v %= mod; if(v<0) v += mod; }
    mint<mod> inv() const { return  *this ^ (mod-2); }
    mint<mod> pow(const ll& exp) const {
        if (!exp) return 1;
        mint<mod> t = pow(exp/2);
        if (exp%2) return t*t*v;
        return t*t;
    }

    static vector<mint<mod> > fact, ifact;
public:
    mint<mod>(ll val = 0){ v = val; norm(); }
    bool operator==(const mint<mod>& a) const { return v == a.v; }
    bool operator!=(const mint<mod>& a) const { return v != a.v; }
    bool operator<(const mint<mod>& a) const { return v < a.v; }
    bool operator<=(const mint<mod>& a) const { return v <= a.v; }
    bool operator>(const mint<mod>& a) const { return v > a.v; }
    bool operator>=(const mint<mod>& a) const { return v >= a.v; }

    mint<mod> operator+(const mint<mod>& a) const { return mint<mod>(v+a.v); }
    mint<mod> operator-(const mint<mod>& a) const { return mint<mod>(v-a.v); }
    mint<mod> operator*(const mint<mod>& a) const { return mint<mod>(v*a.v); }
    mint<mod> operator/(const mint<mod>& a) const { return *this * a.inv(); }
    mint<mod> operator=(const mint<mod>& a) { v = a.v; return *this; }
    mint<mod> operator+=(const mint<mod>& a) { v += a.v; norm(); return *this; }
    mint<mod> operator-=(const mint<mod>& a) { v -= a.v; norm(); return *this; }
    mint<mod> operator*=(const mint<mod>& a) { v *= a.v; norm(); return *this; }
    mint<mod> operator/=(const mint<mod>& a) { v /= a.v; norm(); return *this; }
    mint<mod> operator^(const ll& a) const { return pow(a); }

    friend istream& operator>>(istream& is, mint<mod>& a){ is >> a.v; return is; }
    friend ostream& operator<<(ostream& os, const mint<mod>& a){ os << a.v; return os; }

    static void init_fact(int mx){
        mint<mod>::fact = mint<mod>::ifact = vector<mint<mod> >(mx+10);
        mint<mod>::fact[0] = mint<mod>::fact[1] = 1;
        mint<mod>::ifact[0] = mint<mod>::ifact[1] = 1;
        for (int i = 2; i < mx; i++) mint<mod>::fact[i] = mint<mod>::fact[i-1] * i;
        mint<mod>::ifact[mx-1] = mint<mod>::fact[mx-1].inv();
        for (int i = mx-2; i > 1; i--) mint<mod>::ifact[i] = mint<mod>::ifact[i+1] * (i+1);
    }
    static mint<mod> nck(const mint<mod>& n, const mint<mod>& k){ if (k>n) return 0; return mint<mod>::fact[n] * mint<mod>::ifact[k] * mint<mod>::ifact[n-k]; }
};
#define mod mint<(ll)1e9+7>

int main(){

    mod a;
    cin >> a;
    cout << a/2 << '\n';
    mod::init_fact(20);
}
