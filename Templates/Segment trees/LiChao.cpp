#define ll long long
const ll LINF = 4e18;
class LiChao{

    int ln, rn, n;
    vector<Line> tree;
    vector<array<int, 2> > ch;

    int Child(int s, int i){ if (!~ch[s][i]) ch[s][i] = ++n; return ch[s][i]; }

    void init(int l, int r, int t){
        ln = l; rn = r; n = 1;
        tree.assign(t+10, {0, LINF});
        ch.assign(t+10, {-1, -1});
    }

    void Insert(int s, int l, int r, Line f){
        if (tree[s](l) <= f(l) && tree[s](r) <= f(r)) return;
        if (tree[s](l) > f(l) && tree[s](r) > f(r)){ swap(tree[s], f); return; }

        if (tree[s](l) > f(l)) swap(tree[s], f);

        int m = (l + r)>>1;
        if (tree[s](m) > f(m)){
            swap(tree[s], f);
            Insert(Child(s, 0), l, m, f);
        }
        else Insert(Child(s, 1), m+1, r, f);
    }

    ll query(int s, int l, int r, ll x) const {
        if (!~s) return LINF;
        int m = (l + r)>>1;
        if (x <= m) return min(query(ch[s][0], l, m, x), tree[s](x));
        return min(query(ch[s][1], m+1, r, x), tree[s](x));
    }

public:
    LiChao(int l = 0, int r = 0, int t = 0){ init(l, r, t); }
    void Insert(Line f){ Insert(0, ln, rn, f); }
    ll query(ll x) const { return query(0, ln, rn, x); }
};
