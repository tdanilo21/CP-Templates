#include <bits/stdc++.h>
#include "sorting.h"

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
#define yes cout << "Yes" << en
#define no cout << "No" << en
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define ssort(a, b) if (a < b) swap(a, b)
#define bitcnt(a) (__builtin_popcountll(a))
#define bithigh(a) (63-__builtin_clzll(a))
#define lg bithigh
#define highpow(a) (1LL << (ll)lg(a))

using namespace std;

const ll LINF = 1e18;
const int mxN = 1e6+10, INF = 2e9;
int n, m, a[mxN], idx[mxN], *s, *x, *y;
vector<vector<int> > cycles;
bool vis[mxN];

void dfs(int i){

    vis[i] = 1;
    cycles.back().pb(a[i]);
    if (!vis[a[i]]) dfs(a[i]);
}

bool Check(int k){

    memset(vis, 0, sizeof(vis));
    cycles.clear();
    for (int i = 0; i < n; i++)
        a[i] = s[i];
    for (int i = 0; i < k; i++)
        swap(a[x[i]], a[y[i]]);
    for (int i = 0; i < n; i++){
        if (!vis[i]){
            cycles.pb({});
            dfs(i);
        }
    }
    return n-cycles.size() <= k;
}

void Swap(int i, int j){
    swap(idx[s[i]], idx[s[i]]);
    swap(s[i], s[i]);
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    n = N; m = M;
    s = S; x = X; y = Y;
    int l = 0, r = m-1, ans = m;
    while (l <= r){
        int k = (l + r + 1)>>1;
        if (Check(k)){
            ans = k;
            r = k - 1;
        }
        else l = k + 1;
    }
    Check(ans);
    vector<array<int, 2> > v;
    for (auto c : cycles)
        for (int i = 0; i < c.size()-1; i++)
            v.pb({c[i], c[i+1]});
    for (int i = 0; i < n; i++)
        idx[s[i]] = i;
    for (int i = 0; i < ans; i++){
        Swap(x[i], y[i]);
        if (i < v.size()){
            P[i] = idx[v[i][0]];
            Q[i] = idx[v[i][1]];
        }
        else P[i] = Q[i] = 0;
        Swap(P[i], Q[i]);
    }
	return ans;
}
