#define ll long long
class EdmondsKarp : public NetworkFlowSolverBase {
	private:
		vector<Edge*> par;
		ll BFS() {
			ResetVis();
			queue<pair<int, ll> > q;
			q.push(make_pair(this->source, LINF));
			Visit(this->source);
			this->par[this->source] = nullptr;
			while (q.size()){
				auto [s, flow] = q.front(); q.pop();
				for (auto e : this->graph[s]){
					if (!Visited(e->to) && e->RemainingCap()){
						Visit(e->to);
						this->par[e->to] = e;
						q.push(make_pair(e->to, min(flow, e->RemainingCap())));
						if (e->to == this->sink) return min(flow, e->RemainingCap());
					}
				}
			}
			return 0;
		}
		void Solve() override {
			while (ll bottleNeck = BFS()){
				int s = this->sink;
				while (s ^ this->source){
					par[s]->Augment(bottleNeck);
					s = par[s]->from;
				}
				this->maxFlow += bottleNeck;
			}
		}
	public:
		EdmondsKarp() {};
		EdmondsKarp(int n, int source, int sink) { this->par = *new vector<Edge*>(this->n); Initialize(n, source, sink); }
	};
