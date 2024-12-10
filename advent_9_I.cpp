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
    cin>>s;
    
    ll n=s.size();
    ll id=0;
    map<ll,string>m;
    ll ind=0;
    for(int i=0;i<n;i++){
        if(i%2==0){
            ll times=s[i]-'0';
            string temp=to_string(id);
            id++;
            for(int j=0;j<times;j++){
                m[ind]=temp;
                ind++;
            }
        }
        else{
            ll times=s[i]-'0';
            for(int j=0;j<times;j++){
                m[ind]=".";
                ind++;
            }
        }
    }
    // for(auto it:m) cout<<it.first<<" "<<it.second<<endl;
    ll sz=ind;
    ll it1=0;
    ll it2=sz-1;
   while (it2 > it1) {
    // Find the rightmost non-free space block (file)
    while (it2 >= 0 && m[it2] == ".") it2--;
    
    // Find the leftmost free space block
    while (it1 < sz && m[it1] != ".") it1++;

    // If both pointers are valid, move the file from it2 to it1
    if (it1 < it2) {
        m[it1] = m[it2];
        m[it2] = ".";  // Mark the old file position as free space
    }

    // Move the pointers inward
    it2--;
    it1++;
}
    ll ans=0;
    // for(auto it:m) cout<<it.second;
    cout<<endl;
    for(auto it:m){
        string temp=it.second;
        
        if(temp==".") break;
        ll num=stoll(temp);
        ans+=(it.first*num);
    }
    cout<<ans;
}