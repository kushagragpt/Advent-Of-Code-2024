#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double

ll todec(ll num){
    ll res=0,power=0;
    while(num){
        ll digit=num%10;
        res+=pow(8,power)*digit;
        power++;
        num/=10;
    }
    return res;
}

bool isoct(ll num){
    while(num){
        ll digit=num%10;
        if(num>7) return false;
        num/=10;
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
    ll a,b,c;
    string s;
    getline(cin,s);
    ll sz=s.size();
    string temp;
    for(int i=0;i<sz;i++){
        if(s[i]>='0' && s[i]<='9'){
            ll j=i;
            while(s[j]>='0'&& s[j]<='9'&& j<sz ){
                temp+=s[j];j++;
            }
            a=stoll(temp);
            i=j;
        }
    }
    s="";
    getline(cin,s);
    sz=s.size();
    temp="";
    for(int i=0;i<sz;i++){
        if(s[i]>='0' && s[i]<='9'){
            ll j=i;
            while(s[j]>='0'&& s[j]<='9'&& j<sz ){
                temp+=s[j];j++;
            }
            b=stoll(temp);
        }
    }
    s="";
    getline(cin,s);
    sz=s.size();
    temp="";
    for(int i=0;i<sz;i++){
        if(s[i]>='0' && s[i]<='9'){
            ll j=i;
            while(s[j]>='0'&& s[j]<='9'&& j<sz ){
                temp+=s[j];j++;
            }
            c=stoll(temp);
        }
    }
    // cout<<a<<endl<<b<<endl<<c<<endl;
    s="";
    getline(cin,s);
    getline(cin,s);
    vector<ll>program;
    sz=s.size();
    for(int i=0;i<sz;i++){
        temp="";
        if(s[i]>='0' && s[i]<='9'){
            ll j=i;
            while(s[j]>='0' && s[j]<='9' && j<sz){
                temp+=s[j];j++;
            }
            program.pb(stoll(temp));
        }
    }
    
    ll n=program.size();
    // for(int i=0;i<n;i++) cout<<program[i]<<" ";
    // cout<<endl;
    string in="2411754003165530";
    map<char,ll>m;
    for(int i=0;i<in.size();i++)m[in[i]]++;
    // cout<<in<<endl;
    // a=todec(a;
    // sort(program.begin(),program.end());
    for(int i=0;i<n;i++) cout<<program[i];
    cout<<endl;
        string result="";
        for(int i=0;i<n;i+=2){
            ll opcode=program[i];
            if(i+1>=n) break;
            ll operand=program[i+1];
            // if(operand==3) cout<<a<<" "<<b<<" "<<c<<endl;
            ll val;
            if(operand>=0 && operand<=3) val=operand;
            if(operand==4) val=a;
            if(operand==5) val=b;
            if(operand==6) val=c;
            if(operand==7) val=-1;
            if(opcode==0){
                ll num=a;
                ll den=(1LL<<val);
                ll ans=(num/den);
                a=ans;
            }
            else if(opcode==1){
                ll ans=(b^operand);
                b=ans;
            }
            else if(opcode==2){
                ll ans=val%8;
                b=ans;
            }
            else if(opcode==3){
                if(a==0) continue;
                else{
                    if(i==operand) continue;
                    else i=operand-2;
                }
            }
            else if(opcode==4){
                ll ans=(b^c);
                b=ans;
            }
            else if(opcode==5){
                ll val1=val%8;
                result+=(to_string(val1));
                // if(result.size()>in.size()) break;
            }
            else if(opcode==6){
                ll num=a;
                ll den=(1LL<<val);
                ll ans=(num/den);
                b=ans;
            }
            else if(opcode==7){
                ll num=a;
                ll den=(1LL<<val);
                ll ans=(num/den);
                c=ans;
            }
        }
       
        cout<<result;
        // 1
    
}
