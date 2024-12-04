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

bool xmas(vector<string>&a){
    string s="";
    s+=a[0][0];s+=a[1][1];s+=a[2][2];
    string r="";
    r+=a[0][2];r+=a[1][1];r+=a[2][0];
    
    if((s=="MAS" || s=="SAM") && (r=="MAS" || r=="SAM")) return true;
    else return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string>a(140);
    for(int i=0;i<140;i++){
        string s;
        cin>>s;
        a[i]=s;
        // cout<<a[i]<<endl;
    }
    ll n=a.size();
    ll ans=0;
    ll m=a[0].size();
    cout<<n<<" "<<m<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cout<<a[i][j];
        cout<<endl;
    }
    for(int i=0;i<n-2;i++){
        for(int j=0;j<m-2;j++){
            vector<string>b(3);
            b[0]="";b[1]="";b[2]="";
            b[0] = a[i].substr(j, 3);
            b[1] = a[i + 1].substr(j, 3);
            b[2] = a[i + 2].substr(j, 3);

            // cout<<b[0]<<endl<<b[1]<<endl<<b[2]<<endl;
            ans+=xmas(b);
        }
    }
    cout<<ans<<endl;
}