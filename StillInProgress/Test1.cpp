#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define fi first
#define se second
#define en '\n'
#define sp ' '
#define tb '\t'
#define ri(n) int n; cin >> n
#define rl(n) ll n; cin >> n
#define rs(s) string s; cin >> s
#define rc(c) char c; cin >> c
#define rv(v) for (auto &x : v) cin >> x
#define pven(v) for (auto x : v) cout << x << en
#define pv(v) for (auto x : v) cout << x << sp; cout << en
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define yes cout << "YES" << en
#define no cout << "NO" << en
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define ssort(a, b) if (a < b) swap(a, b)
#define bitcnt(a) __builtin_popcountll(a)
#define bithigh(a) 64-__builtin_clzll(a)
int lg(ll a) { return bithigh(a) - 1; }
ll highpow(ll a) { return 1LL << (ll)lg(a); }

using namespace std;
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
using namespace modop;
template<class T>
class node{
public:
    T val;
    node<T>* ch[2];
    node<T>(){}
    node<T>(T val = T()){
        this->val = val;
        this->ch[0] = this->ch[1] = nullptr;
    }
    ~node<T>(){ delete this->ch[0]; delete this->ch[1]; }
    void add(int x, T val = T()){ this->ch[x] = new node<T>(val); }
};
template<class T>
class implicit_segtree{
private:
    ll left, right;
    node<T>* root;
    void init(ll l, ll r){
        ll n = r-l+1;
        if (highpow(n)^n) n = 2*highpow(n);
        this->left = l;
        this->right = l+n-1;
        root = new node<T>(T());
    }
    node<T>* ch(node<T>* s, int x){
        if (!s->ch[x]) s->add(x);
        return s->ch[x];
    }
    T update(node<T>* s, ll l, ll r, ll pos, T x){
        if (l > pos || r < pos) return s->val;
        if (l == r) return s->val = x;

        T a = T(), b = T();
        ll m = floor((double)(l + r) / 2.0);
        if (pos <= m){
            a = update(ch(s, 0), l, m, pos, x);
            if (s->ch[1]) b = ch(s, 1)->val;
        }
        else{
            b = update(ch(s, 1), m+1, r, pos, x);
            if (s->ch[0]) a = ch(s, 0)->val;
        }
        return s->val = T::op(a, b);
    }
    T query(node<T>* s, ll l, ll r, ll ql, ll qr){
        if (l > qr || r < ql) return T::null_v();
        if (l >= ql && r <= qr) return s->val;

        T a = T(), b = T();
        ll m = floor((double)(l + r) / 2.0);
        if (ql > m) a = T::null_v();
        if (qr <= m) b = T::null_v();

        if (s->ch[0]) a = query(ch(s, 0), l, m, ql, qr);
        if (s->ch[1]) b = query(ch(s, 1), m+1, r, ql, qr);
        return T::op(a, b);
    }
public:
    implicit_segtree(){}
    implicit_segtree(ll l, ll r){ init(l, r); }
    ~implicit_segtree(){ delete this->root; }
    void update(ll pos, auto x){ update(this->root, this->left, this->right, pos, T(x)); }
    auto query(ll l, ll r){ if (l > r) return T::null_v().val; return query(this->root, this->left, this->right, l, r).val; }
};
class prod_t{
public:
    ll val;

    prod_t(ll val = 1){ this->val = val; }
    static prod_t null_v(){ return prod_t(1); }

    static prod_t op(const prod_t& a, const prod_t& b){ return a * b; }
    // This is currently on set mode but it can be on add.
    prod_t up(const prod_t& a){ return *this = a; }
    void lazy_op(const prod_t& a, int l){ up(prod_t(mpow(a.val, l))); }

    prod_t operator =(const prod_t& a){ this->val = a.val; return *this; }
    prod_t operator *=(const prod_t& a) { this->val *= a.val; return *this; }
    prod_t operator /=(const prod_t& a) { this->val /= a.val; return *this; }
    prod_t operator *(const prod_t& a) const { return prod_t(this->val * a.val); }
    prod_t operator /(const prod_t& a) const { return prod_t(this->val / a.val); }
    bool operator ==(const prod_t& a) const { return this->val == a.val; }
    bool operator !=(const prod_t& a) const { return this->val != a.val; }

    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }
};
class lca{
private:
    int n, _edges_ = 0;
    vector<int> depth;
    vector<vector<int> > g, par;
    bool _initialized_ = 0, _computed_ = 0;
    void init(int n){
        this->n = n;
        this->depth = vector<int>(n);
        this->g = vector<vector<int> >(n);
        this->par = vector<vector<int> >(n, vector<int>(lg(n)+10, -1));
        this->_initialized_ = 1;
    }
    void dfs(int s, int p, int d){
        this->depth[s] = d;
        this->par[s][0] = p;
        for (int u : this->g[s])
            if (u^p)
                dfs(u, s, d+1);
    }
public:
    lca(){}
    lca(int n){ init(n); }
    void add(int u, int v){
        if (!this->_initialized_){
            cerr << "Initialize tree u idiot!" << endl;
            exit(1);
        }

        this->g[u].pb(v);
        this->g[v].pb(u);
        this->_edges_++;
    }
    void Compute(int root = 0){
        if (this->_edges_ < this->n-1){
            cerr << "Constructed tree is not connected!" << endl;
            exit(1);
        }
        if (this->_edges_ > this->n-1){
            cerr << "Constructed tree has cycles!" << endl;
            exit(1);
        }

        dfs(root, -1, 0);
        for (int d = 1; d < lg(this->n)+1; d++)
            for (int s = 0; s < this->n; s++)
                if (this->depth[s] >= (1<<d))
                    this->par[s][d] = this->par[this->par[s][d-1]][d-1];
        _computed_ = 1;
    }
    int Depth(int s) const {
        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        return this->depth[s];
    }
    int Par(int s, int d) const {

        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        if (d < 0 || d > this->depth[s]) return -1;
        if (!d) return s;
        return Par(this->par[s][lg(d)], d-highpow(d));
    }
    int Lca(int u, int v) const {

        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        if (this->depth[u] > this->depth[v]) swap(u, v);
        v = Par(v, this->depth[v] - this->depth[u]);
        if (u==v) return v;
        for (int i = lg(this->n)+1; ~i; i--){
            if (this->par[u][i]^this->par[v][i]){
                u = this->par[u][i];
                v = this->par[v][i];
            }
        }
        return this->par[u][0];
    }
    int Dist(int u, int v) const {

        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        int s = Lca(u, v);
        return this->depth[u] + this->depth[v] - 2*this->depth[s];
    }
    void Log() const {

        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        for (int s = 0; s < this->n; s++){
            cerr << s << tb;
            for (int d = 0; d < lg(this->n)+1; d++)
                cerr << this->par[s][d] << sp;
            cerr << endl;
        }
    }
};
class centroid{
private:
    int n;
    vector<vector<int> > g;
    int FindSize(int s, int p = -1){
        this->sz[s] = 1;
        for (int u : this->g[s])
            if (u^p && !this->was[u])
                this->sz[s] += FindSize(u, s);
        return this->sz[s];
    }
    int FindCentroid(int s, int p, int n){
        for (int u : this->g[s])
            if (u^p && !this->was[u] && this->sz[u] > n / 2)
                return FindCentroid(u, s, n);
        return s;
    }
public:
    vector<int> sz;
    vector<bool> was;
    centroid(){}
    centroid(int n){
        this->n = n;
        this->g = vector<vector<int> >(n, vector<int>());
        this->sz = vector<int>(n);
        this->was = vector<bool>(n, 0);
    }
    void edge(int u, int v){
        this->g[u].pb(v);
        this->g[v].pb(u);
    }
    int FindCentroid(int s){
        FindSize(s);
        s = FindCentroid(s, -1, this->sz[s]);
        this->was[s] = 1;
        return s;
    }
};

const ll LINF = 4e18;
const int mxN = 1e5+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
ll n, m, a[mxN], c[mxN], prod[mxN];
vector<array<int, 2> > g[mxN];
implicit_segtree<prod_t>* st[2];
lca* lc;
centroid* ct;

void dfs(int s = 0, int par = -1, int p = 1){

    prod[s] = p;
    for (auto [u, x] : g[s])
        if (u^par)
            dfs(u, s, mul(p, x));
}

ll weight(int u, int v){
    int s = lc->lca(u, v);
    return dvs(mul(prod[u], prod[v]), mpow(prod[s], 2));
}

ll Decomp(int s){
    s = ct->FindCentroid(s);

    for (auto [u, x] : g[s]){
        if (!ct->was[u]){
            d
        }
    }
}

void Solve(){

    cin >> n;
    lc = new lca(n);
    ct = new centroid(n);
    for (int i = 0; i < n-1; i++){
        ri(u); ri(v); ri(x);
        u--; v--;
        g[u].pb({v, x});
        g[v].pb({u, x});
        lc->add(u, v);
        ct->edge(u, v);
        cin >> c[i];
    }
    lc->Compute();
    dfs();
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cerr.tie(0);
    cout << setprecision(12) << fixed;
    cerr << setprecision(12) << fixed;
    cerr << "Started!" << endl;

    int t = 1;
    //cin >> t;
    while (t--)
        Solve();

    return 0;
}
