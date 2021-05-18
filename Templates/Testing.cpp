#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define fi first
#define se second
#define en '\n'
#define sp ' '
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
#define bitcnt(a) __builtin_popcount(a)

using namespace std;

template<class T>
class node{
public:
    T val;
    node<T>* ch[2];
    node<T>(){}
    node<T>(T val = T()){
        this->val = val;
        this->ch[0] = this->ch[1] = nullptr;
    }
    void add(int x, T val = T()){ this->ch[x] = new node<T>(val); }
};
template<class T>
class implicit_segtree{
private:
    ll left, right;
    node<T>* root;
    void init(ll l, ll r){
        ll n = r-l+1;
        ll t = (int)log2(n);
        if ((1<<t)^n) n = 1<<(t+1);
        this->left = l;
        this->right = l+n-1;
        root = new node<T>(T());
    }
    node<T>* ch(node<T>* s, int x){
        if (!s->ch[x]) s->add(x);
        return s->ch[x];
    }
    T update(node<T>* s, int l, int r, int pos, T x){
        if (l > pos || r < pos) return s->val;
        if (l == r) return s->val = x;

        T a = T(), b = T();
        int m = (l + r) / 2;
        if (pos <= m){
            a = update(ch(s, 0), l, m, pos, x);
            if (s->ch[1]) b = ch(s, 1)->val;
        }
        else{
            b = update(ch(s, 1), m+1, r, pos, x);
            if (s->ch[0]) a = ch(s, 0)->val;
        }
        return s->val = T::op(a, b);
    }
    T query(node<T>* s, int l, int r, int ql, int qr){
        if (l > qr || r < ql) return T::null_v();
        if (l >= ql && r <= qr) return s->val;

        T a = T(), b = T();
        int m = (l + r) / 2;
        if (s->ch[0]) a = query(ch(s, 0), l, m, ql, qr);
        if (s->ch[1]) b = query(ch(s, 1), m+1, r, ql, qr);
        return T::op(a, b);
    }
public:
    implicit_segtree(){}
    implicit_segtree(ll l, ll r){ init(l, r); }
    void update(ll pos, auto x){ update(this->root, this->left, this->right, pos, T(x)); }
    auto query(ll l, ll r){ if (l > r) return T::null_v().val; return query(this->root, this->left, this->right, l, r).val; }

    void log(){
        queue<node<T>*> q;
        q.push(this->root);
        while (q.size()){
            node<T>* s = q.front(); q.pop();
            s->val.log();
            for (int i = 0; i < 2; i++)
                if (s->ch[i])
                    q.push(s->ch[i]);    
        }
        cout << en;
    }
};

const ll LINF = 4e18;
const int mxN = 4e5+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
class min_t{
public:
    ll val;

    min_t(ll val = 0){ this->val = val; }
    static min_t null_v(){ return min_t(LINF); }

    static min_t op(const min_t& a, const min_t& b){ return min_t(min(a.val, b.val)); }
    // This is currently on set mode but it can be on add.
    void up(const min_t& a){ this->val = a.val; }
    void lazy_op(const min_t& a, int l){ up(a); }
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }

    min_t operator =(const min_t& a){ this->val = a.val; return *this; }
    bool operator ==(const min_t& a) const { return this->val == a.val; }
    bool operator !=(const min_t& a) const { return this->val != a.val; }
};
ll n, a[mxN], l[mxN], r[mxN], dp[mxN], pre[mxN];
implicit_segtree<min_t> st;

void Solve(){

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    pre[0] = a[0];
    for (int i = 1; i < n; i++)
        pre[i] = pre[i-1] + a[i];
    for (int i = 1; i < n; i++){
        cin >> l[i] >> r[i];
        --l[i]; --r[i];
    }
    st = implicit_segtree<min_t>(0, n-1);
    st.update(0, 0);
    for (int i = 1; i < n; i++){
        dp[i] = pre[i] + st.query(l[i], r[i]);
        st.update(i, dp[i] - pre[i-1]);
    }
    st.log();
    for (int i = 0; i < n; i++)
        cout << dp[i] << sp;
    cout << en;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(12) << fixed;

    int t = 1;
    //cin >> t;
    while (t--)
        Solve();

    return 0;
}
