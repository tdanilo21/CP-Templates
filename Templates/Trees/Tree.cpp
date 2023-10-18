class Tree{

#define Empty [](int, int){}
private:
    int n, root;
    vector<int> depth, in, out, sz;
    vector<vector<int> > g, par;
    int _edges_;
    bool _initialized_;

    bool Valid(int s) const { return s >= 0 && s < n; }

    int InitDfs(int s, int p = -1, int d = 0, int t = 0){
        par[s][0] = p;
        depth[s] = d;
        in[s] = t;
        sz[s] = 1;
        for (int u : g[s]){
            if (u^p){
                t = InitDfs(u, s, d+1, t+1);
                sz[s] += sz[u];
            }
        }
        return out[s] = ++t;
    }

    void Dfs(int s, int p, void bf(int, int), void af(int, int)) const {
        bf(s, p);
        for (int u : g[s])
            if (u^p)
                Dfs(u, s, bf, af);
        af(s, p);
    }

public:
    Tree(int n = 1){ Assign(n); }

    void Assign(int n = 1){
        this->n = n;
        _edges_ = _initialized_ = 0;
        depth.assign(n, 0);
        in.assign(n, 0);
        out.assign(n, 0);
        sz.assign(n, 0);
        g.assign(n, vector<int>());
        par.assign(n, vector<int>(lg(n)+1, -1));
    }

    void Edge(int u, int v){
        if (!Valid(u) || !Valid(v)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        g[u].pb(v);
        g[v].pb(u);
        _edges_++;
    }

    void Read(){
        for (int i = 0; i < n-1; i++){
            ri(u); ri(v);
            u--; v--;
            Edge(u, v);
        }
    }

    void Initialize(int s = 0){
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        if (_edges_ < n-1){
            cerr << "Tree is not connected" << endl;
            exit(1);
        }
        if (_edges_ > n-1){
            cerr << "Tree has cycle(s)" << endl;
            exit(1);
        }
        root = s;
        InitDfs(s);
        for (int d = 1; d <= lg(n); d++)
            for (int i = 0; i < n; i++)
                if (depth[i] >= (1<<d))
                    par[i][d] = par[par[i][d-1]][d-1];
        _initialized_ = 1;
    }

    int Size() const { return n; }

    int Size(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return sz[s];
    }

    int Depth(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return depth[s];
    }

    int InTime(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return in[s];
    }

    int OutTime(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return out[s];
    }

    bool Leaf(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return s^root && g[s].size() == 1;
    }

    vector<int> GetAdjecent(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        return g[s];
    }

    vector<int> GetChilds(int s) const {
        if (!Valid(s)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        vector<int> ch;
        for (int u : g[s])
            if (u^par[s][0])
                ch.pb(u);
        return ch;
    }

    int Par(int s, int d = 1) const {
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        if (d < 0 || d > depth[s]) return -1;
        if (!d) return s;
        return Par(par[s][lg(d)], d - highpow(d));
    }

    bool Ancestor(int s, int p) const {
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        return in[s] >= in[p] && out[s] <= out[p];
    }

    int Lca(int u, int v) const {
        if (!Valid(u) || !Valid(v)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (Ancestor(v, u)) return u;
        v = Par(v, depth[v] - depth[u]);
        for (int d = lg(n); ~d; d--){
            if (par[u][d] != par[v][d]){
                u = par[u][d];
                v = par[v][d];
            }
        }
        return par[u][0];
    }

    int Dist(int u, int v) const {
        if (!Valid(u) || !Valid(v)){
            cerr << "Node index out of range" << endl;
            exit(1);
        }
        if (!_initialized_){
            cerr << "Tree has not been initialized yet" << endl;
            exit(1);
        }
        int lca = Lca(u, v);
        return depth[u] + depth[v] - 2*depth[lca];
    }

    void Dfs(void bf(int, int) = Empty, void af(int, int) = Empty) const { Dfs(root, -1, bf, af); }
};
