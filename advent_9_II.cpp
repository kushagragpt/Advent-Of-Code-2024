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
    
    vector<pair<ll,ll>>dotsizes;
    vector<pair<ll,ll>>idsizes;
    for(int i=0;i<ind;i++){
        ll sind=i;
        string temp=m[i];
        ll len=0;
        while(i<ind&&m[i]==temp){
            i++;
            len++;
        }
        if(temp==".") dotsizes.pb({sind,len});
        else idsizes.pb({sind,len});
        i--;
    }
    // cout<<idsizes.size()<<endl;
    for(auto it:m)cout<<it.second;
    cout<<endl;
    sort(dotsizes.begin(),dotsizes.end());
    for(int i=0;i<idsizes.size();i++) cout<<idsizes[i].f<<" "<<idsizes[i].s<<endl;
    id--;
    for(id;id>=0;id--){
        ll idsize=idsizes[id].second;
        ll idsind=idsizes[id].first;
        for(int i=0;i<idsind;i++){
            if(m[i]=="."){
                ll len=0;
                ll sind=i;
                while(m[i]==".") {len++;i++;}
                if(len>=idsize){
                    for(int j=sind;j<sind+idsize;j++){
                        m[j]=to_string(id);
                    }
                    for(int j=idsind;j<idsind+idsize;j++) m[j]=".";
                    break;
                }
            }
        }
    }
    for(auto it:m) cout<<it.second;
    cout<<endl;
    ll ans=0;
    ll sz=m.size();
    for(int i=0;i<sz;i++){
        if(m[i]!=".") ans+=(i*stoll(m[i]));
    }
    cout<<ans;
}