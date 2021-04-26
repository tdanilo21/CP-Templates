#define ll long long
class sum_t{
public:
    ll val;

    sum_t(ll val = 0){ this->val = val; }
    static sum_t null_v(){ return sum_t(0); }

    static sum_t op(const sum_t& a, const sum_t& b){ return sum_t(a.val + b.val); }
    // This is currently on set mode but it can be on add.
    void up(const sum_t& a){ this->val = a.val; }
    void lazy_op(const sum_t& a, int l){ up(sum_t(a.val * l)); }
    void Print() const { cout << this->val << sp; }

    sum_t operator =(const sum_t& a){ this->val = a.val; return *this; }
    bool operator ==(const sum_t& a) const { return this->val == a.val; }
    bool operator !=(const sum_t& a) const { return this->val != a.val; }
};
