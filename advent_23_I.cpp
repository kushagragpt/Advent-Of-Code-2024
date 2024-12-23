#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <string>
#include <sstream>
using namespace std;

// Function to check if a name starts with 't'
bool startsWithT(const string& name) {
    return !name.empty() && name[0] == 't';
}

// Function to find all valid triplets
int findValidTriplets(const vector<pair<string, string>>& connections) {
    // Create an adjacency list
    unordered_map<string, unordered_set<string>> graph;
    for (const auto& connection : connections) {
        graph[connection.first].insert(connection.second);
        graph[connection.second].insert(connection.first);
    }

    // Find all triplets
    set<set<string>> triplets;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        const string& node = it->first;
        const unordered_set<string>& neighbors = it->second;

        for (const auto& neighbor1 : neighbors) {
            for (const auto& neighbor2 : neighbors) {
                if (neighbor1 != neighbor2 && graph[neighbor1].count(neighbor2)) {
                    set<string> triplet = {node, neighbor1, neighbor2};
                    triplets.insert(triplet);
                }
            }
        }
    }

    // Filter triplets containing at least one name starting with 't'
    int count = 0;
    for (const auto& triplet : triplets) {
        for (const auto& name : triplet) {
            if (startsWithT(name)) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main() {
    // Read input connections
    vector<pair<string, string>> connections;
    string line;
    while (getline(cin, line) && !line.empty()) {
        size_t dashPos = line.find('-');
        string node1 = line.substr(0, dashPos);
        string node2 = line.substr(dashPos + 1);
        connections.emplace_back(node1, node2);
    }

    // Find and print the count of valid triplets
    int result = findValidTriplets(connections);
    cout << "Number of valid triplets: " << result << endl;

    return 0;
}
