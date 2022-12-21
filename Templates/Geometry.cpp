#define ll long long
#define ld long double
#define sp ' '
#define en '\n'
ll LINF = 1e18;
int sig(ll a){ return (!a ? 0 : (a<0 ? -1 : 1)); }
ll gcd(ll a, ll b){ if (!b) return a; return gcd(b, a%b); }
class Point{
public:
    ll x, y;
    Point(ll x, ll y){ this->x = x; this->y = y; }
    Point(){}

    Point Norm(const Point& a) const { return *this - a; }
    Point operator+(const Point& a) const { return Point(this->x + a.x, this->y + a.y); }
    Point operator-(const Point& a) const { return Point(this->x - a.x, this->y - a.y); }
    ll operator*(const Point& a) const { return this->x * a.x + this->y * a.y; }
    ll operator|(const Point& a) const { return this->x * a.y - this->y * a.x; }
    static ll dist(const Point& a, const Point& b) { return abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y); }
    static ll Manhattan(const Point& a, const Point& b) { return abs(a.x - b.x) + abs(a.y - b.y); }
    // In Orientation a is center point from which we are watching.
    static ll Orientation(const Point& a, const Point& b, const Point& c) { return sig(b.Norm(a)|c.Norm(a)); }
    static ld Area(const Point* p, int n) { ld area = 0; for (int i = 0; i < n; i++) area += (p[(i+1) % n].x - p[i].x) * (p[i].y + p[(i+1) % n].y); return area / 2; }
    bool OnSegment(const array<Point, 2>& p) const { return this->x <= max(p[0].x, p[1].x) && this->x >= min(p[0].x, p[1].x) && this->y <= max(p[0].y, p[1].y) && this->y >= min(p[0].y, p[1].y); }
    static bool Intersect(const array<Point, 2>& p, const array<Point, 2>& q) {
        int o1 = Point::Orientation(p[0], p[1], q[0]);
        int o2 = Point::Orientation(p[0], p[1], q[1]);
        int o3 = Point::Orientation(q[0], q[1], p[0]);
        int o4 = Point::Orientation(q[0], q[1], p[1]);
        if (o1^o2 && o3^o4) return 1;
        if (!o1 && q[0].OnSegment(p)) return 1;
        if (!o2 && q[1].OnSegment(p)) return 1;
        if (!o3 && p[0].OnSegment(q)) return 1;
        if (!o4 && p[1].OnSegment(q)) return 1;
        return 0;
    }
    bool Inside(const Point* p, int n) const { 
        Point extreme = Point(LINF, this->y);
        int cnt = 0;
        for (int i = 0; i < n; i++){
            if (Point::Intersect({p[i], p[(i+1) % n]}, {*this, extreme})){
                if (!Point::Orientation(p[i], p[(i+1) % n], *this))
                    return OnSegment({p[i], p[(i+1) % n]});
                cnt++;
            }
        }
        return cnt&1;
    }
    void Read() { cin >> this->x >> this->y; }
    void Print() const { cout << this->x << sp << this->y << en; }
    void log() const { cerr << this->x << sp << this->y << endl; }
};
class Line{
public:
    ll a, b, c;
    Line(ll a, ll b, ll c){ this->a = a; this->b = b; this->c = c; Norm(); }
    Line(const Point& p, const Point& q){ this->a = p.y-q.y; this->b = q.x-p.x; this->c = Point(this->b, -this->a)|p; Norm(); }
    Line(){}

    void Norm(){ if (this->a<0){ this->a *= -1; this->b *= -1; this->c *= -1; } ll t = gcd(gcd(this->a, this->b), this->c); this->a /= t; this->b /= t; this->c /= t; }
    bool operator==(const Line& l) const { if (this->a^l.a || this->b^l.b || this->c^l.c) return false; return true; }
    ld f(ll x) const { return -(ld)(this->a * x + this->c) / (ld)this->b; }
    ld dist(const Point& p) const { return (ld)abs(this->a * p.x + this->b * p.y + this->c) / sqrt(this->a * this->a + this->b * this->b); }
    ll side(const Point& p) const { return sig(this->a*p.x + this->b*p.y - this->c); }
    void Read(){ cin >> this->a >> this->b >> this->c; Norm(); }
    void Print() const { cout << this->a << sp << this->b << sp << this->c << en; }
    void log() const { cerr << this->a << sp << this->b << sp << this->c << endl; }
};
