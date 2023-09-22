#define ll long long
#define pb push_back
namespace NetworkFlow {

  const ll LINF = 4e18;

	class Edge {
	public:
		int to, from;
		ll cap, flow, cost;
		Edge* res;

		Edge(int from, int to, ll cap, ll cost) {
			this->from = from;
			this->to = to;
			this->cap = cap;
			this->flow = 0;
			this->cost = cost;
		}
		Edge(const Edge& e) {
			this->from = e.from;
			this->to = e.to;
			this->cap = e.cap;
			this->flow = e.flow;
			this->cost = e.cost;
		}
		bool IsRes() const { return !this->cap; }
		ll RemainingCap() const { return this->cap - this->flow; }
		void Augment(ll bottleNeck) { this->flow += bottleNeck; this->res->flow -= bottleNeck; }
	};

	class NetworkFlowSolverBase {
    private:
        map<ll, array<ll, 2> > ans;
		int _VISITED_;
		vector<int> vis;
	protected:
		int n, source, sink;
		vector<vector<Edge*> > graph;
		void Initialize(int n, int source, int sink) {
			this->n = n;
			this->source = source;
			this->sink = sink;
			this->vis = *new vector<int>(n, 0);
			this->_VISITED_ = 0;
			this->graph = *new vector<vector<Edge*> >(n, vector<Edge*>());
		}
		void Visit(int s){ this->vis[s] = this->_VISITED_; }
		bool Visited(int s) const { return this->vis[s] == this->_VISITED_; }
		void ResetVis(){ this->_VISITED_++; }
	public:
		void AddEdge(int from, int to, ll cap, ll cost = 0) {
			if (cap < 0) {
				cerr << "Edge capacity must be non negative!" << endl;
				exit(1);
			}
			Edge* e = new Edge(from, to, cap, cost);
			Edge* r = new Edge(to, from, 0, -cost);
			e->res = r; r->res = e;
			this->graph[from].pb(e);
			this->graph[to].pb(r);
		}
		bool IsConnectingEdge(Edge* e) const {
            set<int> s = {this->source, this->sink};
            return !s.count(e->from) && !s.count(e->to) && !e->IsRes();
        }
		vector<Edge*>* GetGraph() const {
			if (this->ans.empty()) return nullptr;
			vector<Edge*>* g = new vector<Edge*>[this->n];
			for (int s = 0; s < this->n; s++)
				for (auto e : this->graph[s])
					g[s].pb(new Edge(*e));
			return g;
		}
		vector<Edge*> GetEdges() const {
            if (this->ans.empty()) return {};
            vector<Edge*> edges;
            for (int s = 0; s < this->n; s++)
                for (auto e : this->graph[s])
                    if (IsConnectingEdge(e))
                        edges.pb(new Edge(*e));
			return edges;
		}
		ll GetMaxFlow() { Execute(); return this->ans[LINF][1]; }
		array<ll, 2> GetMinCostMaxFlow(ll flowLimit = LINF) { Execute(flowLimit); return this->ans[flowLimit]; }
	private:
		void Execute(ll flowLimit = LINF) {
		    if (this->ans.count(flowLimit)) return;
		    auto [minCost, maxFlow] = Solve(flowLimit);
            this->ans[flowLimit] = {minCost, maxFlow};
        }
		virtual array<ll, 2> Solve(ll flowLimit) = 0;
	};
}
