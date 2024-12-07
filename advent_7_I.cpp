#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double

ll concatenate(ll a,ll b){
    string comb=to_string(a)+to_string(b);
    ll res=stoll(comb);
    return res;
}


bool evaluate(vector<ll>&nums,ll ind,ll target, ll curr){
    if(ind==nums.size()){
        return (target==curr);
    }
    if(evaluate(nums,ind+1,target,curr+nums[ind])){
        return true;
    }
    if(evaluate(nums,ind+1,target,curr*nums[ind])){
        return true;
    }
    if(evaluate(nums,ind+1,target,concatenate(curr,nums[ind]))){
        return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    ll ans=0;
    while(getline(cin,line) && !line.empty()){
        istringstream line_stream(line);
        ll target;char colon;
        line_stream>>target>>colon;
        vector<ll>nums;
        ll temp;
        while(line_stream>>temp){
            nums.pb(temp);
        }
       
        if(evaluate(nums,1,target,nums[0])){
            ans+=target;
        }

    }
    cout<<ans;
    
}