#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

// Directions for moving in the grid (right, down, left, up)
const int dr[] = {1, 0, -1, 0};
const int dc[] = {0, 1, 0, -1};

int main() {
    int n = 71; // Size of the grid
    

    vector<pair<int, int>> incomingBytes;
    for (int it = 0; it < 3450; it++) {
        string s;
        getline(cin, s);
        int sz = s.size();
        int first, second;
        int ind;
        for (int i = 0; i < sz; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                int j = i;
                string temp;
                while (j < sz && s[j] >= '0' && s[j] <= '9') {
                    temp += s[j];
                    j++;
                }
                ind = j;
                first = stoi(temp);
                break;
            }
        }
        for (int i = ind; i < sz; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                int j = i;
                string temp;
                while (j < sz && s[j] >= '0' && s[j] <= '9') {
                    temp += s[j];
                    j++;
                }
                second = stoi(temp);
                break;
            }
        }
        incomingBytes.push_back({first, second});
    }

    // for(int i=0;i<25;i++) cout<<incomingBytes[i].first<<" "<<incomingBytes[i].second<<endl;

     vector<vector<char>> a(n, vector<char>(n, '.'));
    for(int i=0;i<3450;i++){
        
        a[incomingBytes[i].second][incomingBytes[i].first]='#';
        // for(int j=0;j<7;j++){
        //     for(int k=0;k<7;k++) cout<<a[i][j];
        //     cout<<endl;
        // }
        vector<vector<bool>>visit(n,vector<bool>(n,false));
        queue<pair<int,pair<int,int>>>q;
        q.push({0, {0, 0}});
        
        visit[0][0] = true;
        bool reach=false;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            int cost = cur.first;
            int r = cur.second.first, c = cur.second.second;

            if (r == 70 && c == 70) {
                // cout<<cost<<endl;
                reach=true;
                break;
            }

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visit[nr][nc] && a[nr][nc] != '#') {
                    visit[nr][nc] = true;
                    q.push({cost + 1, {nr, nc}});
                }
            }
        }
        if(!reach) {cout<<incomingBytes[i].first<<" "<<incomingBytes[i].second<<endl;break;}
    }
   
    
    return 0;
}
