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

template <typename T>
void printv(const vector<T>& v) {
    int n=v.size();
    for (int i=0;i<n;i++) {
        cout<<v[i]<<(i+1<n?" " :"\n");
    }
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

void fordFulkerson(vector<vector<pair<pll,pll>>> &adj, ll s, ll t){
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
}

ld dist(pair<ld,ld> &p1,pair<ld,ld> &p2){
    return (sqrt((p1.fi-p2.fi)*(p1.fi-p2.fi)+(p1.se-p2.se)*(p1.se-p2.se)));
}

void solve(){
    ll m,h; ld r; cin>>m>>h>>r;
    vector<vector<pair<pll,pll>>> adj(m+h+2);
    map<ll,pair<ld,ld>> rmp;
    for(int i=0;i<m;i++){
        ld x,y; cin>>x>>y;
        rmp[i]={x,y};
        adj[m+h].pb({{i,1},{1,adj[i].size()}});
        adj[i].pb({{m+h,2},{0,adj[m+h].size()-1}});
    }
    
    for(int i=0;i<h;i++){
        ld x,y; ll c; cin>>x>>y>>c;
        rmp[m+i]={x,y};           
        adj[m+h+1].pb({{m+i,2},{0,adj[m+i].size()}});
        adj[i+m].pb({{m+h+1,1},{c,adj[m+h+1].size()-1}});
    }
    for(int i=0;i<m;i++){
        for(int j=m;j<m+h;j++){
            if(dist(rmp[i],rmp[j])>r) continue;
            adj[i].pb({{j,1},{1,adj[j].size()}});
            adj[j].pb({{i,1},{0,adj[i].size()-1}});
        }
    }

    fordFulkerson(adj,m+h,m+h+1);
}

int main() {
    FAST_IO;
    int T; 
    T=1;
    cin>>T;
    for(int I=1;I<=T;I++){
        cout<<"Case "<<I<<": ";
        solve();
    }
    return 0;
}
