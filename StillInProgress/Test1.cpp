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

const ll LINF = 4e18;

class implicit_segtree{

    ll L, R;
    vector<ll> tree;
    vector<array<int, 2> > ch;

    int Node(){ tree.pb(-LINF); ch.pb({-1, -1}); return tree.size() - 1; }

    int Ch(int s, int i){ if (!~ch[s][i]) ch[s][i] = Node(); return ch[s][i]; }

    ll Val(int s){ return (!~s ? -LINF : tree[s]); }

    void update(int s, ll l, ll r, ll pos, ll x){
        //volim te<3
        if (l == r){
            smax(tree[s], x);
            return;
        }
        ll m = (l + r)>>1;
        if (pos <= m) update(Ch(s, 0), l, m, pos, x);
        else update(Ch(s, 1), m+1, r, pos, x);
        tree[s] = max(Val(ch[s][0]), Val(ch[s][1]));
    }

    ll query(int s, ll l, ll r, ll ql, ll qr) const {
        if (l > qr || r < ql || !~s) return -LINF;
        if (l >= ql && r <= qr) return tree[s];
        ll m = (l + r)>>1;
        return min(query(ch[s][0], l, m, ql, qr), query(ch[s][1], m+1, r, ql, qr));
    }

public:
    implicit_segtree(ll l, ll r){ Assign(l, r); }

    void Assign(ll l, ll r){
        L = l; R = r;
        Node();
    }

    void update(ll pos, ll x){ update(0, L, R, pos, x); }

    ll query(ll r) const { return query(0, L, R, L, r); }
};

class segtree{

    ll L, R;
    vector<implicit_segtree> tree;
    vector<array<int, 2> > ch;

    int Node(){ tree.pb(implicit_segtree(L, R)); ch.pb({-1, -1}); return tree.size() - 1; }

    int Ch(int s, int i){ if (!~ch[s][i]) ch[s][i] = Node(); return ch[s][i]; }

    void update(int s, ll l, ll r, ll pos, ll x, ll y){
        if (l > pos || r < pos) return;
        tree[s].update(x, y);
        if (l == r) return;
        ll m = (l + r)>>1;
        if (pos <= m) update(Ch(s, 0), l, m, pos, x, y);
        else update(Ch(s, 1), m+1, r, pos, x, y);
    }

    bool Check(int s, ll x) const { if (!~s) return 0; return tree[s].query(x) >= x; }

    ll Walk(int s, ll l, ll r, ll ql, ll qr, ll x) const {
        if (!Check(s, x) || l > qr || r < ql) return -1;
        if (l == r) return l;
        ll m = (l + r)>>1;
        ll y = Walk(ch[s][0], l, m, ql, qr, x);
        if (~y) return y;
        return Walk(ch[s][1], m+1, r, ql, qr, x);
    }

public:
    segtree(ll l, ll r){ Assign(l, r); }

    void Assign(ll l, ll r){
        L = l; R = r;
        Node();
    }

    void update(ll pos, ll x, ll y){ update(0, L, R, pos, x, y); }
    ll Walk(ll l, ll r, ll x) const { return Walk(0, L, R, l, r, x); }
};

const int mxN = 1e6+10, INF = 2e9;
ll n, m, a[mxN];
segtree st[4];
set<array<ll, 2> > s[4];

void Solve(){

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
