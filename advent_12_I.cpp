#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double

vector<ll>dr={0,-1,0,1};
vector<ll>dc={-1,0,1,0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,m;
    n=140;m=140;
    vector<vector<char>>a(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin>>a[i][j];
    }
    ll ans1=0,ans2=0;
    vector<vector<bool>>seen(n,vector<bool>(m,false));
    map<pair<ll,ll>,set<pair<ll,ll>>>dirmap;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!seen[i][j]){
                queue<pair<ll,ll>>q;
                q.push({i,j});
                ll area=0,peri=0;
                dirmap.clear();
                while(!q.empty()){
                    auto cur=q.front();
                    q.pop();
                    ll r=cur.f,c=cur.s;
                    if(seen[r][c]) continue;
                    seen[r][c]=true;
                    area++;
                    for(int k=0;k<4;k++){
                        ll nr=r+dr[k],nc=c+dc[k];
                        if(nr>=0 && nr<n && nc>=0 && nc<m && a[nr][nc]==a[r][c]){
                            q.push({nr,nc});
                        }
                        else{
                            peri++;
                            dirmap[{dr[k],dc[k]}].insert({r,c});
                        }
                    }
                }
                // cout<<area<<" "<<peri<<endl;
                ll sides=0;
                for(auto it:dirmap){
                    pair<ll,ll>dir=it.first;
                    set<pair<ll,ll>>s=it.second;
                    set<pair<ll,ll>>seen;
                    for(auto it2:s){
                        ll r=it2.f,c=it2.s;
                        if(seen.find({r,c})==seen.end()){
                            sides++;
                            queue<pair<ll,ll>>q;
                            q.push({r,c});
                            while(!q.empty()){
                                auto cur=q.front();
                                q.pop();
                                ll x=cur.f;ll y=cur.s;
                                if(seen.find({x,y})!=seen.end()) continue;
                                seen.insert({x,y});
                                for(int k=0;k<4;k++){
                                    ll nx=x+dr[k];ll ny=y+dc[k];
                                    if(s.find({nx,ny})!=s.end()){
                                        q.push({nx,ny});
                                    }
                                }
                            }
                        }
                    }
                }
                ans1+=(area*peri);
                ans2+=(area*sides);
            }
        }
    }
    cout<<ans1<<endl<<ans2;
}