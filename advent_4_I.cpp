// #include<bits/stdc++.h>

// using namespace std;

// #define ll long long int
// #define pb push_back
// #define f first
// #define s second
// #define ld long double

// // code for disjoint set union (by size)
// ll findpar(ll node,vector<ll>&par){
//     if(node==par[node]) return node;
//     return par[node]=findpar(par[node],par);
// }
// void ubs(ll u, ll v,vector<ll>&par,vector<ll>&size){
//     ll ulp_u=findpar(u,par);
//     ll ulp_v=findpar(v,par);
//     if(ulp_v==ulp_u) return;
//     if(size[ulp_u]<size[ulp_v]){
//         par[ulp_u]=ulp_v;
//         size[ulp_v]+=size[ulp_u];
//     }
//     else{
//         par[ulp_v]=ulp_u;
//         size[ulp_u]+=size[ulp_v];
//     }
// }

// ll count(string s){
//     ll n=s.size(); 

//     ll ans=0;
//     ll mul=1;
//     bool flag=true;
//     for(int i=0;i<n;i++){
//         if(s[i]=='X'){
//             ll j=i+1;
//             ll tempc=1;
//             while(j<n && s[j]=='X'){
//                 j++;
//                 tempc++;
//             }
//             mul*=tempc;
//             if(j==n){
//                 flag=false;break;
//             }
//             else{
//                 if(s[j]!='M'){
//                     flag=false;break;
//                 }
//                 tempc=1;
//                 ll k=j+1;
//                 while(k<n && s[k]=='M'){
//                     tempc++;
//                     k++;
//                 }
//                 mul*=tempc;
//                 if(k==n){
//                     flag=false;
//                     break;
//                 }
//                 else{
//                     if(s[k]!='A'){
//                         flag=false;
//                         break;
//                     }
//                     tempc=1;
//                     ll l=k+1;
//                     while(l<n && s[l]=='A'){
//                         tempc++;
//                         l++;
//                     }
//                     mul*=tempc;
//                     if(l==n){flag=false;
//                     break;}
//                     else{
//                         if(s[l]!='S'){flag=false;break;}
//                         tempc=1;
//                         ll m=l+1;
//                         while(m<n&&s[m]=='S'){
//                             tempc++;
//                             m++;
//                         }
//                         mul*=tempc;
//                         ans+=mul;
//                         break;
//                     }
//                 }
//             }
//         }
//     }
//     return ans;
// }

// vector<ll>di={1,1,1,0,0,-1,-1,-1};
// vector<ll>dj={-1,0,1,1,-1,-1,0,1};

// int main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     vector<vector<char>>a(10,vector<char>(10));
//     ll n=10;
//     for(int i=0;i<n;i++){
//         for(int j=0;j<n;j++) cin>>a[i][j];
//     }
//     ll ans=0;
//     for(int i=0;i<n;i++){
//         string s="";
//         for(int j=0;j<n;j++) s+=a[i][j];
//         ans+=count(s);
//         // cout<<s<<endl;
//         reverse(s.begin(),s.end());
//         // cout<<s<<endl;
//         ans+=count(s);
//     }
//     for(int j=0;j<n;j++){
//         string s="";
//         for(int i=0;i<n;i++) s+=a[i][j];
//         ans+=count(s);
//         reverse(s.begin(),s.end());
//         ans+=count(s);
//     }
//     for(int i=0;i<n;i++){
//         string s="";
//         ll tempi=0;
//         for(int j=i;j<n;j++){
            
//                 s+=a[tempi][j];
//             tempi++;
//         }
//         ans+=count(s);
//         // cout<<s<<endl;
//         reverse(s.begin(),s.end());
//         ans+=count(s);
//         if(i!=0){
//         s="";
//         tempi=i;
//         for(int j=0;j<n-i;j++){
//             s+=a[tempi][j];
//             tempi++;
//         }
//          ans+=count(s);
//         //  cout<<s<<endl;
//         reverse(s.begin(),s.end());
//         ans+=count(s);
//         }
//     }
//     for(int i=0;i<n;i++){
//         string s="";
//         ll tempi=0;
//         for(int j=i;j>=0;j--){
//             s+=a[tempi][j];
//             tempi++;
//         }
//          ans+=count(s);
//         //  cout<<s<<endl;
//         reverse(s.begin(),s.end());
//         ans+=count(s);
//         if(i!=n-1){
//         s="";
//         tempi=n-i-1;
//         for(int j=n-1;j>=n-1-i;j--){
//             s+=a[tempi][j];
//             tempi++;
//         }
//          ans+=count(s);
//         //  cout<<s<<endl;
//         reverse(s.begin(),s.end());
//         ans+=count(s);
//         }
//     }

//     cout<<ans;

// }
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Directions for moving in 8 possible ways
const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1}; // Horizontal, vertical, diagonals
const int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int countWordOccurrences(const vector<string>& grid, const string& word) {
    int rows = grid.size();
    int cols = grid[0].size();
    int wordLength = word.size();
    int count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Check in all 8 directions
            for (int dir = 0; dir < 8; ++dir) {
                int k;
                int x = i, y = j;

                // Check if the word can fit in the current direction
                for (k = 0; k < wordLength; ++k) {
                    if (!isValid(x, y, rows, cols) || grid[x][y] != word[k]) {
                        break;
                    }
                    x += dx[dir];
                    y += dy[dir];
                }

                // If the entire word is matched, increment the count
                if (k == wordLength) {
                    ++count;
                }
            }
        }
    }

    return count;
}

int main() {
    vector<string> grid(140);
      
    for(int i=0;i<140;i++){
        string s;
        cin>>s;
        grid[i]=s;
    }

    string word = "XMAS";
    
    int result = countWordOccurrences(grid, word);

    cout << "The word '" << word << "' appears " << result << " times in the grid." << endl;

    return 0;
}