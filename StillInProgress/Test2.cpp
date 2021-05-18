// This is a persistent segment tree that I am working on.
// It's yet to be tested so it is not available as finished version.
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
class persistent_segtree{
private:
    int n, timer;
    vector<node*> roots;
    void init(int n, auto* arr){
        int t = (int)log2(n);
        if ((1<<t)^n) t++;
        this->n = (1<<t);
        this->roots.pb(new node(T()));
        this->timer = 1;
        init(this->roots[0], 0, this->n-1, arr);
    }
    node* ch(node* s, int x){
        if (!s->ch[x]) s->add(x);
        return s->ch[x];
    }
    T init(node* s, int l, int r, auto* arr){
        if (l == r) return s->val = T(arr[l]);

        int m = (l + r) / 2;
        T a = init(ch(s, 0), l, m, arr);
        T b = init(ch(s, 1), m+1, r, arr);
        return T::op(a, b);
    }
    T update(node* s, node* last, int l, int r, int pos, T x){
        if (l > pos || r < pos) return s->val;
        if (l == r) return s->val = x;

        T a, b;
        int m = (l + r) / 2;
        if (pos <= m){
            a = update(ch(s, 0), last->ch[0], l, m, pos, x);
            s->ch[1] = last->ch[1];
            b = s->ch[1]->val;
        }
        else{
            b = update(ch(s, 1), last->ch[1], m+1, r, pos, x);
            s->ch[0] = last->ch[0];
            a = s->ch[0]->val;
        }
        return s->val = T::op(a, b);
    }
    T query(node* s, int l, int r, int ql, int qr){
        if (l > qr || r < ql) return T::null_v();
        if (l >= ql && r <= qr) return s->val;

        int m = (l + r) / 2;
        T a = query(s->ch[0], l, m, ql, qr);
        T b = query(s->ch[1], m+1, r, ql, qr);
        return T::op(a, b);
    }
public:
    persistent_segtree(){}
    persistent_segtree(int n, auto* arr){ init(n, arr); }
    void update(int pos, auto x){ this->roots.pb(new node(T())); this->timer++; update(this->roots[timer-1], this->roots[timer-2], 0, this->n-1, pos, T(x)); }
    auto query(int l, int r, int t = this->timer){ if (l > r) return T::null_v().val; query(this->roots[t-1], 0, this->n-1, l, r); }
}
