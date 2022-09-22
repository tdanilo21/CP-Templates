#include <bits/stdc++.h>

#define ll long long

using namespace std;

namespace Solution{

    #define maxn 100020
    int n;
    int fir[maxn], en[maxn*2], nex[maxn*2], len[maxn*2];
    int fa[maxn];
    int tot;
    int mxid[maxn][4];
    ll f[maxn][2];
    ll mx[maxn][4];
    ll ans;
    ll ret;
    void tjb(int x,int y,int r){
        en[++tot] = y;
        len[tot] = r;
        nex[tot]=fir[x];
        fir[x] =tot;
    }
    void dfs_1(int x){
        f[x][0] = 0;
        for(int k=fir[x];k;k=nex[k]){
            int j = en[k];
            if(j == fa[x])continue;
            fa[j] = x;
            dfs_1(j);
            for(int i=0;i<4;++i){
                if(mxid[x][i] == 0 || mx[x][i] < mx[j][0] + len[k]){
                    for(int z=3;z>i;--z){
                        mxid[x][z] = mxid[x][z-1];
                        mx[x][z] = mx[x][z-1];
                    }
                    mx[x][i] = mx[j][0] + len[k];
                    mxid[x][i] = j;
                    break;
                }
            }
            f[x][0] = max(f[x][0], f[j][0]);
        }
        f[x][0] = max(f[x][0], mx[x][0] + mx[x][1]);
        ans = max(ans, mx[x][0] + mx[x][1] + mx[x][2] + mx[x][3]);
    }
    void dfs_2(int x,ll mxdis){
        int mx1 = 0;
        int mx2 = 0;
        ans = max(ans, mxdis + mx[x][0] + mx[x][1] + mx[x][2]);
        for(int k=fir[x];k;k=nex[k]){
            int j=en[k];
            if(j == fa[x])continue;
            if(mx1 == 0 || f[j][0] > f[mx1][0]){
                mx2 = mx1;
                mx1 = j;
            }else if(mx2 == 0 || f[j][0] > f[mx2][0]){
                mx2 = j;
            }

        }
        for(int k=fir[x];k;k=nex[k]){
            int j=en[k];
            if(j == fa[x])continue;
            f[j][1] = f[x][1];
            for(int z1 = 0; z1 < 3; ++ z1){
                for(int z2 = z1 + 1; z2 < 3;++z2){
                    if(mxid[x][z1] != 0 && mxid[x][z2] != 0 && mxid[x][z1] != j && mxid[x][z2] != j) f[j][1] = max(f[j][1], mx[x][z1] + mx[x][z2]);
                }
            }
            if(mx1 != j && mx1 != 0) f[j][1] = max(f[j][1], f[mx1][0]);
            if(mx2 != j && mx2 != 0) f[j][1] = max(f[j][1], f[mx2][0]);

            ll mxdisj = mxdis;
            f[j][1] = max(f[j][1], mxdis);
            for(int z1 = 0;z1 <2;++z1){
                if(mxid[x][z1] != 0 && mxid[x][z1] != j) {
                    f[j][1] = max(f[j][1], mxdis + mx[x][z1]);
                    mxdisj = max(mxdisj, mx[x][z1]);
                }
            }

            ans = max(ans, f[j][0] + f[j][1] + len[k] * 2);
        //	printf("debug: %d %lld %lld %lld\n",j, f[j][0], f[j][1], ans);
            dfs_2(j, mxdisj + len[k]);

        }
    }
    ll Solve(int _n, vector<array<ll, 3> > _e)
    {
        n = _n;
        tot = 0;
        for(int i=1;i<=n;++i){
            fir[i] = 0;
            memset(mxid[i], 0,sizeof(mxid[i]));
            memset(mx[i],0,sizeof(mx[i]));
            mxid[i][0] = i;
            fa[i] = 0;
            f[i][0] = f[i][1] = 0;
        }
        ans = 0;
        ret = 0;
        for(int i=0;i<n-1;++i){
            auto [x, y, z] = _e[i];
            tjb(x,y,z);
            tjb(y,x,z);
            ret += z*2;
        }
        dfs_1(1);
        dfs_2(1,0);
        return ret-ans;
    }
};

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

namespace Algorithm{

    const ll LINF = 4e18;
    const int mxN = 1e6+10, INF = 2e9;
    ll n, m, a[mxN], par[mxN], diam[mxN], h[mxN], sum[mxN], dp[mxN];
    vector<array<ll, 2> > g[mxN];

    void dfs(int s = 0, int p = -1){

        par[s] = p;
        array<ll, 2> mx = {0, 0};
        for (auto [u, w] : g[s]){
            if (u^p){
                dfs(u, s);
                sum[s] += sum[u] + w;
                smax(diam[s], diam[u]);
                smax(h[s], h[u] + w);
                if (h[u] + w > mx[0]){ mx[1] = mx[0]; mx[0] = h[u] + w; }
                else if (h[u] + w > mx[1]) mx[1] = h[u] + w;
            }
        }
        smax(diam[s], mx[0] + mx[1]);
    }

    void ReRoot(int u, int v, ll w, const vector<array<ll, 2> >& uh, const vector<array<ll, 2> >& ud){

        sum[u] -= sum[v] + w;
        array<ll, 2> mx = {0, 0};
        for (auto [d, s] : uh){
            if (s^v){
                if (d > mx[0]){ mx[1] = mx[0]; mx[0] = d; }
                else if (d > mx[1]) mx[1] = d;
            }
        }
        h[u] = mx[0];
        diam[u] = mx[0] + mx[1];
        for (auto [d, s] : ud)
            if (s^v) smax(diam[u], d);

        sum[v] += sum[u] + w;
        smax(diam[v], max(h[v] + h[u] + w, diam[u]));
        smax(h[v], h[u] + w);
    }

    void dfs1(int s = 0, int p = -1, ll w = 0, const vector<array<ll, 2> >& ph = {}, const vector<array<ll, 2> >& pd = {}){

        if (~p){
            ReRoot(p, s, w, ph, pd);
            dp[s] = 2LL * sum[p] - diam[p];
        }
        vector<array<ll, 2> > sh, sd;
        for (auto [u, w] : g[s]){
            sh.pb({h[u]+w, u});
            sd.pb({diam[u], u});
        }
        sort(all(sh)); reverse(all(sh));
        sort(all(sd)); reverse(all(sd));
        while (sh.size() > 3) sh.pop_back();
        while (sd.size() > 3) sd.pop_back();
        for (auto [u, w] : g[s])
            if (u^p)
                dfs1(u, s, w, sh, sd);
        if (~p) ReRoot(s, p, w, sh, sd);
    }

    ll Solve(int _n, vector<array<ll, 3> > _e){

        n = _n;
        for (int i = 1; i < n; i++){
            auto [u, v, w] = _e[i-1];
            u--; v--;
            g[u].pb({v, w});
            g[v].pb({u, w});
        }
        cout << 11 << endl;
        dfs();
        dfs1();
        ll ans = LINF;
        for (int i = 0; i < n; i++)
            smin(ans, dp[i] + 2LL * sum[i] - diam[i]);
        return ans;
    }
}

class AVL{

    int n, root;
    vector<ll> tree;
    vector<int> h, sz, l, r;
    queue<int> free;

    void Assign(int s, ll x){
        tree[s] = x;
        h[s] = sz[s] = 1;
        l[s] = r[s] = -1;
    }

    int Make(ll x){
        n++;
        int s = free.front(); free.pop();
        Assign(s, x);
        return s;
    }

    void Erase(int s){
        free.push(s);
        n--;
    }

    int Height(int s) const { return (~s ? h[s] : 0); }
    int Size(int s) const { return (~s ? sz[s] : 0); }

    void Update(int s){ h[s] = max(Height(l[s]), Height(r[s])) + 1; sz[s] = Size(l[s]) + Size(r[s]) + 1; }

    int Rrot(int s){
        int u = l[s];
        l[s] = r[u];
        r[u] = s;
        Update(s); Update(u);
        return u;
    }

    int Lrot(int s){
        int u = r[s];
        r[s] = l[u];
        l[u] = s;
        Update(s); Update(u);
        return u;
    }

    ll Min(int s) const { if (!~l[s]) return tree[s]; return Min(l[s]); }
    ll Max(int s) const { if (!~r[s]) return tree[s]; return Max(r[s]); }

    int BF(int s) const { return Height(l[s]) - Height(r[s]); }

    int Balance(int s){
        if (BF(s) < -1){
            if (BF(r[s]) > 0) r[s] = Rrot(r[s]);
            s = Lrot(s);
        }
        else if (BF(s) > 1){
            if (BF(l[s]) < 0) l[s] = Lrot(l[s]);
            s = Rrot(s);
        }
        return s;
    }

    int Insert(int s, ll x){
        if (!~s) return Make(x);
        if (x < tree[s]) l[s] = Insert(l[s], x);
        else r[s] = Insert(r[s], x);
        Update(s);
        return Balance(s);
    }

    int Delete(int s, ll x){
        if (!~s) return s;
        if (x == tree[s]){
            if (!~l[s] && !~r[s]){ Erase(s); return -1; }
            if (!~r[s]){
                int v = Max(l[s]);
                tree[s] = v;
                l[s] = Delete(l[s], v);
            }
            else{
                int v = Min(r[s]);
                tree[s] = v;
                r[s] = Delete(r[s], v);
            }
        }
        else if (x < tree[s]) l[s] = Delete(l[s], x);
        else r[s] = Delete(r[s], x);
        Update(s);
        return Balance(s);
    }

    int Get(int s, ll x) const {
        if (!~s) return 0;
        if (x == tree[s]) return Size(r[s]);
        if (x > tree[s]) return Get(r[s], x);
        return Size(r[s]) + 1 + Get(l[s], x);
    }

    int GetIth(int s, int i) const {
        if (Size(l[s]) + 1 == i) return tree[s];
        if (Size(l[s]) + 1 < i) return GetIth(r[s], i - Size(l[s]) - 1);
        return GetIth(l[s], i);
    }

    vector<int> Dfs(int s) const {
        if (!~s) return {};
        vector<int> v = {s};
        auto a = Dfs(l[s]);
        auto b = Dfs(r[s]);
        for (int u : a) v.pb(u);
        for (int u : b) v.pb(u);
        return v;
    }

public:
    AVL(int s){
        n = 0; root = -1;
        tree.resize(s); h.resize(s); sz.resize(s); l.resize(s); r.resize(s);
        for (int i = 0; i < s; i++) free.push(i);
    }
    int Size() const { return n; }
    void Insert(ll x){ root = Insert(root, x); }
    void Delete(ll x){ root = Delete(root, x); }
    int Get(ll x) const { return Get(root, x); }
    int GetIth(int i) const { return GetIth(root, i); }

    void Print() const {
        auto v = Dfs(root);
        for (int s : v)
            cout << tree[s] << ": " << (~l[s] ? tree[l[s]] : -1) << sp << (~r[s] ? tree[r[s]] : -1) << en;
        cout.flush();
    }
};

int main(){

    srand(time(NULL));
    const int INF = 1e9;
    ri(t);
    for (int tt = 1; tt <= t; tt++){
        int n = rand() % 100 + 1;
        vector<vector<int> > v;
        AVL st(n);
        for (int i = 1; i <= n; i++){
            v.pb({i});
            st.Insert(i-1);
        }
        vector<array<ll, 3> > e;
        for (int _ = 1; _ < n; _++){
            int i = st.GetIth(rand() % st.Size() + 1);
            st.Delete(i);
            int j = st.GetIth(rand() % st.Size() + 1);
            st.Insert(i);
            if (v[i].size() < v[j].size()) swap(i, j);
            int s = v[i][rand() % v[i].size()];
            int u = v[j][rand() % v[j].size()];
            int w = rand() % INF + 1;
            e.pb({s, u, w});
            for (int k : v[j]) v[i].pb(k);
            v[j].clear();
            st.Delete(j);
        }
        cout << tt << endl;
        if (tt == 2){
            cout << "Test " << n << en;
            for (auto [u, v, w] : e) cout << u << sp << v << sp << w << en;
            cout.flush();
        }
        ll output = Algorithm::Solve(n, e);
        cout << tt << endl;
        ll answer = Solution::Solve(n, e);
        cout << tt << endl;
        if (answer^output){
            cout << "test " << tt << ": WA" << en << "Answer: " << answer << " Output: " << output << en;
            cout << n << en;
            for (auto [u, v, w] : e) cout << u << sp << v << sp << w << en;
            cout.flush();
        }
    }
}

/*
Answer: 463938 Output: 499777
22
17 3 31622
3 4 6448
11 16 22003
7 8 30325
16 15 30686
9 2 10009
18 12 24454
9 21 23938
12 22 15649
17 11 2129
6 10 30145
20 14 13908
22 13 430
10 14 20082
15 5 28924
8 19 16294
11 6 25703
11 21 14208
3 13 28089
22 1 4564
11 19 25161
*/
