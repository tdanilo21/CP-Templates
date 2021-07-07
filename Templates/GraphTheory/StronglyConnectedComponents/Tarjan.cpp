#define smin(a, b) a = min(a, b)
class Tarjan : public StronglyConnectedComponentsBase{
    private:
        vector<int> tin;
        vector<bool> OnStack;
        int dfs(int s, int t = 0){
            this->st.push(s);
            this->OnStack[s] = 1;
            this->tin[s] = this->comp[s] = t;
            for (int u : this->g[s]){
                if (!~this->tin[u]) t = dfs(u, t+1);
                if (this->OnStack[u]) smin(comp[s], comp[u]);
            }
            if (this->tin[s] == this->comp[s]){
                while (this->OnStack[s]){
                    int u = this->st.top();
                    this->st.pop();
                    this->OnStack[u] = 0;
                    this->comp[u] = n1;
                }
                n1++;
            }
            return t;
        }
        void Clean(){
            for (int s = 0; s < this->n1; s++){
                vector<int> t;
                for (int i = 0; i < this->g1[s].size(); i++)
                    if (!i || this->g1[s][i]^this->g1[s][i-1])
                        t.pb(this->g1[s][i]);
                this->g1[s].clear();
                for (int u : t) this->g1[s].pb(u);
            }
        }
        void Solve() override{
            for (int s = 0; s < this->n; s++)
                if (!~this->tin[s])
                    dfs(s);
            this->g1 = vector<vector<int> >(n1);
            for (int s = 0; s < this->n; s++)
                for (int u : this->g[s])
                    this->g1[this->comp[s]].pb(this->comp[u]);
            Clean();
        }
    public:
        Tarjan(int n){ Initialize(n); this->tin = vector<int>(n, -1); this->OnStack = vector<bool>(n, 0); }
    };
