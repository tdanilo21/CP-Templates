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
                if (this->OnStack[u]) smin(this->comp[s], this->comp[u]);
            }
            if (this->tin[s] == this->comp[s]){
                while (this->OnStack[s]){
                    int u = this->st.top();
                    this->st.pop();
                    this->OnStack[u] = 0;
                    this->comp[u] = this->n1;
                }
                this->n1++;
            }
            return t;
        }
        void Solve() override{
            for (int s = 0; s < this->n; s++)
                if (!~this->tin[s])
                    dfs(s);
            Compress();
        }
    public:
        Tarjan(int n){ Initialize(n); this->tin = vector<int>(n, -1); this->OnStack = vector<bool>(n, 0); }
    };
