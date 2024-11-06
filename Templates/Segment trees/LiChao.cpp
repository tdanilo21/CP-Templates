#define ll long long
#define pb push_back
const ll LINF = 2e18;
struct Line{
 
    ll k, n;
    Line(ll _k = 0, ll _n = LINF){ k = _k; n = _n; }
    ll operator()(ll x) const { return k*x+n; }
};
class LiChao{
 
    ll L, R;
    vector<Line> tree;
    vector<array<int, 2> > ch;
 
    int Node(){ tree.pb(Line()); ch.pb({-1, -1}); return tree.size()-1; }
 
    int Child(int s, int i){ if (!~ch[s][i]){ int u = Node(); ch[s][i] = u; } return ch[s][i]; }
 
    void Insert(int s, int l, int r, Line f){
        int m = (l + r)>>1;
        if (f(m) < tree[s](m)) swap(tree[s], f);
        if (f(l) < tree[s](l)) Insert(Child(s, 0), l, m, f);
        if (f(r) < tree[s](r)) Insert(Child(s, 1), m+1, r, f);
    }
 
    ll Get(int s, int l, int r, ll x) const {
        if (!~s) return LINF;
        int m = (l + r)>>1;
        if (x <= m) return min(tree[s](x), Get(ch[s][0], l, m, x));
        return min(tree[s](x), Get(ch[s][1], m+1, r, x));
    }
 
public:
    LiChao(ll l, ll r){ Assign(l, r); }
    void Assign(ll l, ll r){
        L = l; R = r;
        tree.clear(); ch.clear();
        Node();
    }
    void Insert(ll k, ll n){ Insert(0, L, R, Line(k, n)); }
    ll Get(ll x) const { return Get(0, L, R, x); }
};
