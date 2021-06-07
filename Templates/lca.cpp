#define pb push_back
#define sp ' '
#define en '\n'
#define tb '\t'
#define bithigh(a) 64-__builtin_clzll(a)
int lg(ll a) { return bithigh(a) - 1; }
ll highpow(ll a) { return 1LL << (ll)lg(a); }
class lca{
private:
    int n, _edges_ = 0;
    vector<int> depth;
    vector<vector<int> > g, par;
    bool _initialized_ = 0, _computed_ = 0;
    void init(int n){
        this->n = n;
        this->depth = vector<int>(n);
        this->g = vector<vector<int> >(n);
        this->par = vector<vector<int> >(n, vector<int>(lg(n)+10, -1));
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
        for (int d = 1; d < lg(this->n)+1; d++)
            for (int s = 0; s < this->n; s++)
                if (this->depth[s] >= (1<<d))
                    this->par[s][d] = this->par[this->par[s][d-1]][d-1];
        _computed_ = 1;
    }
    int Depth(int s) const {
        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        return this->depth[s];
    }
    int Par(int s, int d) const {

        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        if (d < 0 || d > this->depth[s]) return -1;
        if (!d) return s;
        return Par(this->par[s][lg(d)], d-highpow(d));
    }
    int Lca(int u, int v) const {

        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        if (this->depth[u] > this->depth[v]) swap(u, v);
        v = Par(v, this->depth[v] - this->depth[u]);
        if (u==v) return v;
        for (int i = lg(this->n)+1; ~i; i--){
            if (this->par[u][i]^this->par[v][i]){
                u = this->par[u][i];
                v = this->par[v][i];
            }
        }
        return this->par[u][0];
    }
    void Log() const {

        if (!this->_computed_){
            cerr << "Lca table has not been computed yet!" << endl;
            exit(1);
        }
        for (int s = 0; s < this->n; s++){
            cerr << s << tb;
            for (int d = 0; d < lg(this->n)+1; d++)
                cerr << this->par[s][d] << sp;
            cerr << endl;
        }
    }
};
