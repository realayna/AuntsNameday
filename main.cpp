#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class NamesdayParty {
public:
    unordered_map<string, int> setSittingScheme(const unordered_map<string, vector<string>>& graph) {
        unordered_map<string, int> seatingArrangement;
        unordered_set<string> visited;

        int table = 1;
        for (const auto& entry : graph) {
            const string& guest = entry.first;
            if (visited.find(guest) == visited.end()) {
                dfs(graph, guest, seatingArrangement, visited, table);
                table++;
            }
        }

        return seatingArrangement;
    }

private:
    void dfs(const unordered_map<string, vector<string>>& graph, const string& guest, unordered_map<string, int>& seatingArrangement, unordered_set<string>& visited, int table) {
        visited.insert(guest);
        seatingArrangement[guest] = table;

        for (const auto& neighbor : graph.at(guest)) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(graph, neighbor, seatingArrangement, visited, table);
            }
        }
    }
};

int main() {
    unordered_map<string, vector<string>> graph;

    // Add the invited guests and their animosities to the graph
    graph["Aunt Petunia"] = { "John", "Mary" };
    graph["John"] = { "Aunt Petunia", "Mary" };
    graph["Mary"] = { "Aunt Petunia", "John" };

    NamesdayParty party;
    unordered_map<string, int> seatingArrangement = party.setSittingScheme(graph);

    // Print the seating arrangement
    for (const auto& entry : seatingArrangement) {
        cout << entry.first << " - Table " << entry.second << endl;
    }

    return 0;
}
