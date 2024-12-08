#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double

// code for disjoint set union (by size)
ll findpar(ll node,vector<ll>&par){
    if(node==par[node]) return node;
    return par[node]=findpar(par[node],par);
}
void ubs(ll u, ll v,vector<ll>&par,vector<ll>&size){
    ll ulp_u=findpar(u,par);
    ll ulp_v=findpar(v,par);
    if(ulp_v==ulp_u) return;
    if(size[ulp_u]<size[ulp_v]){
        par[ulp_u]=ulp_v;
        size[ulp_v]+=size[ulp_u];
    }
    else{
        par[ulp_v]=ulp_u;
        size[ulp_u]+=size[ulp_v];
    }
}

bool inbound(ll i, ll j, ll n, ll m){
    return (i>=0 && i<n && j>=0 && j<m);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,m;
    n=50;m=50;
    vector<vector<char>>a(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }
    map<char,vector<pair<ll,ll>>>pos;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char ch=a[i][j];
            if(ch!='.'){
                pos[ch].pb({i,j});
            }
        }
    }
    vector<vector<bool>>taken(n,vector<bool>(m,false));
    for(auto it:pos){
        vector<pair<ll,ll>>temp=it.second;
        ll sz=temp.size();
        for(int i=0;i<sz;i++){
            for(int j=i+1;j<sz;j++){
                pair<ll,ll>pehla=temp[i];
                pair<ll,ll>dusra=temp[j];
                
                ll dr=dusra.first-pehla.first;
                ll dc=dusra.second-pehla.second;
                ll r=dusra.first;ll c=dusra.second;
                while(inbound(r,c,n,m)){
                    taken[r][c]=true;
                    r+=dr;c+=dc;
                }
                r=pehla.f;c=pehla.s;
                while(inbound(r,c,n,m)){
                    taken[r][c]=true;;
                    r-=dr;c-=dc;
                }
            }
        }
    }
    
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) if(taken[i][j]) ans++;
    }
    cout<<ans;
}