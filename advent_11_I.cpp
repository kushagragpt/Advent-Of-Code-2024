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

void blink(vector<string>&a){
    vector<string>newstones;
    for(auto stone:a){
        if(stone=="0"){
            newstones.pb("1");
        }
        else if(stone.size()%2==0){
            ll mid=stone.size()/2;
            string left=stone.substr(0,mid);
            string right=stone.substr(mid);
            if (!left.empty() && left[0] == '0') left.erase(0, left.find_first_not_of('0'));
            if (!right.empty() && right[0] == '0') right.erase(0, right.find_first_not_of('0'));

            newstones.push_back(left.empty() ? "0" : left);
            newstones.push_back(right.empty() ? "0" : right);
        }
        else{
            ll num=stoll(stone);
            newstones.pb(to_string(num*2024));
        }
    }
    a=newstones;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string>a={"337", "42493", "1891760", "351136", "2" ,"6932", "73", "0"};
    ll blinks=25;
    for(int i=0;i<blinks;i++){
        blink(a);
    }
    cout<<a.size();
}