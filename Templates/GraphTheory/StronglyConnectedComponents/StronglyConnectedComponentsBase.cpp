#define pb push_back
namespace SCC{
    
    class StronglyConnectedComponentsBase{
    private:
        bool solved;
        vector<vector<int> > g1, comps;
    protected:
        int n, n1;
        vector<vector<int> > g;
        vector<int> comp;
        stack<int> st;
        void Initialize(int n){
            this->n = n;
            this->n1 = 0;
            this->g = vector<vector<int> >(n);
            this->comp = vector<int>(n);
            this->solved = 0;
        }
    public:
        void Add(int u, int v){ this->g[u].pb(v); }
        vector<vector<int> > GetCompresedGraph(){ Execute(); return this->g1; }
        vector<int> GetComp(){ Execute(); return this->comp; }
        vector<vector<int> > GetComps(){ Execute(); return this->comps; }
        int GetSize(){ Execute(); return this->n1; }
    private:
        void Execute(){ if (this->solved) return; this->solved = 1; Solve(); }
        virtual void Solve() = 0;
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
    protected:
        void Compress(){
            this->g1 = vector<vector<int> >(this->n1);
            for (int s = 0; s < this->n; s++)
                for (int u : this->g[s])
                    if (this->comp[s]^this->comp[u])
                        this->g1[this->comp[s]].pb(this->comp[u]);
            this->comps = vector<vector<int> >(this->n1);
            for (int s = 0; s < this->n; s++)
                this->comps[this->comp[s]].pb(s);
            Clean();
        }
    };
  }
