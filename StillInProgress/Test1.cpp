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

const ll LINF = 4e18;
const int mxN = 1e6+10, INF = 2e9;
ll n, m, ans[mxN];
vector<array<ll, 3> > a[mxN];

void Solve(){

    cin >> n;
    for (int i = 0; i < n; i++){
        ans[i] = LINF;
        a[i].clear();
    }
    for (int i = 0; i < n; i++){
        ri(l); ri(r); ri(c);
        a[c-1].pb({l, r, i});
    }
    multiset<array<ll, 2> > msl, msr;
    for (int i = 1; i < n; i++){
        for (auto [l, r, j] : a[i]){
            msl.insert({l, j});
            msr.insert({-r, j});
        }
    }
    for (int i = 0; i < n; i++){
        if (i){
            for (auto [l, r, j] : a[i-1]){
                msl.insert({l, j});
                msr.insert({-r, j});
            }
            for (auto [l, r, j] : a[i]){
                msl.erase(msl.find({l, j}));
                msr.erase(msr.find({-r, j}));
            }
        }
        for (auto [l, r, j] : a[i]){
            auto [l1, j1] = *msl.lower_bound({l, 0});
            auto [r1, j2] = *msr.lower_bound({-r, 0});
            ll t1 = max(l1-r, 0LL), t2 = max(l-r1, 0LL);
            smin(ans[j1], t1); smin(ans[j2], t2);
            smin(ans[j], min(t1, t2));
        }
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << sp;
    cout << en;
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
