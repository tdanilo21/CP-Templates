#define ll long long
#define en '\n'
template<class T>
class segtree{
private:
    int n;
    vector<T> tree, lazy;
    vector<bool> f;
    void init(int n){
        int t = (int)log2(n);
        if ((1<<t)^n) t++;
        this->n = (1<<t);
        this->tree = vector<T>(2 * this->n, T());
        this->lazy = vector<T>(2 * this->n, T());
        this->f = vector<bool>(2 * this->n, 0);
    }
    T init(int s, int l, int r, auto* arr){
        if (l == r) return this->tree[s] = T(arr[l]);
        
        int m = (l + r) / 2;
        T a = init(2*s, l, m, arr);
        T b = init(2*s+1, m+1, r, arr);
        return this->tree[s] = T::op(a, b);
    }
    T update(int s, int l, int r, int ul, int ur, T x){
        eval_lazy(s, l, r);
        if (l > ur || r < ul) return this->tree[s];
        if (l >= ul && r <= ur){
            this->lazy[s].up(x);
            this->f[s] = 1;
            eval_lazy(s, l, r);
            return this->tree[s];
        }

        int m = (l + r) / 2;
        T a = update(2*s, l, m, ul, ur, x);
        T b = update(2*s+1, m+1, r, ul, ur, x);
        return this->tree[s] = T::op(a, b);
    }
    T query(int s, int l, int r, int ql, int qr) {
        eval_lazy(s, l, r);
        if (l > qr || r < ql) return T::null_v();
        if (l >= ql && r <= qr) return tree[s];

        int m = (l + r) / 2;
        T a = query(2*s, l, m, ql, qr);
        T b = query(2*s+1, m+1, r, ql, qr);
        return T::op(a, b);
    }
    void eval_lazy(int s, int l, int r){
        if (!this->f[s]) return;
        this->tree[s].lazy_op(this->lazy[s], r-l+1);
        if (l^r){
            this->lazy[2*s].up(this->lazy[s]);
            this->f[2*s] = 1;
            this->lazy[2*s+1].up(this->lazy[s]);
            this->f[2*s+1] = 1;
        }
        this->lazy[s] = T();
        this->f[s] = 0;
    }
public:
    segtree(int n = 0){ init(n); }
    segtree(int n, auto* arr){ init(n); init(1, 0, this->n - 1, arr); }

    void update(int l, int r, auto x) { update(1, 0, this->n-1, l, r, T(x)); }
    auto query(int l, int r) { if (l>r) return T::null_v().val; return query(1, 0, this->n-1, l, r).val; }
    
    void PrintTree() const { for (int i = 1; i < 2*this->n; i++) this->tree[i].Print(); cout << en; }
    void PrintLazy() const { for (int i = 1; i < 2*this->n; i++) this->lazy[i].Print(); cout << en; }
    void logTree() const { for (int i = 1; i < 2*this->n; i++) this->tree[i].log(); cerr << endl; }
    void logLazy() const { for (int i = 1; i < 2*this->n; i++) this->lazy[i].log(); cerr << endl; }
};
