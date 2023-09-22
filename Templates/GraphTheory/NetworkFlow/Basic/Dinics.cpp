class Dinics : public NetworkFlowSolverBase {
private:
  vector<int> lvl, next;
  ll dfs(int s, ll flow){
    if (s == this->sink) return flow;
    Visit(s);
    for (; this->next[s] < this->graph[s].size(); this->next[s]++){
    	Edge* e = this->graph[s][this->next[s]];
    	if (!Visited(e->to) && lvl[e->to] > lvl[s] && e->RemainingCap()){
    	    ll bottleNeck = dfs(e->to, min(flow, e->RemainingCap()));
    	    if (bottleNeck){
        		e->Augment(bottleNeck);
        		return bottleNeck;
          }
  	    }
      }
    return 0;
  }
  bool bfs(){
    this->lvl = vector<int>(n, -1);
    queue<int> q;
    q.push(this->source);
    this->lvl[this->source] = 0;
    while (q.size()){
    	int s = q.front(); q.pop();
    	for (auto e : this->graph[s]){
    	    if (!~this->lvl[e->to] && e->RemainingCap()){
        		this->lvl[e->to] = lvl[s] + 1;
        		q.push(e->to);
          }
        }
      }
    return ~this->lvl[this->sink];
  }
  void Solve() override {
    while (bfs()){
    	this->next = vector<int>(n, 0);
    	while (ll bottleNeck = dfs(this->source, LINF)){
    	    this->maxFlow += bottleNeck;
    	    ResetVis();
    	}
    	ResetVis();
    }
  }
public:
	Dinics() {};
	Dinics(int n, int source, int sink) { Initialize(n, source, sink); }
};
