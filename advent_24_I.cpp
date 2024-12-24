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
    ll inwires=90;
    map<string,ll>m;
    for(int i=0;i<inwires;i++){
        string s;
        getline(cin,s);
        string wire;wire+=s[0];wire+=s[1];wire+=s[2];
        string value;value+=s[5];
        ll val=stoll(value);
        m[wire]=val;
        cout<<wire<<" "<<m[wire]<<endl;
    }
    string skip;getline(cin,skip);
    vector<string>gate;
    ll gates=222;
    for(int i=0;i<gates;i++){
        string s;
        getline(cin,s);
        gate.pb(s);
        cout<<s<<endl;
    }
    set<pair<ll,ll>>num;
    while(num.size()<46){
        for(int i=0;i<gates;i++){
            string s=gate[i];
            string wire1;wire1+=s[0];wire1+=s[1];wire1+=s[2];
            string type;type+=s[4];type+=s[5];if(type[0]!='O') type+=s[6];
            string wire2;if(type[0]=='O'){wire2+=s[7];wire2+=s[8];wire2+=s[9];} else{wire2+=s[8];wire2+=s[9];wire2+=s[10];}
            string outwire;if(type[0]=='O'){outwire+=s[14];outwire+=s[15];outwire+=s[16];} else {outwire+=s[15];outwire+=s[16];outwire+=s[17];}
            if(m.find(wire1)!=m.end() && m.find(wire2)!=m.end()){
                ll val;
                if(type=="AND") val=(m[wire1]&m[wire2]);
                else if(type=="OR") val=(m[wire1]|m[wire2]);
                else val=(m[wire1]^m[wire2]);
                m[outwire]=val;
                if(outwire[0]=='z'){
                    string form; form+=outwire[1];form+=outwire[2];
                    ll pos=stoll(form);
                    num.insert({pos,val});
                    if(num.size()==46) break;
                }
            }
        }
    }
    
    ll ans=0;
    for(auto it:num){
        ll power=it.first;
        cout<<it.second;
        if(it.second==1)ans+=(1<<power);
    }
    cout<<endl;
    cout<<ans;
}