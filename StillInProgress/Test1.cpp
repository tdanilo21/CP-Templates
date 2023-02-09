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

class NetworkFlow{

    struct Edge{
        int from, to;
        ll cap, flow, cost;
        Edge* res;

        Edge(int from, int to, ll cap, ll cost){
            this->from = from;
            this->to = to;
            this->cap = cap;
            this->cost = cost;
        }

        bool IsRes() const { return !cap; }
        ll RemainingCap() const { return cap - flow; }
        void Augment(ll bottleNeck){ flow += bottleNeck; res->flow -= bottleNeck; }
    };

    int n, source, sink, _VISITED_;
    vector<vector<Edge*> > g;
    vector<int> vis;
    vector<Edge*> par;

    void Visit(int s){ vis[s] = _VISITED_; }
    bool Visited(int s) const { return vis[s] == _VISITED_; }
    void ResetVis(){ _VISITED_++; }

    array<ll, 2> Dijkstra(){
        ResetVis();
        vector<ll> dist(n, LONG_MAX);
        priority_queue<array<ll, 3>,
                vector<array<ll, 3> >,
                greater<array<ll, 3> > > pq;
        dist[source] = 0;
        pq.push({0, LONG_MAX, source});
        ll maxFlow = 0;
        while (pq.size()){
            auto [d, flow, s] = pq.top(); pq.pop();
            if (Visited(s)) continue;
            Visit(s);
            for (auto e : g[s]){
                if (e->RemainingCap() && d + e->cost < dist[e->to]){
                    dist[e->to] = d + e->cost;
                    par[e->to] = e;
                    if (e->to == sink) maxFlow = min(flow, e->RemainingCap());
                    pq.push({dist[e->to], min(flow, e->RemainingCap()), e->to});
                }
            }
        }
        return {dist[sink], maxFlow};
    }

public:
    void assign(int n, int source, int sink){
        this->n = n;
        this->source = source;
        this->sink = sink;
        _VISITED_ = 1;
        g.assign(n, vector<Edge*>());
        vis.assign(n, 0);
        par.assign(n, nullptr);
    }

    void AddEdge(int u, int v, ll cap, ll cost){
        Edge *e = new Edge(u, v, cap, cost), *r = new Edge(v, u, 0, -cost);
        e->res = r; r->res = e;
        g[u].pb(e); g[v].pb(r);
    }

    ll MinCostMaxFlow(){
        ll maxFlow = 0, minCost = 0;
        while (1){
            auto [cost, flow] = Dijkstra();
            if (!flow) break;
            int s = sink;
            while (s != source){
                par[s]->Augment(flow);
                s = par[s]->from;
            }
            maxFlow += flow;
            minCost += flow * cost;
        }
        return minCost;
    }
};

const ll LINF = 1e18;
const int mxN = 1e6+10, INF = 2e9;
ll n, m, a[mxN], b[mxN];

void Solve(){

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> v;
    for (int i = 0; i < n; i++){
        ri(x); a[i] -= x;
        if (a[i] < 0) v.pb(i);
    }
    NetworkFlow solver;
    solver.assign(n+2, 0, n+1);
    for (int i = 0, j = -1; i < n; i++){
        if (a[i] <= 0) continue;
        solver.AddEdge(0, i+1, a[i], 0);
        while (j < v.size()-1 && v[j+1] < i) j++;
        if (~j) solver.AddEdge(i+1, v[j]+1, a[i], i-v[j]);
        if (j < v.size()-1) solver.AddEdge(i+1, v[j+1]+1, a[i], v[j+1]-i);
    }
    for (int i : v) solver.AddEdge(i+1, n+1, -a[i], 0);
    cout << solver.MinCostMaxFlow() << en;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cerr.tie(0);
    cout << setprecision(12) << fixed;
    cerr << setprecision(12) << fixed;
    cerr << "Started!" << endl;

    int t = 1;
    //cin >> t;
    while (t--)
        Solve();

    return 0;
}
