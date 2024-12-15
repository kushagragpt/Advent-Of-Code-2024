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
    ll n,m;
    n=50,m=50;
    vector<vector<char>>a(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }
    ll sz=20000;
    vector<char>moves(sz);
    for(int i=0;i<sz;i++) cin>>moves[i];
    ll r,c;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='@'){
                r=i,c=j;break;
            }
        }
    }
    for(int i=0;i<sz;i++){
        if(moves[i]=='^'){
            if(a[r-1][c]=='.'){
                swap(a[r][c],a[r-1][c]);
                r--;
            }
            else if(a[r-1][c]=='#') continue;
            else{
                ll j=r-1;
                while(a[j][c]=='O') j--;
                if(a[j][c]=='#') continue;
                else{
                    for(int k=j;k<=r-1;k++) a[k][c]=a[k+1][c];
                    a[r][c]='.';
                    r--;
                }
            }
        }
        else if(moves[i]=='v'){
            if(a[r+1][c]=='.'){
                swap(a[r][c],a[r+1][c]);
                r++;
            }
            else if(a[r+1][c]=='#') continue;
            else{
                ll j=r+1;
                while(a[j][c]=='O') j++;
                if(a[j][c]=='#') continue;
                else{
                    for(int k=j;k>=r+1;k--) a[k][c]=a[k-1][c];
                    a[r][c]='.';
                    r++;
                }
            }
        }
        else if(moves[i]=='<'){
            if(a[r][c-1]=='.'){
                swap(a[r][c],a[r][c-1]);
                c--;
            }
            else if(a[r][c-1]=='#') continue;
            else{
                ll j=c-1;
                while(a[r][j]=='O') j--;
                if(a[r][j]=='#') continue;
                else{
                    for(int k=j;k<=c-1;k++) a[r][k]=a[r][k+1];
                    a[r][c]='.';
                    c--;
                }
            }
        }
        else if(moves[i]=='>'){
            if(a[r][c+1]=='.'){
                swap(a[r][c],a[r][c+1]);
                c++;
            }
            else if(a[r][c+1]=='#') continue;
            else{
                ll j=c+1;
                while(a[r][j]=='O') j++;
                if(a[r][j]=='#') continue;
                else{
                    for(int k=j;k>=c+1;k--) a[r][k]=a[r][k-1];
                    a[r][c]='.';
                    c++;
                }
            }
        }
        // cout<<moves[i]<<endl;
        
    }
    for(int x=0;x<n;x++){
            for(int y=0;y<m;y++) cout<<a[x][y];
            cout<<endl;
        }
        cout<<endl;

    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='O') ans+=(ll)100*i+j;
        }
    }
    cout<<ans;
    
}