#include <bits/stdc++.h>
#include "code.h"

#define ll long long
#define ld long double
#define pb push_back
#define fi first
#define se second
#define en '\n'
#define sp ' '
#define tb '\t'
#define ri(n) int n; cin >> n
#define rl(n) ll n; cin >> n
#define rs(s) string s; cin >> s
#define rc(c) char c; cin >> c
#define rv(v) for (auto &x : v) cin >> x
#define pven(v) for (auto x : v) cout << x << en
#define pv(v) for (auto x : v) cout << x << sp; cout << en
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define yes cout << "YES" << en
#define no cout << "NO" << en
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define ssort(a, b) if (a < b) swap(a, b)
#define bitcnt(a) __builtin_popcountll(a)
#define bithigh(a) 63-__builtin_clzll(a)
#define lg bithigh
ll highpow(ll a) { return 1LL << (ll)lg(a); }

using namespace std;

struct Point{

    ll x, y;
    ll Dist(const Point& p) const { return x*p.x + y*p.y; }
    int Turn(const Point& a, const Point& b) const {
        ll t = (a.x - x) * (b.y - y) - (a.y - y) * (b.x - x);
        if (t) t /= abs(t);
        return t; // (-1, 0, 1) => (clockwise, paralel, anti-clockwise)
    }
    bool OnSegment(const array<Point, 2>& p) const { return !Turn(p[0], p[1]) && max(p[0].x, p[1].x) >= x && min(p[0].x, p[1].x) <= x; }
    static bool Intersect(const array<Point, 2>& a, const array<Point, 2>& b){
        int o1 = a[0].Turn(a[1], b[0]);
        int o2 = a[0].Turn(a[1], b[1]);
        int o3 = b[0].Turn(b[1], a[0]);
        int o4 = b[0].Turn(b[1], a[1]);
        return o1*o2 <= 0 && o3*o4 <= 0;
    }
    bool Inside(const vector<Point>& points) const {
        if (points.size() == 1) return x == points[0].x && y == points[0].y;
        Point extreme = {INT_MAX, 0};
        int cnt = 0;
        for (int i = 0; i < points.size(); i++){
            array<Point, 2> d = {points[i], points[(i+1) % points.size()]};
            if (Point::Intersect(d, {*this, extreme})) cnt++;
            if (OnSegment(d)) return 1;
        }
        return cnt&1;
    }
    bool operator<(const Point& p) const { return y < p.y || (y == p.y && x < p.x); }
    bool operator>(const Point& p) const { return y > p.y || (y == p.y && x > p.x); }
};

Point C;

bool cmp(const Point& a, const Point& b){

    if (a.x == C.x && a.y == C.y) return 1;
    int t = C.Turn(a, b);
    if (!t) return C.Dist(a) < C.Dist(b);
    return t > 0;
}

vector<Point> GrahamScan(vector<Point> points){
    int mn = 0;
    for (int i = 0; i < points.size(); i++)
        if (points[i] < points[mn]) mn = i;
    swap(points[0], points[mn]);
    C = points[0];
    sort(points.begin()+1, points.end(), cmp);
    int n = 1;
    for (int i = 1; i < points.size(); i++){
        while (i < points.size()-1 && !C.Turn(points[i], points[i+1])) i++;
        points[n++] = points[i];
    }
    if (n <= 3) return vector<Point>(points.begin(), points.begin() + n);
    vector<Point> Hull = {points[0], points[1]};
    for (int i = 2; i < n; i++){
        while (Hull.size() > 1 && Hull.back().Turn(points[i], Hull[Hull.size()-2]) != 1)
            Hull.pop_back();
        Hull.pb(points[i]);
    }
    return Hull;
}

void Print(const vector<Point>& points){ for (auto p : points) cout << "(" << p.x << ", " << p.y << ") "; cout << en; }

template<class T>
struct Sparse{

    int n;
    vector<vector<Point> > lookup;
    Sparse(int s, const vector<Point>& points){
        n = s;
        lookup = vector<vector<Point> >(n, vector<Point>(lg(n)+1, T::null_v()));
        for (int i = 0; i < n; i++) lookup[i][0] = points[i];
        for (int d = 1; d <= lg(n); d++)
            for (int i = 0; i < n; i++)
                if (i+(1<<d) < n)
                    lookup[i][d] = T::op(lookup[i][d-1], lookup[i + (1<<d)][d-1]);
        for (int i = 0; i < n; i++){
            Print(lookup[i]);
            cout << en;
        }
    }
    Point query(int l, int r) const {
        if (l>r) return T::null_v();
        int d = highpow(r-l+1);
        return T::op(lookup[l][lg(d)], query(l+d, r));
    }
};

struct Min{
    static Point null_v(){ return {INT_MAX, INT_MAX}; }
    static Point op(const Point& a, const Point& b){ return min(a, b); }
};

struct Max{
    static Point null_v(){ return {INT_MIN, INT_MIN}; }
    static Point op(const Point& a, const Point& b){ return max(a, b); }
};

const ll LINF = 4e18;
const int mxN = 2e5+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
ll n, m;
Point P;
vector<Point> a;
Sparse<Min> *min_st[2];
Sparse<Max> *max_st[2];

vector<array<int, 2> > Check(const Point& p, const Point& q){

    set<Point> s;
    for (int i = 0; i < n; i++)
        if (p.Turn(q, a[i]))
            s.insert(a[i]);
    vector<array<int, 2> > w(n, {1, 0});
    if (s.empty()) return w;
    Point t = *s.begin();
    if (s.size() == 1){
        for (int i = 0; i < n; i++)
            if (a[i].x == t.x && a[i].y == t.y)
                swap(w[i][0], w[i][1]);
        return w;
    }
    Point r = *s.rbegin();

    for (int i = 0; i < n; i++){
        w[i][0] = (p.Turn(q, a[i]) == 0);
        w[i][1] = (t.Turn(r, a[i]) == 0);
        if (w[i][0] + w[i][1] == 0) return {};
    }
    return w;
}

vector<array<int, 2> > Find(){

    set<Point> s;
    for (int i = 0; i < n; i++) s.insert(a[i]);
    if (s.size() <= 2) return vector<array<int, 2> >(n, {1, 0});
    vector<Point> v;
    for (auto it = s.begin(); it != s.end(); it++) v.pb(*it);
    auto w = Check(v[0], v[1]);
    if (w.size()) return w;
    return {};
    w = Check(v[0], v[2]);
    if (w.size()) return w;
    return Check(v[1], v[2]);
}

void initSparse(const vector<array<int, 2> >& w){

    vector<Point> p1(n, Min::null_v()), p2(n, Min::null_v());
    for (int i = 0; i < n; i++){
        if (w[i][0]) p1[i] = a[i];
        if (w[i][1]) p2[i] = a[i];
    }
    min_st[0] = new Sparse<Min>(n, p1);
    min_st[1] = new Sparse<Min>(n, p2);
    for (int i = 0; i < n; i++){
        if (p1[i].x == Min::null_v().x) p1[i] = Max::null_v();
        if (p2[i].x == Min::null_v().x) p2[i] = Max::null_v();
    }
    max_st[0] = new Sparse<Max>(n, p1);
    max_st[1] = new Sparse<Max>(n, p2);
}

void Resi(int N, int Px, int Py, int *X, int *Y, int Q, int *L, int *R, bool *O){

    n = N;
    P = {Px, Py};
    for (int i = 1; i <= N; i++) a.pb({X[i], Y[i]});
    auto w = Find();
    if (w.empty()){
        for (int i = 1; i <= Q; i++){
            auto Hull = GrahamScan(vector<Point>(a.begin() + L[i]-1, a.begin() + R[i]));
            O[i] = P.Inside(Hull);
        }
        return;
    }
    for (int i = 0; i < n; i++)
        cout << w[i][0] << sp << w[i][1] << en;
    initSparse(w);
    for (int i = 1; i <= Q; i++){
        L[i]--; R[i]--;
        array<Point, 2> p = {min_st[0]->query(L[i], R[i]), max_st[0]->query(L[i], R[i])};
        array<Point, 2> q = {min_st[1]->query(L[i], R[i]), max_st[1]->query(L[i], R[i])};
        if (p[0].x == Min::null_v().x) swap(p, q);
        vector<Point> points = {p[0], p[1]};
        if (q[0].x != Min::null_v().x){ points.pb(q[1]); points.pb(q[0]); }
        O[i] = P.Inside(points);
    }
}
