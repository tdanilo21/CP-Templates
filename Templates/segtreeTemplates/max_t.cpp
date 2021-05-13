#define ll long long
#define sp ' '
class max_t{
public:
    ll val;

    max_t(ll val = 0){ this->val = val; }
    static max_t null_v(){ return max_t(-LINF); }

    static max_t op(const max_t& a, const max_t& b){ return max_t(max(a.val, b.val)); }
    // This is currently on set mode but it can be on add.
    void up(const max_t& a){ this->val = a.val; }
    void lazy_op(const max_t& a, int l){ up(a); }
    void Print() const { cout << this->val << sp; }
    void log() const { cerr << this->val << sp; }

    max_t operator =(const max_t& a){ this->val = a.val; return *this; }
    bool operator ==(const max_t& a) const { return this->val == a.val; }
    bool operator !=(const max_t& a) const { return this->val != a.val; }
};
