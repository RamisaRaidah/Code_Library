#include <bits/stdc++.h>
using namespace std;
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);  cout.tie(NULL);
#define ll long long
#define ld long double
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define FOR(m,it) for(auto (it)=(m).begin();(it)!=m.end();(it)++)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define setbits(x) __builtin_popcountll(x)
#define leadzero(x) __builtin_clzll(x)  
#define trailzero(x) __builtin_ctzll(x)
#define fi first
#define se second
#define bg begin
#define en end
#define vll vector<ll>
#define vcc vector<char>
#define vbb vector<bool>
#define vpll vector<pair<ll,ll>> 


// Helper DFS to find a single path with flow and 'drain' it



ll dfs_drain(ll u, ll t, ll flow_val, vector<ll> &path, vbb &vis, vector<vector<pair<pll,pll>>> &adj) {
    if (u == t) return flow_val;
    vis[u] = true;

    for (int i = 0; i < adj[u].size(); i++) {
        auto &edge = adj[u][i];
        ll v = edge.fi.fi;       // Target node
        ll type = edge.fi.se;    // 1 = forward, 2 = backward
        ll rev_idx = edge.se.se; // Index of reverse edge in adj[v]
        
        // In your code: Flow on u->v is stored in the residual capacity of v->u
        ll current_flow_on_edge = adj[v][rev_idx].se.fi;

        // We only follow forward edges (type 1) that have flow remaining
        if (!vis[v] && type == 1 && current_flow_on_edge > 0) {
            
            // Recursively try to find the sink
            ll bottleneck = dfs_drain(v, t, min(flow_val, current_flow_on_edge), path, vis, adj);
            
            if (bottleneck > 0) {
                // Path found! Add this node to the path
                path.pb(v);
                
                // CRITICAL: Reduce the flow on this edge so we don't use it again for this amount
                // We reduce the residual of the reverse edge, which represents the flow
                adj[v][rev_idx].se.fi -= bottleneck;
                
                return bottleneck;
            }
        }
    }
    return 0;
}

void printFlowPaths(vector<vector<pair<pll,pll>>> adj, ll s, ll t) {
    // Note: Passed 'adj' by value (copy) so we don't destroy the actual flow in the main graph
    cout << "\n--- Flow Decomposition Paths ---" << endl;
    
    while (true) {
        vbb vis(adj.size(), false);
        vector<ll> path;
        
        // Try to find a path with positive flow
        ll path_flow = dfs_drain(s, t, INT64_MAX, path, vis, adj);
        
        if (path_flow == 0) break; // No more paths exist
        
        // The path is constructed in reverse order (t -> s), so we reverse it
        path.pb(s);
        reverse(all(path));

        // Print the path
        cout << "Flow: " << path_flow << " | Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
    }
}

void addEdge(vector<vector<pair<pll,pll>>> &adj, ll u, ll v, ll cap) {
    adj[u].pb({{v, 1}, {cap, (ll)adj[v].size()}});
    adj[v].pb({{u, 2}, {0, (ll)adj[u].size() - 1}});
}

bool bfs(vector<vector<pair<pll,pll>>> &adj, ll s, ll t, vll &par, vll &e){
    ll n=par.size();
    for(int i=0;i<n;i++){
        par[i]=-1;
    }

    queue<ll> q;
    q.push(s);
    par[s]=s;

    while(!q.empty()){
        ll u=q.front(); q.pop();

        for(int i=0;i<adj[u].size();i++){
            auto p=adj[u][i];
            ll v=p.fi.fi; ll cap=p.se.fi;
            if(par[v]==-1 && cap>0){
                par[v]=u;
                e[v]=i;
                if(v==t) return true;
                q.push(v);
            }
        }
    }

    return false;
}

void fordFulkerson(vector<vector<pair<pll,pll>>> &adj, ll s, ll t, vpll &input){
    ll flow=0;
    ll n=adj.size();
    vll par(n),e(n);

    while(bfs(adj,s,t,par,e)){
        ll mn=INT64_MAX;

        for(int v=t; v!=s; v=par[v]){
            ll u=par[v];
            mn=min(mn,adj[u][e[v]].se.fi);
        }

        for(int v=t;v!=s;v=par[v]){
            ll u=par[v];
            adj[u][e[v]].se.fi-=mn;
            adj[v][adj[u][e[v]].se.se].se.fi+=mn;
        }

        flow += mn;
    }


    cout<<flow<<endl;

    for(auto i: input){
        auto p=adj[i.fi][i.se];
        ll v=p.fi.fi;
        ll w=p.se.fi;
        ll rev=p.se.se;
        ll f=adj[v][rev].se.fi;
        cout<<i.fi<<" "<<v<<" "<<f<<"/"<<(w+f)<<endl;
    }

}

void solve(){
    ll m,n; cin>>n>>m;
    vector<vector<pair<pll,pll>>> adj(n);
    vpll input(m);
    for(int i=0;i<m;i++){
        ll x,y,z; cin>>x>>y>>z;
        adj[x].pb({{y,1},{z,adj[y].size()}});
        input[i]={x,adj[x].size()-1};
        adj[y].pb({{x,2},{0,adj[x].size()-1}});
    }

    ll s,t; cin>>s>>t;
    fordFulkerson(adj,s,t,input);

    printFlowPaths(adj, s, t);
}

int main() {
    FAST_IO;
    int T; 
    T=1;
    for(int I=1;I<=T;I++){
        solve();
    }
    return 0;
}




