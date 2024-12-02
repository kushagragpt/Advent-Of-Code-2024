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

bool check(vector<ll>&a){
    ll n=a.size();
    bool flag=true;
    for(int i=1;i<n && flag;i++){
        if(abs(a[i]-a[i-1])>=1 && abs(a[i]-a[i-1])<=3) continue;
        else flag=false;
    }
    return flag;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll ans=0;
    for(int i=0;i<1000;i++){
        string s;
        
        getline(cin,s);
        
        vector<ll>a;
        istringstream stream(s);
        ll num;
        while(stream >> num){
            a.pb(num);
        }
        // for(int i=0;i<a.size();i++) cout<<a[i]<<" ";
        // cout<<endl;
        if(check(a)){
            ll flag=true;
            ll n=a.size();
            if(a[1]-a[0]>0){
                for(int i=1;i<n && flag;i++){
                    if(a[i]-a[i-1]<0) flag=false;
                }
            }
            else{
                for(int i=1;i<n && flag;i++){
                    if(a[i]-a[i-1]>0) flag=false;
                }
            }
            if(flag) ans++;
        }
        a={};
    }
    cout<<ans;
}