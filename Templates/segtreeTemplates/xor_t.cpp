#define ll long long
#define sp ' '
class xor_t{
public:
    ll val;

    xor_t(ll val = 0){ this->val = val; }
    static xor_t null_v(){ return xor_t(0); }

    static xor_t op(const xor_t& a, const xor_t& b){ return xor_t(a.val^b.val); }
    // This is currently on set mode.
    xor_t up(const xor_t& a){ return *this = a; }
    void lazy_op(const xor_t& a, int l){ if (l>1) up(0); else up(a); }

    xor_t operator =(const xor_t& a){ this->val = a.val; return *this; }
    xor_t operator +=(const xor_t& a) { this->val += a.val; return *this; }
    xor_t operator -=(const xor_t& a) { this->val -= a.val; return *this; }
    xor_t operator +(const xor_t& a) const { return xor_t(this->val + a.val); }
    xor_t operator -(const xor_t& a) const { return xor_t(this->val - a.val); }
    bool operator ==(const xor_t& a) const { return this->val == a.val; }
    bool operator !=(const xor_t& a) const { return this->val != a.val; }
    
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }
};
