
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

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<ll>toposort(map<ll,vector<ll>>&adj){
    map<ll,ll>indeg;
    for(auto it:adj){
        ll u=it.first;
        vector<ll>adjnode=it.second;
        if(indeg.find(u)==indeg.end()){
            indeg[u]=0;
        }
        for(ll node:adjnode){
            indeg[node]++;
        }
    }
    queue<ll>q;
    for(auto it:indeg){
        if(it.second==0) q.push(it.first);
    }
    vector<ll>topo;
    while(!q.empty()){
        ll cur=q.front();
        q.pop();
        topo.pb(cur);
        for(ll node:adj[cur]){
            indeg[node]--;
            if(indeg[node]==0) q.push(node);
        }
    }
    return topo;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map<ll,vector<ll>>adj;
    string s;
    while(getline(cin,s) && !s.empty()){
        vector<string>part=split(s,'|');
        ll u=stoi(part[0]);ll v=stoi(part[1]);
        adj[u].pb(v);
    }
    vector<ll>topo=toposort(adj);
    vector<vector<ll>>updates;
    while(getline(cin,s) && !s.empty()){
        vector<ll>update;
        vector<string>part=split(s,',');
        for(int i=0;i<part.size();i++){
            update.pb(stoi(part[i]));
        }
        updates.pb(update);
    }
    map<ll,ll>m;
    for(int i=0;i<topo.size();i++){
        m[topo[i]]=i+1;
    }
    ll ans=0;
    for(auto it:updates){
        vector<ll>temp=it;
        for(int i=0;i<temp.size();i++){
            ll u=m[temp[i]];
            temp[i]=u;
        }
        vector<ll>b=temp;
        vector<ll>a=it;
        sort(b.begin(),b.end());
        ll mid=temp.size()/2;
        if(b==temp){
            ans+=a[mid];
        }
    }
    cout<<ans<<endl;
}
