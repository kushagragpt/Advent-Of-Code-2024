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
    string s;
    getline(cin,s);
    cout<<s<<endl;
    ll ans=0;
    bool enable=true;
    for(int i=0;i<s.size();i++){

        if(s.substr(i,7)=="don't()"){
            enable=false;
            i+=6;
            continue;
        }
        if(s.substr(i,4)=="do()"){
            enable=true;
            i+=3;
            continue;
        }

        if(s.substr(i,4)=="mul(" && enable){
            ll j=i+4;
            string num1="",num2="";
            bool valid=true;
            bool foundcomma=false;
            while(j<s.size() && s[j]!=')'){
                if(isdigit(s[j])){
                    if(!foundcomma){
                        num1+=s[j];
                    }
                    else num2+=s[j];
                }
                else if(s[j]==','){
                    if(foundcomma){
                        valid=false;
                        break;
                    }
                    foundcomma=true;
                }
                else{
                    valid=false;
                    break;
                }
                j++;
            }
            if(valid && !num1.empty() && !num2.empty() && s[j]==')'){
                ll a=stoi(num1);
                ll b=stoi(num2);
                ans+=(a*b);
            }
            i=j;

            
        }
    }
    cout<<enable<<endl;
    cout<<ans;
}