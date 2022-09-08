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

struct arr{ ll s, d; arr(ll _s = 0, ll _d = 0){ s = _s; d = _d; } };

struct node{

    ll val;
    arr lazy;
    bool f;
    node* ch[2];
    node(ll v = 0){ val = v; f = 0; ch[0] = ch[1] = nullptr; }
    node* add(int i, ll v = 0){ return ch[i] = new node(v); }
};

class segtree{

    ll left, right;
    node* root;

    void init(ll l, ll r){
        ll n = highpow(r-l+1);
        if (bitcnt(r-l+1) > 1) n <<= 1;
        left = l;
        right = l+n-1;
        root = new node();
    }

    node* ch(node* s, int i){ if (!s->ch[i]) s->add(i); return s->ch[i]; }

    ll update(node* s, ll l, ll r, ll ul, ll ur, arr x){
        eval_lazy(s, l, r);
        if (l > ur || r < ul) return s->val;
        if (l >= ul && r <= ur){
            s->lazy = x;
            s->f = 1;
            eval_lazy(s, l, r);
            return s->x;
        }
        ll a = 0, b = 0;
        ll m = floor((double)(l + r) / 2.0);
        if (ul <= m) a = update(ch(s, 0), l, m, ul, ur, x);
        else if (s->ch[0]) a = s->ch[0]->val;
        if (ur > m) b = update(ch(s, 1), m+1, r, ul, ur, x);
        else if (s->ch[1]) b = s->ch[1]->val;
        return s->val = max(a, b);
    }

    ll query(node* s, ll l, ll r, ll ql, ll qr){
        eval_lazy(s, l, r);
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return s->val;
        ll a = 0, b = 0;
        ll m = floor((double)(l + r) / 2.0);
        if (s->ch[0]) a = query(s->ch[0], l, m, ql, qr);
        if (s->ch[1]) b = query(s->ch[1], m+1, r, ql, qr);
        return max(a, b);
    }

    void eval_lazy(node* s, ll l, ll r){
        if (!s->f) return;
        ll n = r-l+1;
        s->val += s->lazy.s * n + n * (n-1) * s->lazy.d / 2LL;
        if (n^1){

        }
    }
};

const ll LINF = 4e18;
const int mxN = 1e6+10, INF = 2e9;
ll n, m, a[mxN];

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
