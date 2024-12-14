#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define pb push_back
#define f first
#define s second
#define ld long double


struct Machine {
    ll ax, ay; // Movement for button A
    ll bx, by; // Movement for button B
    ll px, py; // Prize location
};

ll mintoken(Machine& machine){
    ll tokens=LLONG_MAX;
    bool poss=false;
    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            ll xval=i*machine.ax+j*machine.bx;
            ll yval=i*machine.ay+j*machine.by;
            if(xval==machine.px && yval==machine.py){
                poss=true;
                ll used=i*3+j;
                tokens=min(tokens,used);
            }
        }
    }
    if(poss) return tokens;
    else return (ll)0;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Machine>a;
    string s;
    ll n=320;
    for(int i=0;i<n;i++){
        Machine machine;
        string s;
        getline(cin,s);
        string x;
        string y;
        ll ind;
        x="";y="";
        ll sz=s.size();
        ind=0;
        for(int j=0;j<sz;j++){
            if(s[j]>='0' && s[j]<='9'){
                while(s[j]>='0' && s[j]<='9' && j<sz){
                    x+=s[j];j++;
                }
                machine.ax=stoll(x);
                ind =j;
                break;
            }
        }
        for(int j=ind;j<sz;j++){
            if(s[j]>='0' && s[j]<='9'){
                while(s[j]>='0' && s[j]<='9' && j<sz){
                    y+=s[j];j++;
                }
                machine.ay=stoll(y);
                ind =j;
                break;
            }
        }

        getline(cin,s);
        
        x="";y="";
        sz=s.size();
        ind=0;
        for(int j=0;j<sz;j++){
            if(s[j]>='0' && s[j]<='9'){
                while(s[j]>='0' && s[j]<='9' && j<sz){
                    x+=s[j];j++;
                }
                machine.bx=stoll(x);
                ind =j;
                break;
            }
        }
        for(int j=ind;j<sz;j++){
            if(s[j]>='0' && s[j]<='9'){
                while(s[j]>='0' && s[j]<='9' && j<sz){
                    y+=s[j];j++;
                }
                machine.by=stoll(y);
                ind =j;
                break;
            }
        }

        getline(cin,s);
        
        x="";y="";
        sz=s.size();
        ind=0;
        for(int j=0;j<sz;j++){
            if(s[j]>='0' && s[j]<='9'){
                while(s[j]>='0' && s[j]<='9' && j<sz){
                    x+=s[j];j++;
                }
                machine.px=stoll(x);
                ind =j;
                break;
            }
        }
        for(int j=ind;j<sz;j++){
            if(s[j]>='0' && s[j]<='9'){
                while(s[j]>='0' && s[j]<='9' && j<sz){
                    y+=s[j];j++;
                }
                machine.py=stoll(y);
                ind =j;
                break;
            }
        }
        string blank;
        cin>>blank;
        a.pb(machine);
    }
    ll ans=0;
    for(Machine machine:a){
        // cout<<machine.ax<<" "<<machine.ay<<" "<<machine.bx<<" "<<machine.by<<" "<<machine.px<<" "<<machine.py<<endl;
        ans+=mintoken(machine);
    }
    cout<<ans;
    
}