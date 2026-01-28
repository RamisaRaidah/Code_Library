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

ll gcd(ll a, ll b){
    while(b!=0){
        ll temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

ll lcm(ll a, ll b){
    return 1LL*a*b/(gcd(a,b));
}

bool isPrime(ll n) {
    if(n<2) return false;
    if(n%2==0) return n==2;
    if(n%3==0) return n==3;
    for(ll i=5;i*i<=n;i+=6){
        if((n%i==0) || (n%(i+2)==0)) return false;
    }

    return true;
}

int countBits(ll n){
    int cnt=0;
    while(n){
        cnt++; n=n>>1;
    } return cnt;
}

ll nCr(ll n, ll r){
    ld sum = 1;
    for (int i=1;i<=r;i++){
        sum=sum*(n-r+i)/i;
    } return (ll)sum;
}
ll nPr(ll n, ll r) {
    ll res = 1;
    for (int i=0;i<r;i++) {
        res*=(n-i);
    } return res;
}

vector<int> primes, spf; 
void linear_sieve(int n){
    spf.assign(n+1,0);
    for(int i=2;i<=n;i++){
        if(spf[i]==0){
            spf[i]=i;
            primes.pb(i);
        }
        for(int p:primes){
            if(p>spf[i] || 1LL*i*p>n) break;
            spf[i*p]=p;
        }
    }
}


void solve(){
    
}

int main() {
    FAST_IO;
    int T; 
    T=1;
    cin >> T;
    for(int I=1;I<=T;I++){
        solve();
    }
    return 0;
}
