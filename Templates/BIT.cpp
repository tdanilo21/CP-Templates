class BIT{

    int n;
    vector<ll> tree;

    ll query(int pos) const {
        if (pos > n) pos = n;
        ll sum = 0;
        for (; pos; pos -= (pos & (-pos)))
            sum += tree[pos];
        return sum;
    }
public:
    BIT(int s = 0){ Assign(s); }
    
    void Assign(int s = 0){ n = s; tree.assign(s+1, 0); }
    
    ll query(int l, int r) const {
        l++; r++;
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
    
    void update(int pos, ll x){
        pos++;
        if (pos <= 0) return;
        for (; pos <= n; pos += (pos & (-pos)))
            tree[pos] += x;
    }
};
