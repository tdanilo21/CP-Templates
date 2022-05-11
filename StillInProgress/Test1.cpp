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

class segtree{

    int n;
    vector<ll> tree;

    void init(int s){
        n = highpow(s);
        if (bitcnt(s) > 1) n <<= 1;
        tree.assign(2*n, 0);
    }

    ll update(int s, int l, int r, int pos, ll x){
        if (pos < l || pos > r) return tree[s];
        if (l == r) return tree[s] = x;
        int m = (l + r)>>1;
        ll a = update(2*s, l, m, pos, x);
        ll b = update(2*s+1, m+1, r, pos, x);
        return tree[s] = max(a, b);
    }

    ll query(int s, int l, int r, int ql, int qr) const {
        if (ql > r || qr < l) return 0;
        if (l >= ql && r <= qr) return tree[s];
        int m = (l + r)>>1;
        ll a = query(2*s, l, m, ql, qr);
        ll b = query(2*s+1, m+1, r, ql, qr);
        return max(a, b);
    }

public:
    segtree(int n){ init(n); }
    void update(int pos, ll x){ update(1, 0, n-1, pos, x); }
    ll query(int l, int r) const { if (l>r) return 0; return query(1, 0, n-1, l, r); }
};

const ll LINF = 4e18;
const int mxN = 2e2+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
ll n, m, a[mxN], b[mxN], dp[mxN][mxN], sub_dp[mxN][mxN];
vector<int> g[mxN];
segtree* st[mxN];

int BS(int i, int u, int j){

    int l = 0, r = j, ans = j;
    while (l <= r){
        int k = (l + r + 1)>>1;
        if (sub_dp[i][k] >= dp[u][j-k]){
            r = k - 1;
            ans = k;
        }
        else l = k + 1;
    }
    return ans;
}

void DP(int s){

    int n = g[s].size();
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            sub_dp[i][j] = 0;
    if (!n) return;
    segtree* sub_st[n];
    for (int i = 0; i < n; i++)
        sub_st[i] = new segtree(m+1);
    for (int j = 0; j <= m; j++){
        sub_dp[0][j] = dp[g[s][0]][j];
        sub_st[0]->update(j, sub_dp[0][j]);
    }
    for (int i = 1; i < n; i++){
        for (int j = 0; j <= m; j++){
            int k = BS(i-1, g[s][i], j);
            sub_dp[i][j] = max(sub_st[i-1]->query(0, k-1), st[g[s][i]]->query(k, j));
            sub_st[i]->update(j, sub_dp[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
        delete sub_st[i];
}

void dfs(int s){

    for (int u : g[s])
        dfs(u);
    DP(s);
    for (int j = 0; j <= m; j++){
        for (int k = 0; k <= j; k++)
            smax(dp[s][j], k + sub_dp[g[s].size()-1][j-k]);
        dp[s][j] = a[s] + b[s] * dp[s][j];
        st[s]->update(j, dp[s][j]);
    }
}

void Solve(){

    cin >> n >> m;
    for (int i = 0; i < n; i++){
        ri(p); p--;
        if (~p) g[p].pb(i);
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < n; i++)
        st[i] = new segtree(m+1);
    dfs(0);
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= m; j++)
            cout << dp[i][j] << sp;
        cout << en;
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
