#define ll long long
#define pb push_back
const ll LINF = 4e18;
namespace MaxFlow {

	class Edge {
	public:
		int to, from;
		ll cap, flow;
		Edge* res;

		Edge(int from, int to, ll cap) {
			this->from = from;
			this->to = to;
			this->cap = cap;
			this->flow = 0;
		}
		Edge(const Edge& e) {
			this->from = e.from;
			this->to = e.to;
			this->cap = e.cap;
			this->flow = e.flow;
		}
		bool IsRes() const { return !this->cap; }
		ll RemainingCap() const { return this->cap - this->flow; }
		void Augment(ll bottleNeck) { this->flow += bottleNeck; this->res->flow -= bottleNeck; }
	};

	class NetworkFlowSolverBase {
    private:
        bool solved;
		int _VISITED_;
		vector<int> vis;
	protected:
		int n, source, sink;
		ll maxFlow;
		vector<vector<Edge*> > graph;
		void Initialize(int n, int source, int sink) {
			this->n = n;
			this->source = source;
			this->sink = sink;
			this->vis = *new vector<int>(n, 0);
			this->_VISITED_ = 0;
			this->solved = 0;
			this->maxFlow = 0;
			this->graph = *new vector<vector<Edge*> >(n, vector<Edge*>());
		}
		void Visit(int s){ this->vis[s] = this->_VISITED_; }
		bool Visited(int s) const { return this->vis[s] == this->_VISITED_; }
		void ResetVis(){ this->_VISITED_++; }
	public:
		void AddEdge(int from, int to, ll cap) {
			if (cap <= 0) {
				cerr << "Edge capacity must be greater than 0!" << endl;
				exit(1);
			}
			Edge* e = new Edge(from, to, cap);
			Edge* r = new Edge(to, from, 0);
			e->res = r; r->res = e;
			this->graph[from].pb(e);
			this->graph[to].pb(r);
		}
		vector<Edge>* GetGraph() {
			Execute();
			vector<Edge>* g = new vector<Edge>[this->n];
			for (int s = 0; s < this->n; s++)
				for (auto e : this->graph[s])
					g[s].pb(*new Edge(*e));
			return g;
		}
		ll GetMaxFlow() { Execute(); return this->maxFlow; }
	private:
		void Execute() { if (this->solved) return; this->solved = 1; Solve(); }
		virtual void Solve() = 0;
	};
}
