#define ll long long
#define pb push_back
#define en '\n'
#define bithigh(a) 64-__builtin_clzll(a)
int log(ll a) { return bithigh(a) - 1; }
ll highpow(ll a) { return 1LL << (ll)log(a); }
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
    void init(int n, auto* arr) {
        this->n = n;
        if (highpow(n) ^ n) this->n = 2*highpow(n);
        this->roots.pb(new node<T>());
        this->timer = 1;
        build(this->roots[0], 0, this->n-1, arr);
    }
    node<T>* ch(node<T>* s, int x) {
        if (!s->ch[x]) s->add(x);
        return s->ch[x];
    }
    T build(node<T>* s, int l, int r, auto* arr) {
        if (l == r) return s->val = T(arr[l]);

        int m = (l + r) / 2;
        T a = build(ch(s, 0), l, m, arr);
        T b = build(ch(s, 1), m+1, r, arr);
        return s->val = T::op(a, b);
    }
    T update(node<T>* s, node<T>* last, int l, int r, int pos, T x) {
        if (l > pos || r < pos) return s->val;
        if (l == r){
            s->val = last->val;
            return s->val.up(x);
        }

        T a, b;
        int m = (l + r) / 2;
        if (pos <= m) {
            a = update(ch(s, 0), last->ch[0], l, m, pos, x);
            s->ch[1] = last->ch[1];
            b = s->ch[1]->val;
        }
        else {
            b = update(ch(s, 1), last->ch[1], m+1, r, pos, x);
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
        T b = query(s->ch[1], m+1, r, ql, qr);
        return T::op(a, b);
    }
public:
    persistent_segtree<T>() {}
    persistent_segtree<T>(int n, auto* arr) { init(n, arr); }
    void update(int pos, auto x, int t = -1) {
        if (!~t) t = this->timer-1;
        assert(t < this->timer);
        this->roots.pb(new node<T>());
        this->timer++;
        update(this->roots[this->timer-1], this->roots[t], 0, this->n-1, pos, T(x));
    }
    auto query(int l, int r, int t = -1) {
        if (!~t) t = this->timer-1;
        assert(t < this->timer);
        if (l > r) return T::null_v().val;
        return query(this->roots[t], 0, this->n-1, l, r).val;
    }

    void Print(int t) const {
        assert(t < this->timer);
        queue<node<T>*> q;
        q.push(this->roots[t]);
        while (q.size()) {
            node<T>* s = q.front(); q.pop();
            s->Print();
            if (s->ch[0]) {
                q.push(s->ch[0]);
                q.push(s->ch[1]);
            }
        }
        cout << en;
    }
    void log(int t) const {
        assert(t < this->timer);
        queue<node<T>*> q;
        q.push(this->roots[t]);
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
