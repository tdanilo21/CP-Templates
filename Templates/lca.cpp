#define pb push_back
#define bithigh(a) 64-__builtin_clzll(a)
#define log(a) bithigh(a)-1
#define highpow(a) (1<<log(a))
#define sp ' '
#define en '\n'
class lca{
private:
    int n, _edges_ = 0;
    vector<int> depth;
    vector<vector<int> > g, par;
    bool _initialized_ = 0;
    void init(int n){
        this->n = n;
        this->depth = vector<int>(n);
        this->g = vector<vector<int> >(n);
        this->par = vector<vector<int> >(n, vector<int>(log(n)+10, -1));
        this->_initialized_ = 1;
    }
    void dfs(int s, int p, int d){
        this->depth[s] = d;
        this->par[s][0] = p;
        for (int u : this->g[s])
            if (u^p)
                dfs(u, s, d+1);
    }
public:
    lca(){}
    lca(int n){ init(n); }
    void add(int u, int v){
        if (!this->_initialized_){
            cerr << "Initialize tree u idiot!" << endl;
            exit(1);
        }

        this->g[u].pb(v);
        this->g[v].pb(u);
        this->_edges_++;
    }
    void Compute(int root = 0){
        if (this->_edges_ < this->n-1){
            cerr << "Constructed tree is not connected!" << endl;
            exit(1);
        }
        if (this->_edges_ > this->n-1){
            cerr << "Constructed tree has cycles!" << endl;
            exit(1);
        }

        dfs(root, -1, 0);
        for (int d = 1; d < log(this->n)+1; d++)
            for (int s = 0; s < this->n; s++)
                if (this->depth[s] >= (1<<d))
                    this->par[s][d] = this->par[this->par[s][d-1]][d-1];
    }
    int GetPar(int s, int d) const {

        if (d > this->depth[s]) return -1;
        if (!d) return s;
        return GetPar(this->par[s][log(d)], d-highpow(d));
    }
    int GetLca(int u, int v) const {

        if (this->depth[u] > this->depth[v]) swap(u, v);
        v = GetPar(v, this->depth[v] - this->depth[u]);
        int l = 0, r = this->depth[u], ans = -1;
        while (l <= r){
            int k = (l + r + 1) / 2;
            if (GetPar(u, k) == GetPar(v, k)){
                ans = GetPar(u, k);
                r = k - 1;
            }
            else l = k + 1;
        }
        return ans;
    }
    void Print() const {

        for (int s = 0; s < this->n; s++){
            cout << s << sp;
            for (int d = 0; d < (int)log2(this->n)+1; d++)
                cout << this->par[s][d] << sp;
            cout << en;
        }
    }
};
