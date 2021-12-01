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

const ll LINF = 4e18;
const int mxN = 1e5+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
int n, a[mxN], dep[mxN], in[mxN], out[mxN], par[mxN][20];
vector<int> g[mxN];
array<int, 2> seg[4*mxN];

int dfs(int s = 0, int p = -1, int d = 0, int t = 0){
    in[s] = t;
    dep[s] = d;
    par[s][0] = p;
    for (int u : g[s])
        if (u^p)
            t = dfs(u, s, d+1, t+1);
    return out[s] = ++t;
}

void LcaInit(){
    for (int d = 0; d <= lg(n); d++)
        for (int s = 0; s < n; s++)
            par[s][d] = -1;
    dfs();
    for (int d = 0; d <= lg(n); d++)
        for (int s = 0; s < n; s++)
            if (dep[s] >= (1<<d))
                par[s][d] = par[par[s][d-1]][d-1];
}

bool inSub(int u, int v){ return in[u] <= in[v] && out[u] >= out[v]; }

int lca(int u, int v){
    if (dep[u] > dep[v]) swap(u, v);
    if (inSub(u, v)) return u;
    for (int i = lg(n); ~i; i--)
        if (~par[u][i] && !inSub(par[u][i], v))
            u = par[u][i];
    return par[u][0];
}

int dist(int u, int v){ return dep[u] + dep[v] - 2*dep[lca(u, v)]; }

array<int, 2> mx(array<int, 2>& a, array<int, 2> b){ if (dist(b[0], b[1]) > dist(a[0], a[1])) a = b; }

array<int, 2> op(array<int, 2> a, array<int, 2> b){
    if (!~a[0]) return b;
    if (!~b[0]) return a;
    array<int, 2> res = a;
    mx(res, b);
    mx(res, {a[0], b[0]});
    mx(res, {a[0], b[1]});
    mx(res, {a[1], b[0]});
    mx(res, {a[1], b[1]});
    return res;
}

array<int, 2> upd(int s, int l, int r, int ind, int x){
    if (l > ind || r < ind) return seg[s];
    if (l == r) return seg[s] = {x, x};
    int m = (l + r) / 2;
    array<int, 2> a = upd(2*s, l, m, ind, x);
    array<int, 2> b = upd(2*s+1, m+1, r, ind, x);
    return seg[s] = op(a, b);
}

array<int, 2> query(int s, int l, int r, int ql, int qr){
    if (l > qr || r < ql) return {-1, -1};
    if (ql >= l && qr <= r) return seg[s];
    int m = (l + r) / 2;
    array<int, 2> a = query(2*s, l, m, ql, qr);
    array<int, 2> b = query(2*s+1, m+1, r, ql, qr);
    return op(a, b);
}

void Solve(){

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i], a[i]--;
    for (int i = 1; i < n; i++){
        ri(u); ri(v);
        u--; v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    LcaInit();
    int N = (highpow(n)^n ? 2*highpow(n) : n);
    for (int i = 1; i < 2*N; i++) seg[i] = {-1, -1};
    for (int i = 0; i < n; i++) upd(1, 0, N-1, i, a[i]);
    for (int i = 1; i < 2*N; i++) cout << seg[i][0]+1 << sp;
    cout << endl;
    for (int i = 1; i < 2*N; i++) cout << seg[i][1]+1 << sp;
    cout << endl;
    ri(q);
    while (q--){
        ri(t); t--;
        if (t){
            ri(l); ri(r); ri(x);
            l--; r--; x--;
            array<int, 2> s = query(1, 0, N-1, l, r);
            cout << max(dist(s[0], x), dist(s[1], x)) << en;
        }
        else{
            ri(u); ri(v);
            u--; v--;
            upd(1, 0, N-1, u, a[v]);
            upd(1, 0, N-1, v, a[u]);
            swap(a[u], a[v]);
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
