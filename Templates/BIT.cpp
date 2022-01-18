#define ll long long
class BIT{
private:
    vector<ll> tree;
    int n;

    ll query(int pos){
        if (pos > n) pos = n;
        ll sum = 0;
        while (pos > 0){
            sum += tree[pos];
            pos -= pos & (-pos);
        }
        return sum;
    }
public:
    BIT(int s){
        tree = vector<ll>(s + 1, 0);
        n = s;
    }

    ll query(int l, int r){
        l++; r++;
        if (l > r) return 0;
        return query(r) - query(l-1);
    }

    void update(int pos, ll x){
        x -= query(pos, pos);
        pos++;
        if (pos <= 0) return;
        while (pos <= n){
            tree[pos] += x;
            pos += pos & (-pos);
        }
    }
};
