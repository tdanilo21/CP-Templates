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

struct Chain{

    int n, u, v;
    vector<ll> nodes, pre, suf;
};

const ll LINF = 4e18;
const int mxN = 1e6+10, INF = 2e9;
ll n, m, ans, a[mxN], deg[mxN], idx[mxN], c_in[mxN];
vector<int> g[mxN], vbig;
vector<vector<ll> > dist;
bool erased[mxN], vis[mxN], big[mxN];
vector<Chain> chains;

void BFS(int S){

    queue<int> q;
    q.push(S);
    dist[idx[S]][S] = 0;
    while (q.size()){
        int s = q.front(); q.pop();
        for (int u : g[s]){
            if (!erased[u] && !~dist[idx[S]][u]){
                dist[idx[S]][u] = dist[idx[S]][s] + a[u];
                ans += dist[idx[S]][u] * a[S];
                q.push(u);
            }
        }
    }
}

vector<int> stk;

void InsertChain(){

    if (stk.size() < 3) return;
    chains.pb({});
    auto c = &chains.back();
    c->n = stk.size()-2;
    c->u = stk[0];
    c->v = stk.back();
    for (int i = 0; i < c->n; i++)
        c->nodes.pb(stk[i+1]);
    c->pre.resize(c->n);
    c->suf.resize(c->n);
    c->pre[0] = a[c->nodes[0]];
    for (int i = 1; i < c->n; i++)
        c->pre[i] = c->pre[i-1] + a[c->nodes[i]] * (i+1);
    c->suf[c->n-1] = a[c->nodes[c->n-1]];
    for (int i = c->n-2; ~i; i--)
        c->suf[i] = c->suf[i+1] + a[c->nodes[i]] * (c->n-i);
    for (int i = 0; i < c->n; i++){
        int s = c->nodes[i];
        idx[s] = chains.size()-1;
        c_in[s] = i;
    }
}

void dfs(int s, int p, int S, bool first){

    stk.pb(s);
    vis[s] = 1;
    if (big[s] && !first){
        if (S <= s) InsertChain();
        stk.pop_back();
        return;
    }
    for (int u : g[s])
        if (!erased[u] && u^p && (!vis[u] || u == S)) dfs(u, s, S, 0);
    stk.pop_back();
}

void NewBig(int s){
    idx[s] = vbig.size();
    big[s] = 1;
    vbig.pb(s);
    dist.pb(vector<ll>(n, -1));
    BFS(s);
}

int BS(int s, int i){

    auto c = &chains[i];
    int iu = idx[c->u], iv = idx[c->v];
    int l = 0, r = c->n-1, ans = -1;
    while (l <= r){
        int k = (l + r + 1)>>1;
        int x = c->nodes[k];
        if (dist[iu][s] + dist[iu][x] < dist[iv][s] + dist[iv][x]){
            l = k + 1;
            ans = k;
        }
        else r = k - 1;
    }
    return ans;
}

void Solve(){

    cin >> n >> m;
    for (int i = 0; i < m; i++){
        ri(u); ri(v);
        u--; v--;
        g[u].pb(v);
        g[v].pb(u);
        deg[u]++;
        deg[v]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++){
        a[i] = 1;
        if (deg[i] == 1) q.push(i);
    }
    while (q.size()){
        int s = q.front(); q.pop();
        erased[s] = 1;
        ans += 2*a[s]*(n-a[s]);
        for (int u : g[s]){
            if (!erased[u]){
                deg[u]--;
                a[u] += a[s];
                if (deg[u] == 1) q.push(u);
            }
        }
    }
    memset(idx, -1, sizeof(idx));
    for (int i = 0; i < n; i++)
        if (!erased[i] && deg[i] > 2)
            NewBig(i);
    if (vbig.empty()){
        for (int i = 0; i < n && vbig.empty(); i++)
            if (!erased[i]) NewBig(i);
    }
    for (int s : vbig) dfs(s, -1, s, 1);
    for (int i = 0; i < vbig.size(); i++){
        cout << vbig[i] << ": "; pv(dist[i]);
    }
    cout << "Chains: \n";
    for (int i = 0; i < chains.size(); i++){
        cout << chains[i].n << sp << chains[i].u << sp << chains[i].v << en;
        pv(chains[i].nodes);
        pv(chains[i].pre);
        pv(chains[i].suf);
    }
    for (int s = 0; s < n; s++){
        if (!erased[s] && !big[s]){
            for (int i = 0; i < chains.size(); i++){
                ll sum = 0;
                if (idx[s]^i){
                    int j = BS(s, i);
                    int iu = idx[chains[i].u], iv = idx[chains[i].v];
                    if (~j) sum += dist[iu][s] * (j+1) + chains[i].pre[j];
                    if (j < n-1) sum += dist[iv][s] * (chains[i].n - j - 1) + chains[i].suf[j+1];
                }
                else{
                    int j = c_in[s];
                    if (j) sum += chains[i].pre[j-1];
                    if (j < n-1) sum += chains[i].suf[j+1];
                }
                ans += sum * a[s];
            }
        }
    }
    cout << ans << en;
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
