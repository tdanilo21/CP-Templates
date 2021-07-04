#define ll long long
#define sp ' '
const ll LINF = 4e18;
class min_t{
public:
    ll val;

    min_t(ll val = 0){ this->val = val; }
    static min_t null_v(){ return min_t(LINF); }

    static min_t op(const min_t& a, const min_t& b){ return min_t(min(a.val, b.val)); }
    // This is currently on set mode but it can be on add.
    min_t up(const min_t& a){ return *this = a; }
    void lazy_op(const min_t& a, int l){ up(a); }

    min_t operator =(const min_t& a){ this->val = a.val; return *this; }
    min_t operator +=(const min_t& a) { this->val += a.val; return *this; }
    min_t operator -=(const min_t& a) { this->val -= a.val; return *this; }
    min_t operator +(const min_t& a) const { return min_t(this->val + a.val); }
    min_t operator -(const min_t& a) const { return min_t(this->val - a.val); }
    bool operator ==(const min_t& a) const { return this->val == a.val; }
    bool operator !=(const min_t& a) const { return this->val != a.val; }
    
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }
};
