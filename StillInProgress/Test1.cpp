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
#define bithigh(a) 64 - __builtin_clzll(a)
//#define log(a) bithigh(a) - 1
//#define highpow(a) (1LL<<log(a))

ll log(ll a){ return bithigh(a) - 1; }
ll highpow(ll a){ return 1LL << (bithigh(a) - 1); }

using namespace std;

template<class T>
class segtree{
private:
    int n;
    vector<T> tree, lazy;
    vector<bool> f;
    void init(int n){
        this->n = n;
        if (highpow(n)^n) this->n = 2*highpow(n);
        this->tree = vector<T>(2 * this->n, T());
        this->lazy = vector<T>(2 * this->n, T());
        this->f = vector<bool>(2 * this->n, 0);
    }
    T init(int s, int l, int r, auto* arr){
        if (l == r) return this->tree[s] = T(arr[l]);

        int m = (l + r) / 2;
        T a = init(2*s, l, m, arr);
        T b = init(2*s+1, m+1, r, arr);
        return this->tree[s] = T::op(a, b);
    }
    T update(int s, int l, int r, int ul, int ur, T x){
        eval_lazy(s, l, r);
        if (l > ur || r < ul) return this->tree[s];
        if (l >= ul && r <= ur){
            this->lazy[s].up(x);
            this->f[s] = 1;
            eval_lazy(s, l, r);
            return this->tree[s];
        }

        int m = (l + r) / 2;
        T a = update(2*s, l, m, ul, ur, x);
        T b = update(2*s+1, m+1, r, ul, ur, x);
        return this->tree[s] = T::op(a, b);
    }
    T query(int s, int l, int r, int ql, int qr) {
        eval_lazy(s, l, r);
        if (l > qr || r < ql) return T::null_v();
        if (l >= ql && r <= qr) return tree[s];

        int m = (l + r) / 2;
        T a = query(2*s, l, m, ql, qr);
        T b = query(2*s+1, m+1, r, ql, qr);
        return T::op(a, b);
    }
    void eval_lazy(int s, int l, int r){
        if (!this->f[s]) return;
        this->tree[s].lazy_op(this->lazy[s], r-l+1);
        if (l^r){
            this->lazy[2*s].up(this->lazy[s]);
            this->f[2*s] = 1;
            this->lazy[2*s+1].up(this->lazy[s]);
            this->f[2*s+1] = 1;
        }
        this->lazy[s] = T();
        this->f[s] = 0;
    }
public:
    segtree(int n = 0){ init(n); }
    segtree(int n, auto* arr){ init(n); init(1, 0, this->n - 1, arr); }

    void update(int l, int r, auto x) { update(1, 0, this->n-1, l, r, T(x)); }
    auto query(int l, int r) { if (l>r) return T::null_v().val; return query(1, 0, this->n-1, l, r).val; }

    void PrintTree() const { for (int i = 1; i < 2*this->n; i++) this->tree[i].Print(); cout << en; }
    void PrintLazy() const { for (int i = 1; i < 2*this->n; i++) this->lazy[i].Print(); cout << en; }
    void logTree() const { for (int i = 1; i < 2*this->n; i++) this->tree[i].log(); cerr << endl; }
    void logLazy() const { for (int i = 1; i < 2*this->n; i++) this->lazy[i].log(); cerr << endl; }
};
class sum_t{
public:
    ll val;

    sum_t(ll val = 0){ this->val = val; }
    static sum_t null_v(){ return sum_t(0); }

    static sum_t op(const sum_t& a, const sum_t& b){ return sum_t(a.val + b.val); }
    // This is currently on set mode but it can be on add.
    void up(const sum_t& a){ this->val = a.val; }
    void lazy_op(const sum_t& a, int l){ up(sum_t(a.val * l)); }

    sum_t operator =(const sum_t& a){ this->val = a.val; return *this; }
    bool operator ==(const sum_t& a) const { return this->val == a.val; }
    bool operator !=(const sum_t& a) const { return this->val != a.val; }

    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }
};

class lca{
private:
    int n, _edges_ = 0;
    vector<int> depth;
    vector<vector<int> > g, par;
    bool _initialized_ = 0;
    void init(int n){
        this->n = n;
        this->depth = vector<int>(n);
        this->g = vector<vector<int> >(n);
        this->par = vector<vector<int> >(n, vector<int>(log(n)+10, -1));
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
        for (int d = 1; d < log(this->n)+1; d++)
            for (int s = 0; s < this->n; s++)
                if (this->depth[s] >= (1<<d))
                    this->par[s][d] = this->par[this->par[s][d-1]][d-1];
    }
    int GetPar(int s, int d) const {

        if (d > this->depth[s]) return -1;
        if (!d) return s;
        return GetPar(this->par[s][log(d)], d-highpow(d));
    }
    int GetLca(int u, int v) const {

        if (this->depth[u] > this->depth[v]) swap(u, v);
        v = GetPar(v, this->depth[v] - this->depth[u]);
        int l = 0, r = this->depth[u], ans = -1;
        while (l <= r){
            int k = (l + r + 1) / 2;
            if (GetPar(u, k) == GetPar(v, k)){
                ans = GetPar(u, k);
                r = k - 1;
            }
            else l = k + 1;
        }
        return ans;
    }
    void Log() const {

        for (int s = 0; s < this->n; s++){
            cerr << s << sp;
            for (int d = 0; d < (int)log2(this->n)+1; d++)
                cerr << this->par[s][d] << sp;
            cerr << en;
        }
    }
};

const ll LINF = 4e18;
const int mxN = 2e5+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
int n, m, q, PQ, a[2*mxN], in[2][mxN], out[2][mxN];
vector<int> g[2][mxN];
lca lc[2];
segtree<sum_t> st;

int dfs(int s, int p, int x, int t){

    in[x][s] = t;
    for (int u : g[x][s])
        if (u^p)
            t = dfs(u, s, x, t+1);
    out[x][s] = ++t;
    return t;
}

void Resi(int N, int Q, int P, int *U1, int *V1, int *U2, int *V2, int *A1, int *B1, int *C1, int *D1, int *R){

    n = N; q = Q; PQ = P;
    lc[0] = *new lca(n);
    lc[1] = *new lca(n);
    for (int i = 0; i < n-1; i++){
        int u = U1[i]-1;
        int v = V1[i]-1;
        g[0][u].pb(v);
        g[0][v].pb(u);
        lc[0].add(u, v);
        u = U2[i]-1;
        v = V2[i]-1;
        g[1][u].pb(v);
        g[1][v].pb(u);
        lc[1].add(u, v);
    }
    lc[0].Compute();
    lc[1].Compute();
    dfs(0, -1, 0, 0);
    dfs(0, -1, 1, 0);
    for (int i = 0; i < n; i++){
        a[in[0][i]] = i;
        a[out[0][i]] = -i;
    }
    map<array<int, 2>, int> mp[2*n];
    for (int i = 0; i < q; i++){
        int a = A1[i]-1;
        int b = B1[i]-1;
        int c = C1[i]-1;
        int d = D1[i]-1;
        int s = lc[0].GetLca(a, b);
        int u = lc[1].GetLca(c, d);
        vector<array<int, 2> > v[2];
        v[0] = {{s, a}, {s, b}, {s, s}};
        v[1] = {{u, c}, {u, d}, {u, u}};
        for (auto x : v[0]){
            for (auto y : v[1]){
                mp[in[0][x[1]]][{in[1][y[0]], in[1][y[1]]}] = 0;
                if (in[0][x[0]])
                    mp[in[0][x[0]]-1][{in[1][y[0]], in[1][y[1]]}] = 0;
            }
        }
    }
    st = *new segtree<sum_t>(2*n);
    for (int i = 0; i < 2*n; i++){
        int s = a[i];
        if (!i || s > 0){
            st.update(in[1][s], in[1][s], 1);
            st.update(out[1][s], out[1][s], -1);
        }
        else{
            s = -s;
            st.update(in[1][s], in[1][s], 0);
            st.update(out[1][s], out[1][s], 0);
        }
        for (auto& t : mp[i])
            t.se = st.query(t.fi[0], t.fi[1]);
    }
    for (int i = 0; i < q; i++){
        int a = A1[i]-1;
        int b = B1[i]-1;
        int c = C1[i]-1;
        int d = D1[i]-1;
        int s = lc[0].GetLca(a, b);
        int u = lc[1].GetLca(c, d);
        vector<array<int, 2> > v[2];
        v[0] = {{s, a}, {s, b}};
        v[1] = {{u, c}, {u, d}};
        ll ans = 0;
        for (auto x : v[0]){
            for (auto y : v[1]){
                ans += mp[in[0][x[1]]][{in[1][y[0]], in[1][y[1]]}];
                if (in[0][x[0]])
                    ans -= mp[in[0][x[0]]-1][{in[1][y[0]], in[1][y[1]]}];
            }
            ans -= mp[in[0][x[1]]][{in[1][u], in[1][u]}];
            if (in[0][x[0]])
                ans += mp[in[0][x[0]]-1][{in[1][u], in[1][u]}];
        }
        for (auto y : v[1]){
            ans -= mp[in[0][s]][{in[1][y[0]], in[1][y[1]]}];
            if (in[0][s])
                ans += mp[in[0][s]-1][{in[1][y[0]], in[1][y[1]]}];
        }
        R[i] = ans;
    }
}
