#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double


ll n=101;
ll m=103;

struct Robot{
    ll px,py,vx,vy;
};

vector<ll>dr={1,-1,0,0};
vector<ll>dc={0,0,1,-1};

void bfs(vector<vector<char>>&pos,vector<vector<bool>>&visit, ll i, ll j){
    queue<pair<ll,ll>>q;
    q.push({i,j});
    visit[i][j]=true;
    while(!q.empty()){
        auto cur=q.front();
        q.pop();
        ll r=cur.first;ll c=cur.second;
        for(int k=0;k<4;k++){
            ll nr=r+dr[k];ll nc=c+dc[k];
            if(nr<n && nr>=0 && nc<m && nc>=0 && !visit[nr][nc] && pos[nr][nc]=='#'){
                visit[nr][nc]=true;
                q.push({nr,nc});
            }
        }
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    vector<Robot>a;
    while(getline(cin,line)){
        char temp;
        Robot robot;
        stringstream ss(line);
        ss>>temp>>temp>>robot.px>>temp>>robot.py>>temp>>temp>>robot.vx>>temp>>robot.vy;
        a.pb(robot);
    }
    for(int t=1;t<=100;t++){
       
        for(auto& robot:a){
            robot.px=(robot.px+robot.vx+n)%n;
            robot.py=(robot.py+robot.vy+m)%m;
            
        }
        
    }
    
    ll q1=0,q2=0,q3=0,q4=0;
    for(auto& robot:a){
        ll px=robot.px,py=robot.py;
        if(px==n/2 || py==m/2) continue;
        else if(px<n/2 && py<m/2) q1++;
        else if(px<n/2 && py>m/2) q2++;
        else if(px>n/2 && py<m/2) q3++;
        else if(px>n/2 && py>m/2) q4++;
    }
    cout<<q1*q2*q3*q4;
       

}
