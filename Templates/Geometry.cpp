#define ll long long
#define ld long double
#define sp ' '
#define en '\n'
#define vec(a, b) (b-a)
ll sq(ll x){ return x*x; }
int sig(ll a){ return (!a ? 0 : (a<0 ? -1 : 1)); }
ll gcd(ll a, ll b){ if (!b) return a; return gcd(b, a%b); }
struct Point{

    ll x, y;
    static ll Dist(const Point& a, const Point& b){ return sq(a.x - b.x) + sq(a.y - b.y); }
    static ll Manhattan(const Point& a, const Point& b) { return abs(a.x - b.x) + abs(a.y - b.y); }
    static ll Area(const Point* p, int n){ ll area = 0; for (int i = 0; i < n; i++) area += p[i]|p[(i+1)%n]; return abs(area); }
    // Returns (-1, 0, 1) -> (cw, parallel, ccw)
    static int Orientation(const Point& a, const Point& b){ return sig(a | b); }
    bool OnSegment(const Point& a, const Point& b) const {
        if (Point::Orientation(vec(*this, a), vec(*this, b))) return 0;
        return x >= min(a.x, b.x) && x <= max(a.x, b.x)
            && y >= min(a.y, b.y) && y <= max(a.y, b.y);
    }
    // Returns (0, 1, 2) -> (don't intersect, do intersect, common point)
    static int Intersect(const array<Point, 2>& a, const array<Point, 2>& b){
        if (a[0].OnSegment(b[0], b[1]) || a[1].OnSegment(b[0], b[1])
            || b[0].OnSegment(a[0], a[1]) || b[1].OnSegment(a[0], a[1])) return 2;
        array<int, 2> oa = {Point::Orientation(vec(a[0], a[1]), vec(a[0], b[0])), Point::Orientation(vec(a[0], a[1]), vec(a[0], b[1]))};
        array<int, 2> ob = {Point::Orientation(vec(b[0], b[1]), vec(b[0], a[0])), Point::Orientation(vec(b[0], b[1]), vec(b[0], a[1]))};
        return oa[0] != oa[1] && ob[0] != ob[1];
    }
    // Returns (0, 1, 2) -> (out, in, boundary)
    int Inside(const Point* p, int n) const {
        int cnt = 0;
        for (int i = 0; i < n; i++){
            if (OnSegment(p[i], p[(i+1) % n])) return 2;
            if (p[i].x <= x && p[(i+1)%n].x > x && Point::Orientation(vec(*this, p[i]), vec(*this, p[(i+1)%n])) < 0) cnt++;
            else if (p[(i+1)%n].x <= x && p[i].x > x && Point::Orientation(vec(*this, p[(i+1)%n]), vec(*this, p[i])) < 0) cnt++;
        }
        return cnt&1;
    }
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    ll operator*(const Point& p) const { return x * p.x + y * p.y; }
    ll operator|(const Point& p) const { return x * p.y - p.x * y; }
    bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }

    friend istream& operator>>(istream& is, Point& p){ is >> p.x >> p.y; return is; }
    friend ostream& operator<<(ostream& os, const Point& p){ os << p.x << sp << p.y; return os; }
};
struct ConvexHull{

    vector<Point> points, hull_up, hull_down, hull_tot;
    void Reset(){ points.clear(); hull_up.clear(); hull_down.clear(); hull_tot.clear(); }
    void AddPoint(const Point& p){ points.pb(p); }
    void FindHull(){
        if (points.size() < 2){
            hull_up = hull_down = hull_tot = points;
            return;
        }
        sort(all(points));
        for (auto p : points){
            while (hull_up.size() > 1 && Point::Orientation(vec(hull_up[hull_up.size()-2], hull_up.back()), vec(hull_up.back(), p)) != -1)
                hull_up.pop_back();
            hull_up.pb(p);
            while (hull_down.size() > 1 && Point::Orientation(vec(hull_down[hull_down.size()-2], hull_down.back()), vec(hull_down.back(), p)) != 1)
                hull_down.pop_back();
            hull_down.pb(p);
        }
        for (auto p : hull_up)
            hull_tot.pb(p);
        for (int i = hull_down.size()-2; i; i--)
            hull_tot.pb(hull_down[i]);
    }
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
