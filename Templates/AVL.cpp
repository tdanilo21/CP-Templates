#define ll long long
class AVL{

    int n, root;
    vector<ll> tree;
    vector<int> h, sz, l, r;
    queue<int> free;

    void Assign(int s, ll x){
        tree[s] = x;
        h[s] = sz[s] = 1;
        l[s] = r[s] = -1;
    }

    int Make(ll x){
        n++;
        int s = free.front(); free.pop();
        Assign(s, x);
        return s;
    }

    void Erase(int s){
        free.push(s);
        n--;
    }

    int Height(int s) const { return (~s ? h[s] : 0); }
    int Size(int s) const { return (~s ? sz[s] : 0); }

    void Update(int s){ h[s] = max(Height(l[s]), Height(r[s])) + 1; sz[s] = Size(l[s]) + Size(r[s]) + 1; }

    int Rrot(int s){
        int u = l[s];
        l[s] = r[u];
        r[u] = s;
        Update(s); Update(u);
        return u;
    }

    int Lrot(int s){
        int u = r[s];
        r[s] = l[u];
        l[u] = s;
        Update(s); Update(u);
        return u;
    }

    ll Min(int s) const { if (!~l[s]) return tree[s]; return Min(l[s]); }
    ll Max(int s) const { if (!~r[s]) return tree[s]; return Max(r[s]); }

    int BF(int s) const { return Height(l[s]) - Height(r[s]); }

    int Balance(int s){
        if (BF(s) < -1){
            if (BF(r[s]) > 0) r[s] = Rrot(r[s]);
            s = Lrot(s);
        }
        else if (BF(s) > 1){
            if (BF(l[s]) < 0) l[s] = Lrot(l[s]);
            s = Rrot(s);
        }
        return s;
    }

    int Insert(int s, ll x){
        if (!~s) return Make(x);
        if (x < tree[s]) l[s] = Insert(l[s], x);
        else r[s] = Insert(r[s], x);
        Update(s);
        return Balance(s);
    }

    int Delete(int s, ll x){
        if (!~s) return s;
        if (x == tree[s]){
            if (!~l[s] && !~r[s]){ Erase(s); return -1; }
            if (!~r[s]){
                int v = Max(l[s]);
                tree[s] = v;
                l[s] = Delete(l[s], v);
            }
            else{
                int v = Min(r[s]);
                tree[s] = v;
                r[s] = Delete(r[s], v);
            }
        }
        else if (x < tree[s]) l[s] = Delete(l[s], x);
        else r[s] = Delete(r[s], x);
        Update(s);
        return Balance(s);
    }

    int Get(int s, ll x) const {
        if (!~s) return 0;
        if (x == tree[s]) return Size(r[s]);
        if (x > tree[s]) return Get(r[s], x);
        return Size(r[s]) + 1 + Get(l[s], x);
    }

    vector<int> Dfs(int s) const {
        if (!~s) return {};
        vector<int> v = {s};
        auto a = Dfs(l[s]);
        auto b = Dfs(r[s]);
        for (int u : a) v.pb(u);
        for (int u : b) v.pb(u);
        return v;
    }

public:
    AVL(int s){
        n = 0; root = -1;
        tree.resize(s); h.resize(s); sz.resize(s); l.resize(s); r.resize(s);
        for (int i = 0; i < s; i++) free.push(i);
    }
    void Insert(ll x){ root = Insert(root, x); }
    void Delete(ll x){ root = Delete(root, x); }
    int Get(ll x) const { return Get(root, x); }

    void Print() const {
        auto v = Dfs(root);
        for (int s : v)
            cout << tree[s] << ": " << (~l[s] ? tree[l[s]] : -1) << sp << (~r[s] ? tree[r[s]] : -1) << en;
        cout.flush();
    }
};
