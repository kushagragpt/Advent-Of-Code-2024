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

vector<ll>dr={1,-1,0,0};
vector<ll>dc={0,0,-1,1};

bool inbound(ll i,ll j, ll n, ll m){
    return (i>=0 && i<n && j>=0 && j<m);
}

vector<vector<ll>> mintime(vector<vector<char>>&a, ll si, ll sj){
    ll n=a.size();
    ll m=a[0].size();
    vector<vector<bool>>visit(n,vector<bool>(m,false));
    vector<vector<ll>>dis(n,vector<ll>(m,LLONG_MAX));
    
    queue<pair<ll,pair<ll,ll>>>q;
    q.push({0,{si,sj}});
    dis[si][sj]=0;
    visit[si][sj]=true;
    while(!q.empty()){
        auto cur=q.front();
        ll time=cur.first;
        ll r=cur.second.first,c=cur.second.second;
        q.pop();
        
        for(int k=0;k<4;k++){
            ll nr=r+dr[k],nc=c+dc[k];
            if(inbound(nr,nc,n,m) && !visit[nr][nc] && (a[nr][nc]=='E' || a[nr][nc]=='.')){
                q.push({time+1,{nr,nc}});
                visit[nr][nc]=true;
                dis[nr][nc]=time+1;
                
            }
        }
    }
    
    return dis;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n=141,m=141;
    vector<vector<char>>a(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }
  
    pair<ll,ll>s,e;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='S'){
                s.first=i,s.second=j;
            }
            if(a[i][j]=='E'){
                e.first=i,e.second=j;
            }
        }
    }
    // state will be as (r,c,time,cheatremaining,what cheat was used)
    vector<vector<ll>>disfroms=mintime(a,s.first,s.second);
    vector<vector<ll>>disfrome=mintime(a,e.first,e.second);
    ll nocheattime=disfroms[e.first][e.second];
    int ans = 0;
    //7,10
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='#'){
                for(int k=0;k<4;k++){
                    ll ni=i+dr[k],nj=j+dc[k];
                    ll iskatime=nocheattime;
                    //   if(i==7 && j==6 && k==2 ) cout<<iskatime<<" "<<ni<<" "<<nj<<disfrome[ni][nj]<<" "<<a[ni][]
                    if(inbound(ni,nj,n,m) && (a[ni][nj]=='.' || a[ni][nj]=='E')  && disfrome[ni][nj]!=LLONG_MAX){
                        for(int l=0;l<4;l++){
                            if(l!=k){
                                
                                ll nni=i+dr[l],nnj=j+dc[l];
                                if(inbound(nni,nnj,n,m) && (a[nni][nnj]=='.' || a[nni][nnj]=='S') && disfroms[nni][nnj]!=LLONG_MAX){
                                    ll newtime=disfroms[nni][nnj]+2+disfrome[ni][nj];
                                    iskatime=min(iskatime,newtime);
                                }
                              
                            }
                        }
                    }
                    
                    if(iskatime<=nocheattime-100) ans++;
                }
            }
        }
    }
    cout<<ans<<endl;


}
