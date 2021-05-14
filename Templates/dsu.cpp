#define pb push_back
class dsu{
private:
    int n;
    vector<int> comp, sz;
    vector<vector<int> > g;
    void dfs(int s, int c){
        if (this->comp[s] == c) return;
        this->comp[s] = c;
        for (int u : this->g[s])
            dfs(u, c);
    }
public:
    void init(int n){
        this->n = n;
        this->sz = vector<int>(n, 1);
        this->comp = vector<int>(n);
        for (int i = 0; i < n; i++) this->comp[i] = i;
        this->g = vector<vector<int> >(n);
    }
    void merge(int s, int u){
        if (comp[s] == comp[u]) return;
        this->g[s].pb(u);
        this->g[u].pb(s);
        if (sz[comp[s]] < sz[comp[u]]) swap(s, u);
        sz[comp[s]] += sz[comp[u]];
        sz[comp[u]] = 0;
        dfs(u, comp[s]);
    }
    int find(int s){ return comp[s]; }
};
