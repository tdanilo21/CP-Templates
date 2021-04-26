#define ll long long
class min_t{
public:
    ll val;

    min_t(ll val = 0){ this->val = val; }
    static min_t null_v(){ return min_t(-LINF); }

    static min_t op(const min_t& a, const min_t& b){ return min_t(min(a.val, b.val)); }
    void up(const min_t& a){ this->val += a.val; }
    void lazy_op(const min_t& a, int l){ up(a); }
    void Print() const { cout << this->val << sp; }

    min_t operator =(const min_t& a){ this->val = a.val; return *this; }
    bool operator ==(const min_t& a) const { return this->val == a.val; }
    bool operator !=(const min_t& a) const { return this->val != a.val; }
};