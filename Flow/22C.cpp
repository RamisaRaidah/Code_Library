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

void solve(){
    ll n,m; cin>>n>>m;
    vector<vll> gang(n, vll(7)), asc(m,vll(7));
    vector<vector<pair<pll,pll>>> adj(n+m+2);

    for(int i=0;i<n;i++){
        cin>>gang[i][0]>>gang[i][1]>>gang[i][2]>>gang[i][3]>>gang[i][4]>>gang[i][5]>>gang[i][6];
        adj[n+m].pb({{i,1},{1,adj[i].size()}});
        adj[i].pb({{n+m,2},{0,adj[n+m].size()-1}});
    }

    for(int i=0;i<m;i++){
        cin>>asc[i][0]>>asc[i][1]>>asc[i][2]>>asc[i][3]>>asc[i][4]>>asc[i][5]>>asc[i][6];
        adj[n+m+1].pb({{i+n,1},{0,adj[i+n].size()}});
        adj[i+n].pb({{n+m+1,2},{1,adj[n+m+1].size()-1}});
    }

    for(int i=0;i<n;i++){
        for(int j=n;j<m+n;j++){
            int x=j-n;
            if(abs(gang[i][0]-asc[x][0])<=12 && abs(gang[i][1]-asc[x][1])<=5 && (gang[i][2]==asc[x][2]) &&
                (gang[i][3]==asc[x][3]) && (gang[i][4]+asc[x][4]>=1) && (gang[i][5]+asc[x][5]>=10)
                && (gang[i][6]&asc[x][6])){
                    adj[i].pb({{j,1},{1,adj[j].size()}});
                    adj[j].pb({{i,2},{0,adj[i].size()-1}});
                }     
        }
    }

    fordFulkerson(adj,n+m,n+m+1);
    
}

int main() {
    FAST_IO;
    int T; 
    T=1;
    cin >> T;
    for(int I=1;I<=T;I++){
        cout<<"Case "<<I<<": ";
        solve();
    }
    return 0;
}
