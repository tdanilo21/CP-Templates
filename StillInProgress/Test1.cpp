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
#define bitcnt(a) __builtin_popcountll(a)
#define bithigh(a) 63-__builtin_clzll(a)
#define lg bithigh
ll highpow(ll a) { return 1LL << (ll)lg(a); }

using namespace std;

const ll LINF = 4e18;
const int mxN = 1e3+10, INF = 2e9, mod = (1 ? 1e9+7 : 998244353);
ll n, m, dp[2][2][mxN][mxN];

void DP(const vector<int>& a, int t){

    for (int i = 0; i < n; i++){
        for (int j = 0; j <= n; j++){
            dp[t][0][i][j] = -LINF;
            dp[t][1][i][j] = LINF;
        }
    }
    dp[t][0][0][0] = dp[t][1][0][0] = 0;
    dp[t][0][0][1] = dp[t][1][0][1] = a[0];
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j <= n; j++){
            smax(dp[t][0][i+1][j], dp[t][0][i][j]);
            if (dp[t][0][i][j] != -LINF && j < n) smax(dp[t][0][i+1][j+1], dp[t][0][i][j] + a[i+1]);
            smin(dp[t][1][i+1][j], dp[t][1][i][j]);
            if (dp[t][1][i][j] != LINF && j < n) smin(dp[t][1][i+1][j+1], dp[t][1][i][j] + a[i+1]);
        }
    }
}

void Solve(){

    cin >> n >> m;
    vector<int> a(n);
    rv(a);
    DP(a, 0);
    reverse(all(a));
    DP(a, 1);
    for (int t = 0; t < 2; t++){
        for (int k = 0; k < 2; k++){
            for (int i = 0; i < n; i++){
                for (int j = 0; j <= n; j++)
                    cout << dp[t][k][i][j] << sp;
                cout << en;
            }
            cout << en;
        }
    }
    ll ans = -LINF;
    for (int i = 0; i < n; i++){
        for (int t = 1; t < m; t++){
            int j = n-i-2;
            int k = m - t;
            smax(ans, dp[0][0][i][t] - dp[1][1][j][k]);
            smax(ans, dp[1][0][j][k] - dp[0][1][i][t]);
        }
    }
    cout << ans << en;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); cerr.tie(0);
    cout << setprecision(12) << fixed;
    cerr << setprecision(12) << fixed;
    cerr << "Started!" << endl;

    int t = 1;
    cin >> t;
    while (t--)
        Solve();

    return 0;
}
