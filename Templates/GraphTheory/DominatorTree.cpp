#define pb push_back;
class DominatorTreeSolver{

    int n;
    vector<vector<int> > g, rg;
    vector<int> in, rev, par, f, best, sdom;

    int initDfs(int s, int t = 0){
        in[s] = t; rev[t] = s;
        sdom[t] = f[t] = best[t] = t;
        for (int u : g[s]){
            if (!~in[u]){
                t = initDfs(u, t+1);
                par[in[u]] = in[s];
            }
            rg[in[u]].pb(in[s]);
        }
        return t;
    }

    int Find(int s){
        if (f[s] != s){
            int u = f[s];
            f[s] = Find(u);
            if (sdom[best[u]] < sdom[best[s]])
                best[s] = best[u];
        }
        return f[s];
    }

    void Unite(int u, int v){ f[v] = u; }

    void Init(){
        in.assign(n, -1);
        rev.resize(n);
        par.assign(n, -1);
        f.resize(n);
        best.resize(n);
        sdom.resize(n);
    }

public:

    DominatorTreeSolver(int n = 0){ Assign(n); }
    void Assign(int s){
        n = s;
        g.assign(n, {});
        rg.assign(n, {});
    }

    void AddEdge(int u, int v){ g[u].pb(v); }

    vector<int> GetTree(int source = 0){
        Init();
        initDfs(source);
        vector<vector<int> > childs(n);
        vector<vector<int> > bucket(n);
        vector<int> idom(n, 0);
        for (int s = n-1; ~s; s--){
            for (int u : rg[s]){
                Find(u);
                smin(sdom[s], sdom[best[u]]);
            }
            bucket[sdom[s]].pb(s);
            for (int u : bucket[s]){
                Find(u);
                if (sdom[u] == sdom[best[u]]) idom[u] = sdom[u];
                else idom[u] = best[u];
            }
            if (s){
                for (int u : childs[s]) Unite(s, u);
                childs[par[s]].pb(s);
            }
        }
        vector<int> tpar(n, -1);
        for (int s = 1; s < n; s++){
            if (idom[s] != sdom[s]) idom[s] = idom[idom[s]];
            tpar[rev[s]] = rev[idom[s]];
        }
        return tpar;
    }
};

class DominatorTree{

    int n;
    vector<vector<int> > g;
    vector<bool> vis;

    void dfs(int s){
        vis[s] = 1;
        for (int u : g[s])
            if (!vis[u]) dfs(u);
    }

public:

    DominatorTree(int n = 0){ Assign(n); }

    void Assign(int s){
        n = s;
        g.assign(n, {});
    }

    void AddEdge(int u, int v){ g[u].pb(v); }

    vector<int> GetTree(int source = 0){
        vis.assign(n, 0);
        dfs(source);
        vector<int> visible_nodes;
        for (int s = 0; s < n; s++)
            if (vis[s]) visible_nodes.pb(s);
        vector<int> mp(n), rmp(visible_nodes.size());
        int m = 0;
        for (int s : visible_nodes){
            mp[s] = m;
            rmp[m] = s;
            m++;
        }
        DominatorTreeSolver dts(m);
        for (int s : visible_nodes)
            for (int u : g[s])
                if (vis[u]) dts.AddEdge(mp[s], mp[u]);
        auto mpar = dts.GetTree(mp[source]);
        vector<int> par(n, -1);
        for (int i = 0; i < m; i++)
            if (~mpar[i]) par[rmp[i]] = rmp[mpar[i]];
        return par;
    }
};
