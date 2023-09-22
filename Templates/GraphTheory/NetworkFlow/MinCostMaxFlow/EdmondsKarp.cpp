class EdmondsKarp : public NetworkFlowSolverBase {
    private:
        vector<Edge*> par;
        array<ll, 2> Dijkstra(){
            this->par.assign(this->n, nullptr);
            vector<ll> dist(this->n, LINF);
            priority_queue<array<ll, 3>,
                    vector<array<ll, 3> >,
                    greater<array<ll, 3> > > pq;
            dist[this->source] = 0;
            pq.push({0, this->source, LINF});
            ll maxFlow = 0;
            while (pq.size()){
                auto [cost, s, flow] = pq.top(); pq.pop();
                if (cost > dist[s]) continue;
                for (auto e : this->graph[s]){
                    if (e->RemainingCap() && cost + e->cost < dist[e->to]){
                        dist[e->to] = cost + e->cost;
                        par[e->to] = e;
                        if (e->to == this->sink) maxFlow = min(flow, e->RemainingCap());
                        pq.push({dist[e->to], e->to, min(flow, e->RemainingCap())});
                    }
                }
            }
            return {dist[this->sink], maxFlow};
        }
        array<ll, 2> Solve(ll flowLimit) override {
            ll minCost = 0, maxFlow = 0;
            while (maxFlow < flowLimit){
                auto [cost, flow] = Dijkstra();
                if (!flow) break;
                smin(flow, flowLimit - maxFlow);
                int s = this->sink;
                while (s ^ this->source){
                    par[s]->Augment(flow);
                    s = par[s]->from;
                }
                minCost += flow * cost;
                maxFlow += flow;
            }
            return {minCost, maxFlow};
        }
    public:
        EdmondsKarp() {};
        EdmondsKarp(int n, int source, int sink) { this->par = *new vector<Edge*>(n); Initialize(n, source, sink); }
    };
