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
#define bitcnt(a) (__builtin_popcountll(a))
#define bithigh(a) (63-__builtin_clzll(a))
#define lg bithigh
#define highpow(a) (1LL << (ll)lg(a))

using namespace std;

class segtree{

    int n;
    vector<ll> tree;

    ll update(int s, int l, int r, int pos, ll x){
        if (pos < l || pos > r) return tree[s];
        if (l == r) return tree[s] = x;
        int m = (l + r)>>1;
        ll a = update(2*s, l, m, pos, x);
        ll b = update(2*s+1, m+1, r, pos, x);
        return tree[s] = max(a, b);
    }

    ll query(int s, int l, int r, int ql, int qr) const {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tree[s];
        int m = (l + r)>>1;
        ll a = query(2*s, l, m, ql, qr);
        ll b = query(2*s+1, m+1, r, ql, qr);
        return max(a, b);
    }

public:
    void Assign(int s){
        n = highpow(s);
        if (bitcnt(s) > 1) n <<= 1;
        tree.assign(2*n, 0);
    }
    void update(int pos, ll x){ update(1, 0, n-1, pos, x); }
    ll query(int l, int r) const { return query(1, 0, n-1, l, r); }
};

class Tree{

private:
    int n, root;
    vector<int> depth, in, out;
    vector<vector<int> > g, par;
    int _edges_ = 0;
    bool _initialized_ = 0;

    bool Valid(int s) const { return s >= 0 && s < n; }

    int InitDfs(int s, int p = -1, int d = 0, int t = 0){
        par[s][0] = p;
        depth[s] = d;
        in[s] = t;
        for (int u : g[s])
            if (u^p)
                t = InitDfs(u, s, d+1, t+1);
        return out[s] = ++t;
    }

    void Dfs(int s, int p, void bf(int, int), void af(int, int)) const {
        bf(s, p);
        for (int u : g[s])
            if (u^p)
                Dfs(u, s, bf, af);
        af(s, p);
    }

public:
    Tree(int n = 0){ Assign(n); }

    void Assign(int n = 0){
        this->n = n;
        depth.assign(n, 0);
        in.assign(n, 0);
        out.assign(n, 0);
        g.assign(n, vector<int>());
        par.assign(n, vector<int>(lg(n)+1, -1));
    }

    void Edge(int u, int v){
        if (!Valid(u) || !Valid(v)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        g[u].pb(v);
        g[v].pb(u);
        _edges_++;
    }

    void Read(int d = 1){
        for (int i = 0; i < n-1; i++){
            ri(u); ri(v);
            u -= d; v -= d;
            Edge(u, v);
        }
    }

    void Initialize(int s = 0){
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        if (_edges_ < n-1){
            cerr << "Tree is not connected" << endl;
            exit(1);
        }
        if (_edges_ > n-1){
            cerr << "Tree has cycle(s)" << endl;
            exit(1);
        }
        root = s;
        InitDfs(s);
        for (int d = 1; d <= lg(n); d++)
            for (int i = 0; i < n; i++)
                if (depth[i] >= (1<<d))
                    par[i][d] = par[par[i][d-1]][d-1];
        _initialized_ = 1;
    }

    int Size() const { return n; }

    int Depth(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return depth[s];
    }

    int InTime(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return in[s];
    }

    int OutTime(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return out[s];
    }

    vector<int> GetAdjecent(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return g[s];
    }

    vector<int> GetChilds(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        vector<int> ch;
        for (int u : g[s])
            if (u^par[s][0])
                ch.pb(u);
        return ch;
    }

    int Par(int s, int d = 1) const {
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        if (d < 0 || d > depth[s]) return -1;
        if (!d) return s;
        return Par(par[s][lg(d)], d - highpow(d));
    }

    bool Ancestor(int s, int p) const {
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        return in[s] > in[p] && out[s] < out[p];
    }

    int Lca(int u, int v) const {
        if (!Valid(u) || !Valid(v)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (Ancestor(v, u)) return u;
        v = Par(v, depth[v] - depth[u]);
        for (int d = lg(n); ~d; d--){
            if (par[u][d] != par[v][d]){
                u = par[u][d];
                v = par[v][d];
            }
        }
        return par[u][0];
    }

    int Dist(int u, int v) const {
        if (!Valid(u) || !Valid(v)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        int lca = Lca(u, v);
        return 2*depth[lca] - depth[u] - depth[v];
    }

    void Dfs(void bf(int, int), void af(int, int)) const { Dfs(root, -1, bf, af); }
};
#define Empty [](int, int){}

class HLD{

    int n, m;
    vector<vector<int> > g;
    vector<int> path, idx, sz;
    vector<segtree> st;
    Tree tree;

    int Size(int s, int p){
        sz[s] = 1;
        for (int u : g[s])
            if (u^p)
                sz[s] += Size(u, s);
        return sz[s];
    }

    void dfs(int s, int p, int c, int i){
        path[s] = c;
        idx[s] = i;
        int big = -1;
        for (int u : g[s])
            if (u^p && (!~big || sz[u] > sz[big]))
                big = u;
        dfs(big, s, c, i+1);
        for (int u : g[s])
            if (u^p && u^big)
                dfs(u, s, m++, 0);
        if (g[s].size() == 1 && ~p){
            segtree seg; seg.Assign(i+1);
            st.pb(seg);
        }
    }

public:
    void Assign(int s){
        n = s; m = 0;
        g.assign(n, vector<int>());
        path.resize(n);
        idx.resize(n);
        sz.resize(n);
        tree.Assign(n);
    }
    void edge(int u, int v){
        g[u].pb(v);
        g[v].pb(u);
        tree.Edge(u, v);
    }
    void Compute(int root = 0){
        Size(root, -1);
        dfs(root, -1, m++, 0);
        tree.Initialize(root);
    }
    void update(int s, ll x){ st[path[s]].update(idx[s], x); }
    ll query(int u, int v) const {
        if (tree.Depth(u) > tree.Depth(v)) swap(u, v);
        if (!tree.Ancestor(v, u)){
            int s = tree.Lca(u, v);
            return max(query(s, u), query(s, v));
        }
        if (path[u] == path[v]) return st[path[u]].query(idx[u], idx[v]);
        return st[path[v]].query(0, idx[v]) + query(u, tree.Par(v, idx[v]+1));
    }
};

const ll LINF = 4e18;
const int mxN = 1e6+10, INF = 2e9;
ll n, m, a[mxN];
HLD hld;

void Solve(){

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    hld.Assign(n);
    for (int i = 0; i < n-1; i++){
        ri(u); ri(v);
        u--; v--;
        hld.edge(u, v);
    }
    for (int i = 0; i < n; i++)
        hld.update(i, a[i]);
    while (m--){
        ri(t); t--;
        if (t){
            ri(u); ri(v);
            u--; v--;
            cout << hld.query(u, v) << en;
        }
        else{
            ri(s); rl(x);
            s--;
            hld.update(s, x);
        }
    }
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
