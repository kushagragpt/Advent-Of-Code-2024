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
    ld b=static_cast<ld>(((ld)machine.ax*(ld)machine.py-(ld)machine.ay*(ld)machine.px)/((ld)machine.ax*(ld)machine.by-(ld)machine.ay*(ld)machine.bx));
    ld a=static_cast<ld>(((ld)machine.px-(ld)machine.bx*(ld)b)/(ld)machine.ax);
    if(a==static_cast<ll>(a) && b==static_cast<ll>(b)) return 3*static_cast<ll>(a)+static_cast<ll>(b);
    else return 0;
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
                machine.px=stoll(x)+10000000000000;
                ind =j;
                break;
            }
        }
        for(int j=ind;j<sz;j++){
            if(s[j]>='0' && s[j]<='9'){
                while(s[j]>='0' && s[j]<='9' && j<sz){
                    y+=s[j];j++;
                }
                machine.py=stoll(y)+10000000000000;
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

