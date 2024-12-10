#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double


vector<ll>dr={0,0,1,-1};
vector<ll>dc={1,-1,0,0};
bool inbound(ll i, ll j, ll n, ll m){
    return (i>=0 && i<n && j>=0 && j<m);
}

ll score(ll r, ll c, vector<vector<char>>&a, ll n, ll m){
    ll ans=0;
    vector<vector<bool>>visit(n,vector<bool>(m,false));
    visit[r][c]=true;
    queue<pair<ll,ll>>q;
    q.push({r,c});
    while(!q.empty()){
        auto cur=q.front();
        q.pop();
        r=cur.f;c=cur.s;
        char val=a[r][c];
        if(val=='9' && !visit[r][c]){
            ans++;
            visit[r][c]=true;
            continue;
        }
        visit[r][c]=true;
        for(int k=0;k<4;k++){
            ll nr=r+dr[k];
            ll nc=c+dc[k];
            if(inbound(nr,nc,n,m) && a[nr][nc]==val+1){
                q.push({nr,nc});
            }
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,m;
    n=40;m=40;
    vector<vector<char>>a(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='0'){
                ans+=score(i,j,a,n,m);
            }
        }
    }
    cout<<ans;
}