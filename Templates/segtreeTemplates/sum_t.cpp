#define ll long long
#define sp ' '
class sum_t{
public:
    ll val;

    sum_t(ll val = 0){ this->val = val; }
    static sum_t null_v(){ return sum_t(0); }

    static sum_t op(const sum_t& a, const sum_t& b){ return a + b; }
    // This is currently on set mode but it can be on add.
    sum_t up(const sum_t& a){ return *this = a; }
    void lazy_op(const sum_t& a, int l){ up(sum_t(a.val * l)); }

    sum_t operator =(const sum_t& a){ this->val = a.val; return *this; }
    sum_t operator +=(const sum_t& a) { this->val += a.val; return *this; }
    sum_t operator -=(const sum_t& a) { this->val -= a.val; return *this; }
    sum_t operator +(const sum_t& a) const { return sum_t(this->val + a.val); }
    sum_t operator -(const sum_t& a) const { return sum_t(this->val - a.val); }
    bool operator ==(const sum_t& a) const { return this->val == a.val; }
    bool operator !=(const sum_t& a) const { return this->val != a.val; }
    
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }
};
