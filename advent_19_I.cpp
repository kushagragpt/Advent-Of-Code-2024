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
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    getline(cin,s);
    set<string>designs;
    ll sz=s.size();
    for(int i=0;i<sz;i++){
        string temp;
        if(s[i]>='a' && s[i]<='z'){
            ll j=i;
            while(j<sz && s[j]>='a' && s[j]<='z'){
                temp+=s[j];
                j++;
            }
            designs.insert(temp);
            i=j-1;
        }
    }
    ll larsize=(*designs.rbegin()).size();
    // for(auto it:designs) cout<<it<<endl;
    getline(cin,s);
    ll ans=0;
    for(int i=0;i<400;i++){
        cin>>s;
        
        ll n=s.size();
        vector<bool>dp(n+1,false);
        dp[0]=true;
        for(int j=1;j<=n;j++){
            for(auto design:designs){
                ll len=design.size();
                if(j>=len && s.substr(j-len,len)==design && dp[j-len]){
                    dp[j]=true;
                    break;
                }
            }
        }
        if(dp[n]) ans++;
    }
    cout<<ans;
}