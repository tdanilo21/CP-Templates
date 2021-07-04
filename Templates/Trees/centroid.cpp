#define pb push_back
class centroid{
private:
    int n;
    vector<vector<int> > g;
    int FindSize(int s, int p = -1){
        this->sz[s] = 1;
        for (int u : this->g[s])
            if (u^p && !this->was[u])
                this->sz[s] += FindSize(u, s);
        return this->sz[s];
    }
    int FindCentroid(int s, int p, int n){
        for (int u : this->g[s])
            if (u^p && !this->was[u] && this->sz[u] > n / 2)
                return FindCentroid(u, s, n);
        return s;
    }
public:
    vector<int> sz;
    vector<bool> was;
    centroid(){}
    centroid(int n){
        this->n = n;
        this->g = vector<vector<int> >(n, vector<int>());
        this->sz = vector<int>(n);
        this->was = vector<bool>(n, 0);
    }
    void edge(int u, int v){
        this->g[u].pb(v);
        this->g[v].pb(u);
    }
    int FindCentroid(int s){
        FindSize(s);
        s = FindCentroid(s, -1, this->sz[s]);
        this->was[s] = 1;
        return s;
    }
};
