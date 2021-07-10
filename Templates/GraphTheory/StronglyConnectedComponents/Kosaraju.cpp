    class Kosaraju : public StronglyConnectedComponentsBase{
    private:
        vector<bool> vis;
        vector<vector<int> > _g;
        void dfs(int s){
            this->vis[s] = 1;
            for (int u : this->g[s])
                if (!this->vis[u])
                    dfs(u);
            this->st.push(s);
        }
        void dfs1(int s, int c){
            this->vis[s] = 1;
            this->comp[s] = c;
            for (int u : this->_g[s])
                if (!this->vis[u])
                    dfs1(u, c);
        }
        void Reverse(){
            for (int s = 0; s < this->n; s++)
                for (int u : this->g[s])
                    this->_g[u].pb(s);
        }
        void Solve() override {
            Reverse();
            for (int s = 0; s < this->n; s++)
                if (!this->vis[s])
                    dfs(s);
            this->vis = vector<bool>(n, 0);
            while (this->st.size()){
                int s = this->st.top();
                this->st.pop();
                if (!this->vis[s]){
                    dfs1(s, this->n1);
                    this->n1++;
                }
            }
            Compress();
        }
    public:
        Kosaraju(){}
        Kosaraju(int n){ Initialize(n); this->_g = vector<vector<int> >(n); this->vis = vector<bool>(n, 0); }
    };
