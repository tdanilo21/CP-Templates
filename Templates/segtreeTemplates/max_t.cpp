#define ll long long
#define sp ' '
const ll LINF = 4e18;
class max_t{
public:
    ll val;

    max_t(ll val = 0){ this->val = val; }
    static max_t null_v(){ return max_t(-LINF); }

    static max_t op(const max_t& a, const max_t& b){ return max_t(max(a.val, b.val)); }
    // This is currently on set mode but it can be on add.
    max_t up(const max_t& a){ return *this = a; }
    void lazy_op(const max_t& a, int l){ up(a); }

    max_t operator =(const max_t& a){ this->val = a.val; return *this; }
    max_t operator +=(const max_t& a) { this->val += a.val; return *this; }
    max_t operator -=(const max_t& a) { this->val -= a.val; return *this; }
    max_t operator +(const max_t& a) const { return max_t(this->val + a.val); }
    max_t operator -(const max_t& a) const { return max_t(this->val - a.val); }
    bool operator ==(const max_t& a) const { return this->val == a.val; }
    bool operator !=(const max_t& a) const { return this->val != a.val; }
    
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }
};
