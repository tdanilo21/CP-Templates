#define ll long long
class and_t{
public:
    ll val;

    and_t(ll val = 0){ this->val = val; }
    static and_t null_v(){ return and_t((1LL<<63LL)-1LL); }

    static and_t op(const and_t& a, const and_t& b){ return and_t(a.val&b.val); }
    // This is currently on set mode.
    void up(const and_t& a){ this->val = a.val; }
    void lazy_op(const and_t& a, int l){ up(a); }
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }

    and_t operator =(const and_t& a){ this->val = a.val; return *this; }
    bool operator ==(const and_t& a) const { return this->val == a.val; }
    bool operator !=(const and_t& a) const { return this->val != a.val; }
};
