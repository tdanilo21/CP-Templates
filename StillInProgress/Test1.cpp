// Working version of an implicit segment tree is available in the "Templates" folder,
// but it does not have lazy propagation.
// I am developing it so that's why it's here.
#define ll long long
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
    T update(node<T>* s, ll l, ll r, ll pos, T x){
        if (l > pos || r < pos) return s->val;
        if (l == r) return s->val = x;

        T a = T(), b = T();
        ll m = (l + r) / 2;
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
    T query(node<T>* s, ll l, ll r, ll ql, ll qr){
        if (l > qr || r < ql) return T::null_v();
        if (l >= ql && r <= qr) return s->val;

        T a = T(), b = T();
        ll m = (l + r) / 2;
        if (ql > m) a = T::null_v();
        if (qr <= m) b = T::null_v();

        if (s->ch[0]) a = query(ch(s, 0), l, m, ql, qr);
        if (s->ch[1]) b = query(ch(s, 1), m+1, r, ql, qr);
        return T::op(a, b);
    }
public:
    implicit_segtree(){}
    implicit_segtree(ll l, ll r){ init(l, r); }
    void update(ll pos, auto x){ update(this->root, this->left, this->right, pos, T(x)); }
    auto query(ll l, ll r){ if (l > r) return T::null_v().val; return query(this->root, this->left, this->right, l, r).val; }
};
