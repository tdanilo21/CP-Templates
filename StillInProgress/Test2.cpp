#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>

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
#define rv(v) for (ll &x : v) cin >> x
#define pven(v) for (ll x : v) cout << x << en
#define pv(v) for (ll x : v) cout << x << sp; cout << en
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define yes cout << "YES" << en
#define no cout << "NO" << en
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define ssort(a, b) if (a < b) swap(a, b)
//#define bitcnt(a) __builtin_popcountll(a)
//#define bithigh(a) 64-__builtin_clzll(a)
//#define log(a) bithigh(a)-1
//#define highpow(a) (1<<log(a))

//int log(ll a) { return bithigh(a) - 1; }
ll highpow(ll a) { return 1LL << (ll)log2(a); }

using namespace std;

template<class T>
class node {
public:
    T val;
    node<T>* ch[2];
    node<T>(T val = T()) {
        this->val = val;
        this->ch[0] = this->ch[1] = nullptr;
    }
    void add(int x, T val = T()) { this->ch[x] = new node<T>(val); }

    void Print() const { val.Print(); }
    void log() const { val.log(); }
};
template<class T>
class persistent_segtree {
private:
    int n, timer;
    vector<node<T>*> roots;
    void init(int n, ll* arr) {
        this->n = n;
        if (highpow(n) ^ n) this->n = 2 * highpow(n);
        this->roots.pb(new node<T>());
        this->timer = 1;
        build(this->roots[0], 0, this->n - 1, arr);
    }
    node<T>* ch(node<T>* s, int x) {
        if (!s->ch[x]) s->add(x);
        return s->ch[x];
    }
    T build(node<T>* s, int l, int r, ll* arr) {
        if (l == r) return s->val = T(arr[l]);

        int m = (l + r) / 2;
        T a = build(ch(s, 0), l, m, arr);
        T b = build(ch(s, 1), m + 1, r, arr);
        return s->val = T::op(a, b);
    }
    T update(node<T>* s, node<T>* last, int l, int r, int pos, T x) {
        if (l > pos || r < pos) return s->val;
        if (l == r) return s->val = x;

        T a, b;
        int m = (l + r) / 2;
        if (pos <= m) {
            a = update(ch(s, 0), last->ch[0], l, m, pos, x);
            s->ch[1] = last->ch[1];
            b = s->ch[1]->val;
        }
        else {
            b = update(ch(s, 1), last->ch[1], m + 1, r, pos, x);
            s->ch[0] = last->ch[0];
            a = s->ch[0]->val;
        }
        return s->val = T::op(a, b);
    }
    T query(node<T>* s, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return T::null_v();
        if (l >= ql && r <= qr) return s->val;

        int m = (l + r) / 2;
        T a = query(s->ch[0], l, m, ql, qr);
        T b = query(s->ch[1], m + 1, r, ql, qr);
        return T::op(a, b);
    }
public:
    persistent_segtree<T>() {}
    persistent_segtree<T>(int n, ll* arr) { init(n, arr); }
    void update(int pos, ll x) { this->roots.pb(new node<T>()); this->timer++; update(this->roots[timer - 1], this->roots[timer - 2], 0, this->n - 1, pos, T(x)); }
    ll query(int l, int r, int t) { if (l > r || t > this->timer) return T::null_v().val; return query(this->roots[t - 1], 0, this->n - 1, l, r).val; }

    void Print(int t) const {
        queue<node<T>*> q;
        q.push(this->roots[t - 1]);
        while (q.size()) {
            node<T>* s = q.front(); q.pop();
            s->Print();
            if (s->ch[0]) {
                q.push(s->ch[0]);
                q.push(s->ch[1]);
            }
        }
        cout << endl;
    }
    void log(int t) const {
        queue<node<T>*> q;
        q.push(this->roots[t - 1]);
        while (q.size()) {
            node<T>* s = q.front(); q.pop();
            s->log();
            if (s->ch[0]) {
                q.push(s->ch[0]);
                q.push(s->ch[1]);
            }
        }
        cerr << endl;
    }
};
class sum_t {
public:
    ll val;

    sum_t(ll val = 0) { this->val = val; }
    static sum_t null_v() { return sum_t(0); }

    static sum_t op(const sum_t& a, const sum_t& b) { return sum_t(a.val + b.val); }
    void up(const sum_t& a) { this->val += a.val; }
    void lazy_op(const sum_t& a, int l) { up(sum_t(a.val * l)); }

    sum_t operator =(const sum_t& a) { this->val = a.val; return *this; }
    bool operator ==(const sum_t& a) const { return this->val == a.val; }
    bool operator !=(const sum_t& a) const { return this->val != a.val; }

    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }
};

const ll LINF = 4e18;
const int mxN = 2e5 + 10, INF = 2e9, mod = (1 ? 1e9 + 7 : 998244353);
ll n, m, d, q, a[mxN];
persistent_segtree<sum_t> pst;

void Solve() {

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    pst = *new persistent_segtree<sum_t>(n, a);
    pst.log(1);
    cin >> q;
    while (q--) {
        ri(t); ri(v);
        t--; v++;
        if (t) {
            ri(l); ri(r);
            l--; r--;
            cout << pst.query(l, r, v) << endl;
        }
        else {
            ri(i); ri(x);
            i--;
            pst.update(i, x);
        }
    }
    pst.Print(3);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cerr.tie(0);
    cerr << "Started!" << endl;

    int t = 1;
    //cin >> t;
    while (t--)
        Solve();

    return 0;
}
