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

struct gcd_t{

    ll x;
    gcd_t(ll v = 0){ update(v); }
    static gcd_t op(const gcd_t& a, const gcd_t& b){ return gcd_t(gcd2(a.x ,b.x)); }
    void update(ll v){ x = v; }
    ll query(){ return x; }
};

template<class T>
struct node{

    T val;
    node<T>* ch[2];
    node<T>(const T& v = T()){ Assign(v); }
    node<T>(node<T>* p){ Assign(p->val); }
    ~node<T>(){ delete ch[0]; delete ch[1]; }
    void Assign(const T& v){
        val = T(v);
        ch[0] = ch[1] = nullptr;
    }
    node<T>* Ch(int i, const T& a = T()){
        if (!ch[i]) ch[i] = new node<T>(a);
        return ch[i];
    }
    static node<T>* op(node<T>* a, node<T>* b){
        if (!a) return new node<T>(b);
        if (!b) return new node<T>(a);
        return new node<T>(T::op(a->val, b->val));
    }
};

class segtree{

    ll n;
    node<gcd_t>* root;

    static node<gcd_t>* op(node<gcd_t>* u, node<gcd_t>* v, ll l, ll r){
        if (!u && !v) return nullptr;
        if (l == r) return node<gcd_t>::op(u, v);
        cout << l << sp << r << endl;
        ll m = (l + r)>>1;
        node<gcd_t>* a = segtree::op((u ? u->ch[0] : nullptr), (v ? v->ch[0] : nullptr), l, m);
        node<gcd_t>* b = segtree::op((u ? u->ch[1] : nullptr), (v ? v->ch[1] : nullptr), m+1, r);
        node<gcd_t>* s = node<gcd_t>::op(a, b);
        s->ch[0] = a; s->ch[1] = b;
        return s;
    }

    gcd_t update(node<gcd_t>* s, ll l, ll r, ll pos, ll x){
        //cout << l << sp << r << endl;
        if (l == r){
            s->val.update(x);
            return s->val;
        }
        int m = (l + r)>>1;
        gcd_t a = gcd_t(), b = gcd_t();
        if (pos <= m){
            a = update(s->Ch(0), l, m, pos, x);
            if (s->ch[1]) b = s->ch[1]->val;
        }
        else{
            b = update(s->Ch(1), m+1, r, pos, x);
            if (s->ch[0]) a = s->ch[0]->val;
        }
        return s->val = gcd_t::op(a, b);
    }

    gcd_t query(node<gcd_t>* s, ll l, ll r, ll ql, ll qr) const {
        if (l > qr || r < ql || !s) return gcd_t();
        if (l >= ql && r <= qr) return s->val;
        ll m = (l + r)>>1;
        gcd_t a = query(s->ch[0], l, m, ql, qr);
        gcd_t b = query(s->ch[1], m+1, r, ql, qr);
        return gcd_t::op(a, b);
    }

public:
    segtree(ll n = 0){ Assign(n); }
    segtree(const segtree& st){ Assign(st.n); }
    void Assign(ll s){
        n = highpow(s);
        if (bitcnt(s) > 1) n <<= 1;
        root = new node<gcd_t>();
    }
    ll Size() const { return n; }
    static segtree op(const segtree& a, const segtree& b){
        segtree r(a.n);
        delete r.root;
        cout << a.n << endl;
        a.Print(a.root, 0, a.n-1);
        cout << b.n << endl;
        b.Print(b.root, 0, b.n-1);
        r.root = segtree::op(a.root, b.root, 0, a.n-1);
        return r;
    }
    void update(ll pos, ll x){ update(root, 0, n-1, pos, x); }
    gcd_t query(ll l, ll r) const { return query(root, 0, n-1, l, r); }
    void Print(node<gcd_t>* s, ll l, ll r) const {
        cout << l << sp << r << sp << s->val.x << endl;
        ll m = (l + r)>>1;
        if (s->ch[0]) Print(s->ch[0], l, m);
        if (s->ch[1]) Print(s->ch[1], m+1, r);
    }
};

class segtree2D{

    ll n;
    node<segtree>* root;

    segtree update(node<segtree>* s, ll l, ll r, ll pos, array<ll, 2> args){
        if (l == r){
            s->val.update(args[0], args[1]);
            return s->val;
        }
        ll m = (l + r)>>1;
        ll n = s->val.Size();
        segtree a = segtree(n), b = segtree(n);
        if (pos <= m){
            a = update(s->Ch(0, segtree(n)), l, m, pos, args);
            if (s->ch[1]) b = s->ch[1]->val;
        }
        else{
            b = update(s->Ch(1, segtree(n)), m+1, r, pos, args);
            if (s->ch[0]) a = s->ch[0]->val;
        }
        return s->val = segtree::op(a, b);
    }

    gcd_t query(node<segtree>* s, ll l, ll r, ll ql, ll qr, array<ll, 2> args) const {
        if (l > qr || r < ql || !s) return gcd_t();
        if (l >= ql && r <= qr) return s->val.query(args[0], args[1]);
        ll m = (l + r)>>1;
        gcd_t a = query(s->ch[0], l, m, ql, qr, args);
        gcd_t b = query(s->ch[1], m+1, r, ql, qr, args);
        return gcd_t::op(a, b);
    }

public:
    segtree2D(ll n = 0, const segtree& st = segtree()){ Assign(n, st); }
    void Assign(ll r, const segtree& st){
        n = highpow(r);
        if (bitcnt(r) > 1) n <<= 1;
        root = new node<segtree>(st);
    }
    void update(ll pos, array<ll, 2> args){ update(root, 0, n-1, pos, args); }
    ll query(ll l, ll r, array<ll, 2> args){ return query(root, 0, n-1, l, r, args).x; }
};

const ll LINF = 4e18;
const int mxN = 1e3+10, INF = 2e9;
ll n, m, a[mxN];
segtree2D st;

void init(int R, int C){
    st.Assign(C, segtree(R));
}

void update(int P, int Q, long long K) {
    cout << 1 << endl;
    st.update(Q, {P, K});
}

long long calculate(int P, int Q, int U, int V) {
    cout << 2 << endl;
    return st.query(Q, V, {P, U});
}
