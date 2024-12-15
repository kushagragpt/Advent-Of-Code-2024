#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double

vector<ll>dr={0,0,1,-1};
vector<ll>dc={1,-1,0,0};


vector<pair<pair<ll,ll>,char>> findbox(vector<vector<char>>&a,ll i, ll j, ll b,ll d){
    ll n=a.size();
    ll m=a[0].size();
    vector<vector<bool>>visit(n,vector<bool>(m,false));
    queue<pair<ll,ll>>q;
    vector<pair<pair<ll,ll>,char>>comp;
    q.push({i,j});
    visit[i][j]=true;
    while(!q.empty()){
        auto cur=q.front();
        
        q.pop();
        ll r=cur.first,c=cur.second;
        comp.pb({{r,c},a[r][c]});
        if(a[r][c]=='[' && !visit[r][c+1]){
            visit[r][c+1]=true;
            q.push({r,c+1});
        }
        else if(a[r][c]==']' && !visit[r][c-1]){
            visit[r][c-1]=true;
            q.push({r,c-1});
        }
        
            ll nr=r+b,nc=c+d;
            if((a[nr][nc]=='[' || a[nr][nc]==']') && !visit[nr][nc]){
                visit[nr][nc]=true;
                q.push({nr,nc});
            }
        
    }
    return comp;
}

bool move(vector<vector<char>>&a,vector<pair<pair<ll,ll>,char>>&comp,ll di,ll dj){
    for(auto it:comp){
        ll r=it.first.first,c=it.first.second;
        if(a[r+di][c+dj]=='#') return false;
    }
    for(auto it:comp){
        a[it.f.f][it.f.s]='.';
    }
    for(auto it:comp){
        a[it.f.f+di][it.f.s+dj]=it.s;
    }
    return true;
}

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
    vector<vector<char>>a(n,vector<char>(2*m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char temp;
            cin>>temp;
            if(temp=='#'){
                a[i][2*j]='#';
                a[i][2*j+1]='#';
            }
            else if(temp=='.'){
                a[i][2*j]='.';a[i][2*j+1]='.';
            }
            else if(temp=='@'){
                a[i][2*j]='@';a[i][2*j+1]='.';
            }
            else if(temp=='O'){
                a[i][2*j]='[';a[i][2*j+1]=']';
            }
        }
    }
    ll sz=20000;
    ll x=20,y=1000;
    vector<vector<char>>temp(x,vector<char>(y));;
    for(int i=0;i<x;i++) for(int j=0;j<y;j++) cin>>temp[i][j];
    vector<char>moves;
    for(int i=0;i<x;i++) for(int j=0;j<y;j++) moves.pb(temp[i][j]);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cout<<a[i][2*j]<<a[i][2*j+1];
        cout<<endl;
    }
    cout<<endl;
    ll r,c;
    for(int i=0;i<n;i++){
        for(int j=0;j<2*m;j++){
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
                vector<pair<pair<ll,ll>,char>>temp=findbox(a,r-1,c,-1,0);
                temp.pb({{r,c},'@'});
                if(move(a,temp,-1,0)) r--;
            }
        }
        else if(moves[i]=='v'){
            if(a[r+1][c]=='.'){
                swap(a[r][c],a[r+1][c]);
                r++;
            }
            else if(a[r+1][c]=='#') continue;
            else{
                vector<pair<pair<ll,ll>,char>>temp=findbox(a,r+1,c,1,0);
                temp.pb({{r,c},'@'});
                if(move(a,temp,1,0)) r++;
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
                while(a[r][j]==']' || a[r][j]=='[') j--;
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
                while(a[r][j]=='[' || a[r][j]==']') j++;
                if(a[r][j]=='#') continue;
                else{
                    for(int k=j;k>=c+1;k--) a[r][k]=a[r][k-1];
                    a[r][c]='.';
                    c++;
                }
            }
        }
        
        cout<<moves[i]<<endl<<i+1<<endl;
        for(int x=0;x<n;x++){
            for(int y=0;y<2*m;y++) cout<<a[x][y];
            cout<<endl;
        }
        cout<<endl;
        
    }
    // for(int x=0;x<n;x++){
    //         for(int y=0;y<2*m;y++) cout<<a[x][y];
    //         cout<<endl;
    //     }
    //     cout<<endl;

    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='[') ans+=(ll)100*i+j;
        }
    }
    cout<<ans;
    
}