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
