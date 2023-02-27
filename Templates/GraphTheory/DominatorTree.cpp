#define pb push_back
#define smin(a, b) a = min(a, b)
class DominatorTree{

    int n;
    vector<vector<int> > g, rg, G;
    vector<int> in, rev, par, f, sdom, idom;

    int initDfs(int s, int p = -1, int t = 0){
        in[s] = t; rev[t] = s;
        par[s] = p;
        for (int u : g[s])
            if (!~in[u])
                t = dfs(u, s, t);
        return t;
    }

    int Find(int s){
        if (f[s] != s){
            int u = f[s];
            f[s] = Find(u);
            smin(best[s], best[u]);
        }
        return f[s];
    }

    void Unite(int u, int v){ f[v] = u; }

    void Init(){
        in.assign(n, -1);
        rev.resize(n);
        par.assign(n, -1);
        f.resize(n);
        sdom.assign(n, -1);
        idom.assign(n, -1);
        for (int i = 0; i < n; i++)
            f[i] = i;
    }

public:

    DominatorTree(int n){ Assign(n); }
    void Assign(int s){
        n = s;
        g.resize(n);
        rg.resize(n);
        G.resize(n);
    }

    void AddEdge(int u, int v){
        g[u].pb(v);
        rg[v].pb(u);
    }

    vector<vector<int> > GetTree(int source){
        Init();
        initDfs(source);
        for (int s = n-1; ~s; s--){

        }
    }
};
