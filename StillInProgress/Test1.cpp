#include <bits/stdc++.h>
#include "game.h"

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

long long gcd2(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

const ll LINF = 4e18;
const int mxN = 1e7+10, INF = 2e9;
ll n, m;
int root2D;
vector<ll> node;
vector<array<int, 2> > ch;

int Node(){ node.pb(0); ch.pb({-1, -1}); return node.size()-1; }

int Node2(){ int s = Node(); node[s] = Node(); return s; }

int Child(int s, int i){ if (!~s) return -1; if (!~ch[s][i]) ch[s][i] = Node(); return ch[s][i]; }

int Child2(int s, int i){ if (!~s) return -1; if (!~ch[s][i]) ch[s][i] = Node2(); return ch[s][i]; }

int _Child(int s, int i){ if (!~s) return -1; return ch[s][i]; }

ll Val(int s){ return (~s ? node[s] : 0); }

void Print(int s, ll l, ll r){
    if (!~s) return;
    cout << tb << tb << s << sp << l << sp << r << sp << node[s] << en;
    ll m = (l + r)>>1;
    Print(ch[s][0], l, m);
    Print(ch[s][1], m+1, r);
}
void Print(int s){ cout << tb << "SEGTREE\n"; Print(s, 0, n-1); cout << en; }

void Print2D(int s, ll l, ll r){
    if (!~s) return;
    cout << tb << l << sp << r << en;
    Print(node[s]);
    ll m = (l + r)>>1;
    Print2D(ch[s][0], l, m);
    Print2D(ch[s][1], m+1, r);
}
void Print2D(){ cout << "2D SEGTREE\n"; Print2D(root2D, 0, m-1); cout << en; }

void update(int s, ll l, ll r, ll pos, ll x){
    cout << tb << l << sp << r << endl;
    if (l == r){ node[s] = x; return; }
    ll m = (l + r)>>1;
    if (pos <= m) update(Child(s, 0), l, m, pos, x);
    else update(Child(s, 1), m+1, r, pos, x);
    node[s] = gcd2(Val(ch[s][0]), Val(ch[s][1]));
}
void update(int s, ll pos, ll x){ update(s, 0, n-1, pos, x); }

ll query(int s, ll l, ll r, ll ql, ll qr){
    if (l > qr || r < ql || !~s) return 0;
    if (l >= ql && r <= qr) return node[s];
    ll m = (l + r)>>1;
    ll a = query(ch[s][0], l, m, ql, qr);
    ll b = query(ch[s][1], m+1, r, ql, qr);
    return gcd2(a, b);
}
ll query(int s, ll l, ll r){ return query(s, 0, n-1, l, r); }

void update2D(int s, ll l, ll r, ll pos, array<ll, 2> args){
    cout << l << sp << r << endl;
    if (l == r){ update(node[s], args[0], args[1]); return; }
    ll m = (l + r)>>1;
    if (pos <= m) update2D(Child2(s, 0), l, m, pos, args);
    else update2D(Child2(s, 1), m+1, r, pos, args);
    ll x = (~ch[s][0] ? query(node[ch[s][0]], args[0], args[0]) : 0);
    ll y = (~ch[s][1] ? query(node[ch[s][1]], args[0], args[0]) : 0);
    update(node[s], args[0], gcd2(x, y));
}
void update2D(ll i, ll j, ll x){ update2D(root2D, 0, m-1, j, {i, x}); }

ll query2D(int s, ll l, ll r, ll ql, ll qr, array<ll, 2> args){
    if (l > qr || r < ql || !~s) return 0;
    if (l >= ql && r <= qr) return query(node[s], args[0], args[1]);
    ll m = (l + r)>>1;
    ll a = query2D(ch[s][0], l, m, ql, qr, args);
    ll b = query2D(ch[s][1], m+1, r, ql, qr, args);
    return gcd2(a, b);
}
ll query2D(ll i1, ll j1, ll i2, ll j2){ return query2D(root2D, 0, m-1, j1, j2, {i1, i2}); }

void init(int R, int C){
    n = highpow(R);
    if (bitcnt(R) > 1) n <<= 1;
    m = highpow(C);
    if (bitcnt(C) > 1) m <<= 1;
    root2D = Node2();
}

void update(int P, int Q, long long K) {
    update2D(P, Q, K);
    Print2D(); cout.flush();
}

long long calculate(int P, int Q, int U, int V) {
    return query2D(P, Q, U, V);
}
