#define ll long long
#define ld long double
#define sp ' '
#define en '\n'
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
    // In Orientation this is center point from which we are watching.
    int Orientation(const Point& a, const Point& b) const { return sig(a.Norm(*this)|b.Norm(*this)); }
    static ll Area(const Point* p, int n) { ll area = 0; for (int i = 0; i < n; i++) area += p[i]|p[(i+1)%n]; return abs(area); }
    bool OnSegment(const Point& p, const Point& q) const {
        if (Orientation(p, q)) return 0;
        return this->x <= max(p.x, q.x) && this->x >= min(p.x, q.x) && this->y <= max(p.y, q.y) && this->y >= min(p.y, q.y);
    }
    static bool Intersect(const array<Point, 2>& p, const array<Point, 2>& q) {
        int o1 = q[0].Orientation(p[0], p[1]);
        int o2 = q[1].Orientation(p[0], p[1]);
        int o3 = p[0].Orientation(q[0], q[1]);
        int o4 = p[1].Orientation(q[0], q[1]);
        if (o1^o2 && o3^o4) return 1;
        if (q[0].OnSegment(p[0], p[1])) return 1;
        if (q[1].OnSegment(p[0], p[1])) return 1;
        if (p[0].OnSegment(q[0], q[1])) return 1;
        if (p[1].OnSegment(q[0], q[1])) return 1;
        return 0;
    }
    // Returns (0, 1, 2) -> (out, in, boundary)
    int Inside(const Point* p, int n) const {
        int cnt = 0;
        for (int i = 0; i < n; i++){
            if (OnSegment(p[i], p[(i+1) % n])) return 2;
            if (p[i].x <= x && p[(i+1)%n].x > x && Orientation(p[i], p[(i+1)%n]) < 0) cnt++;
            else if (p[(i+1)%n].x <= x && p[i].x > x && Orientation(p[(i+1)%n], p[i]) < 0) cnt++;
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
