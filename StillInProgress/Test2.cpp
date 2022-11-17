#include <bits/stdc++.h>

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
#define bitcnt(a) (__builtin_popcountll(a))
#define bithigh(a) (63-__builtin_clzll(a))
#define lg bithigh
#define highpow(a) (1LL << (ll)lg(a))

using namespace std;

struct Point{

    int x, y;
    static bool Intersect(const array<Point, 2>& a, const array<Point, 2>& b){
        if ((a[0].x == b[0].x && a[0].y == b[0].y) || (a[1].x == b[0].x && a[1].y == b[0].y)) return 0;
        if ((a[0].x == b[1].x && a[0].y == b[1].y) || (a[1].x == b[1].x && a[1].y == b[1].y)) return 0;
        if (Product(a[0], a[1], b[0]) != Product(a[0], a[1], b[1])) return 0;
        if (Product(b[0], b[1], a[0]) != Product(b[0], b[1], a[1])) return 0;
        return 1;
    }
    static int Product(const Point& a, const Point& b, const Point& c){
        ll x1 = b.x - a.x, x2 = c.x - b.x;
        ll y1 = b.y - a.y, y2 = c.y - b.y;
        ll p = x1*y2 - x2*y1;
        return p / abs(p);
    }
};

const ll LINF = 4e18;
const int mxN = 1e6+10, INF = 2e9;
string fileid = "/00.txt";
ll n, m, L, a[mxN];
Point p[mxN];
vector<int> g[mxN];
vector<array<int, 2> > edge;

ll Calc(){

    ll ans = 0;
    for (int i = 0; i < m; i++){
        for (int j = i+1; j < m; j++){
            auto [u1, v1] = edge[i];
            auto [u2, v2] = edge[j];
            if (Point::Intersect({p[a[u1]], p[a[v1]]}, {p[a[u2]], p[a[v2]]})) ans++;
        }
    }
    return ans;
}

ll Solve(ll last){

    mt19937 mt(time(NULL));
    vector<int> v;
    for (int i = 0; i < L; i++) v.pb(i);
    for (int i = 0; i < n; i++){
        int j = mt() % v.size();
        a[i] = v[j];
        v.erase(v.begin() + j);
    }
    ll ans = Calc();
    for (int t = 0; t < 50; t++){
        for (int i = 0; i < n; i++){
            for (int j = i+1; j < n; j++){
                swap(a[i], a[j]);
                ll sol = Calc();
                if (sol < ans) ans = sol;
                else swap(a[i], a[j]);
            }
        }
    }
    if (ans < last){
        ofstream f("out" + fileid, std::ofstream::out | std::ofstream::trunc);
        for (int i = 0; i < n; i++)
            f << a[i]+1 << en;
        f.close();
    }
    return ans;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cerr.tie(0);
    cout << setprecision(12) << fixed;
    cerr << setprecision(12) << fixed;
    cerr << "Started!" << endl;

    for (int t = 1; t <= 1; t++){
        fileid[2] = (char)('0' + t);
        ifstream f("in" + fileid);
        f >> n >> m;
        for (int i = 0; i < m; i++){
            int u, v;
            f >> u >> v;
            u--; v--;
            edge.pb({u, v});
            g[u].pb(v);
            g[v].pb(u);
        }
        f >> L;
        for (int i = 0; i < L; i++)
            f >> p[i].x >> p[i].y;
        f.close();
        ll last = LINF;
        for (int i = 0; i < 100; i++)
            smin(last, Solve(last));
        cout << last << endl;
        edge.clear();
        for (int i = 0; i < n; i++)
            g[i].clear();
    }

    return 0;
}
