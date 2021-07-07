#define pb push_back
namespace SCC{
    class StronglyConnectedComponentsBase{
    private:
        bool solved;
    protected:
        int n, n1;
        vector<vector<int> > g, g1;
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
        int GetSize(){ Execute(); return this->n1; }
    private:
        void Execute(){ if (this->solved) return; this->solved = 1; Solve(); }
        virtual void Solve() = 0;
    };
  }
