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

ll solve(ll val,ll blinks,map<pair<ll,ll>,ll>&m){
    if(m.find({val,blinks})!=m.end()){
        return m[{val,blinks}];
    }
    if(blinks==0) return 1;
    if(val==0){
        return m[{val,blinks}]=solve((ll)1,blinks-1,m);
    }
    string temp=to_string(val);
    ll sz=temp.size();
    if(sz%2==0){
        ll mid=sz/2;
        string left=temp.substr(0,mid);
        string right=temp.substr(mid);
        
        ll leftcount=solve(stoll(left),blinks-1,m);
        ll rightcount=solve(stoll(right),blinks-1,m);
        return m[{val,blinks}]=leftcount+rightcount;
    }
    return m[{val,blinks}]=solve((ll)(val*(ll)2024),blinks-1,m);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll>a;
    ll temp;
    while(cin>>temp){
        a.pb(temp);
    }
    ll n=a.size();
    map<pair<ll,ll>,ll>m;
    ll ans=0;
    for(int i=0;i<n;i++){
        ans+=solve(a[i],75,m);
    }
    cout<<ans;
}