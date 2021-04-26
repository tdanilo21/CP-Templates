#define ll long long
class or_t{
public:
    ll val;

    or_t(ll val = 0){ this->val = val; }
    static or_t null_v(){ return or_t(0); }

    static or_t op(const or_t& a, const or_t& b){ return or_t(a.val|b.val); }
    // This is currently on set mode.
    void up(const or_t& a){ this->val = a.val; }
    void lazy_op(const or_t& a, int l){ up(a); }
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }

    or_t operator =(const or_t& a){ this->val = a.val; return *this; }
    bool operator ==(const or_t& a) const { return this->val == a.val; }
    bool operator !=(const or_t& a) const { return this->val != a.val; }
};
