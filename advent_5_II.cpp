#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

// Function to split a string by a delimiter
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to check if an update is in the correct order
bool isCorrectOrder(const vector<int> &update, const unordered_map<int, unordered_set<int>> &rules) {
    unordered_map<int, int> position;
    for (size_t i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }

    for (unordered_map<int, unordered_set<int>>::const_iterator it = rules.begin(); it != rules.end(); ++it) {
        int page = it->first;
        const unordered_set<int> &afterPages = it->second;
        if (position.find(page) != position.end()) {
            for (unordered_set<int>::const_iterator afterPageIt = afterPages.begin(); afterPageIt != afterPages.end(); ++afterPageIt) {
                int afterPage = *afterPageIt;
                if (position.find(afterPage) != position.end() && position[page] > position[afterPage]) {
                    return false;
                }
            }
        }
    }

    return true;
}

// Function to sort an update based on the rules
vector<int> sortUpdate(const vector<int> &update, const unordered_map<int, unordered_set<int>> &rules) {
    unordered_map<int, int> inDegree;
    unordered_map<int, vector<int>> graph;
    vector<int> sortedUpdate;

    // Initialize in-degrees and graph for pages in the update
    for (size_t i = 0; i < update.size(); ++i) {
        inDegree[update[i]] = 0;
        graph[update[i]] = {};
    }

    // Build the graph and calculate in-degrees
    for (unordered_map<int, unordered_set<int>>::const_iterator it = rules.begin(); it != rules.end(); ++it) {
        int page = it->first;
        const unordered_set<int> &afterPages = it->second;
        if (inDegree.find(page) != inDegree.end()) {
            for (unordered_set<int>::const_iterator afterPageIt = afterPages.begin(); afterPageIt != afterPages.end(); ++afterPageIt) {
                int afterPage = *afterPageIt;
                if (inDegree.find(afterPage) != inDegree.end()) {
                    graph[page].push_back(afterPage);
                    inDegree[afterPage]++;
                }
            }
        }
    }

    // Perform topological sort
    queue<int> q;
    for (unordered_map<int, int>::const_iterator it = inDegree.begin(); it != inDegree.end(); ++it) {
        if (it->second == 0) {
            q.push(it->first);
        }
    }

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        sortedUpdate.push_back(current);

        for (size_t i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return sortedUpdate;
}

int main() {
    string line;
    unordered_map<int, unordered_set<int>> rules;
    vector<vector<int>> updates;

    // Read rules
    while (getline(cin, line) && !line.empty()) {
        vector<string> parts = split(line, '|');
        int x = stoi(parts[0]);
        int y = stoi(parts[1]);
        // cout<<x<<" "<<y<<endl;
        rules[x].insert(y);
    }

    // Read updates
    while (getline(cin, line) && !line.empty()) {
        vector<int> update;
        vector<string> pages = split(line, ',');
        for (size_t i = 0; i < pages.size(); ++i) {
            update.push_back(stoi(pages[i]));
        }
        updates.push_back(update);
    }

    int sumOfMiddlePages = 0;

    for (size_t i = 0; i < updates.size(); ++i) {
        const vector<int> &update = updates[i];
        if (!isCorrectOrder(update, rules)) {
            vector<int> sortedUpdate = sortUpdate(update, rules);
            int middleIndex = sortedUpdate.size() / 2;
            for(int j=0;j<sortedUpdate.size();j++){
                cout<<sortedUpdate[j]<<" ";
            }
            cout<<endl;
            sumOfMiddlePages += sortedUpdate[middleIndex];
        }
    }

    cout << "Sum of middle page numbers: " << sumOfMiddlePages << endl;

    return 0;
}
