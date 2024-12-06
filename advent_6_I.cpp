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
vector<ll>dr={-1,0,1,0};
vector<ll>dc={0,1,0,-1};

bool cycle(vector<vector<char>>&a,ll r,ll c, ll dir){
    ll n=a.size();
    ll m=a[0].size();
    vector<vector<vector<bool>>>visit(n,vector<vector<bool>>(m,vector<bool>(4,false)));
    while(true){
        if(visit[r][c][dir]) return true;
        visit[r][c][dir]=true;
        r+=dr[dir];c+=dc[dir];
        if(r>=n || r<0 || c>=m || c<0) break;
        else if(a[r][c]=='#'){
            r-=dr[dir];
            c-=dc[dir];
            dir=(dir+1)%4;
        }
        
    }
    return false;
}


void move(vector<vector<char>>&a,ll r,ll c,ll dir,vector<vector<bool>>&visit){
    ll n=a.size();
    ll m=a[0].size();
    visit[r][c]=true;
    r+=dr[dir];c+=dc[dir];
    while(r<n && r>=0 && c<m && c>=0 && (a[r][c]=='.' || a[r][c]=='^')){
        visit[r][c]=true;
        r+=dr[dir];
        c+=dc[dir];
    }
    if(r<n && r>=0 && c<m && c>=0){
        r-=dr[dir];
        c-=dc[dir];
        dir=(dir+1)%4;
        move(a,r,c,dir,visit);
    }
    else return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n=130,m=130;
    vector<vector<char>>a(n,vector<char>(m));
    ll r,c;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];
            if(a[i][j]=='^'){
                r=i;c=j;
            }
        }
    }
    // cout<<r<<" "<<c<<endl;
    ll dir=0;
    vector<vector<bool>>visit(n,vector<bool>(m,false));
    move(a,r,c,dir,visit);
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++) cout<<visit[i][j]<<" ";
    //     cout<<endl;
    // }
    // cout<<r<<" "<<c<<endl;
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(visit[i][j] && a[i][j]=='.'){
                a[i][j]='#';
                if(cycle(a,r,c,0)) ans++;
                a[i][j]='.';
            }
        }
    }
    cout<<ans;
}

