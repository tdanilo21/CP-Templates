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
#define bithigh(a) 63-__builtin_clzll(a)
#define lg bithigh
ll highpow(ll a) { return 1LL << (ll)lg(a); }

using namespace std;

struct node{

    int val;
    node* ch[2];
    node(int v = 0){ val = v; ch[0] = ch[1] = nullptr; }
    node* create(int i){ return ch[i] = new node(); }
};
class segtree{

    int n, T;
    vector<node*> root;
    void init(int s){
        n = highpow(s);
        if (bitcnt(s) > 1) n <<= 1;
        root.pb(new node());
        T = 1;
        build(root[0], 0, n-1);
    }

    void build(node* s, int l, int r){
        if (l==r) return;
        int m = (l + r)>>1;
        build(s->create(0), l, m);
        build(s->create(1), m+1, r);
    }

    void update(node* s, node* last, int l, int r, int pos, int x){
        if (l == r){ s->val = x; return; }
        int m = (l + r)>>1;
        if (pos <= m){
            update(s->create(0), last->ch[0], l, m, pos, x);
            s->ch[1] = last->ch[1];
        }
        else{
            update(s->create(1), last->ch[1], m+1, r, pos, x);
            s->ch[0] = last->ch[0];
        }
        s->val = s->ch[0]->val + s->ch[1]->val;
    }

    int query(node* s, int l, int r, int ql, int qr) const {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return s->val;
        int m = (l + r)>>1;
        int a = query(s->ch[0], l, m, ql, qr);
        int b = query(s->ch[1], m+1, r, ql, qr);
        return a + b;
    }

public:
    segtree(int n){ init(n); }
    void update(int pos, int x, int t = -1){ if (!~t) t = T; root.pb(new node()); T++; update(root[T], root[t], 0, n-1, pos, x); }
    int query(int l, int r, int t) const { return query(root[t], 0, n-1, l, r); }
    int time() const { return T; }
};

class Lca{

    int n;
    vector<vector<int> > g, par;
    vector<int> depth, in, out;

    int dfs(int s, int p, int d, int t){
        par[s][0] = p;
        depth[s] = d;
        in[s] = t;
        for (int u : g[s])
            if (u^p)
                t = dfs(u, s, d+1, t+1);
        return out[s] = t+1;
    }

public:
    Lca(int s){
        n = s;
        g.resize(n+1);
        par.assign(n+1, vector<int>(lg(n)+1, -1));
        depth.resize(n+1);
        in.resize(n+1);
        out.resize(n+1);
    }

    void add(int u, int v){
        g[u].pb(v);
        g[v].pb(u);
    }

    void Compute(int root){
        dfs(root, 0, 0, 0);
        for (int d = 1; d <= lg(n); d++)
            for (int s = 1; s <= n; s++)
                if (~par[s][d-1])
                    par[s][d] = par[par[s][d-1]][d-1];
    }

    bool Ancestor(int p, int s) const { return in[s] >= in[p] && out[s] <= out[p]; }
    int Par(int s, int d) const {
        if (!d) return s;
        return Par(par[s][lg(d)], d-highpow(d));
    }
    int lca(int u, int v) const {
        if (depth[u] > depth[v]) swap(u, v);
        if (Ancestor(u, v)) return u;
        v = Par(v, depth[v]-depth[u]);
        for (int d = lg(n); ~d; d++){
            if (par[u][d]^par[v][d]){
                u = par[u][d];
                v = par[v][d];
            }
        }
        return par[u][0];
    }
    int In(int s) const { return in[s]; }
    int Out(int s) const { return out[s]; }
};

const ll LINF = 4e18;
const int mxN = 2e5+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
int t[mxN];
vector<int> g[mxN];
Lca *lc1, *lc2;
segtree* st;

void dfs(int s, int p){

    st->update(lc2->In(s), 1, t[p]);
    st->update(lc2->Out(s), -1);
    t[s] = st->time();
    for (int u : g[s])
        if (u^p)
            dfs(u, s);
}

int query(int s, int u, int v){

    int p = lc2->lca(u, v);
    int a = lc2->In(u);
    int b = lc2->In(v);
    int c = lc2->In(p);
    return st->query(c, a, t[s]) + st->query(c, b, t[s]) - st->query(c, c, t[s]);
}

void Resi(int N, int Q, int P, int *U1, int *V1, int *U2, int *V2, int *A1, int *B1, int *C1, int *D1, int *R){

    lc1 = new Lca(N); lc2 = new Lca(N);
    for (int i = 1; i <= N; i++){
        g[U1[i]].pb(V1[i]);
        g[V1[i]].pb(U1[i]);
        lc1->add(U1[i], V1[i]);
        lc2->add(U2[i], V2[i]);
    }
    lc1->Compute(1);
    lc2->Compute(1);
    st = new segtree(2*N);
    dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= Q; i++){
        int a = (A1[i] + ans * P - 1) % N + 1;
        int b = (B1[i] + ans * P - 1) % N + 1;
        int c = (C1[i] + ans * P - 1) % N + 1;
        int d = (D1[i] + ans * P - 1) % N + 1;
        int s = lc1->lca(a, b);
        ans = query(a, c, d) + query(b, c, d) - query(s, c, d);
        R[i] = ans;
    }
}
