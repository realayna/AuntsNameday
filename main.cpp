#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<string, unordered_set<string>> dislikes;

bool isSafeToSit(const string& person, const vector<string>& table) {
    for (const string& guest : table) {
        if (dislikes[person].count(guest))
            return false;
    }
    return true;
}

bool dfs(vector<string>& guests, vector<vector<string>>& tables) {
    if (guests.empty()) {
        return true;  // All guests have been seated
    }

    const string person = guests.back();
    guests.pop_back();

    for (auto& table : tables) {
        if (isSafeToSit(person, table)) {
            table.push_back(person);

            if (dfs(guests, tables)) {
                return true;  // Guests have been successfully seated
            }

            table.pop_back();  // Backtrack if arrangement failed
        }
    }

    guests.push_back(person);  // Put the person back in the guests list
    return false;  // Unable to arrange guests at the tables
}

bool arrangeTables(vector<string>& guests, vector<vector<string>>& tables) {
    return dfs(guests, tables);
}

void printSittingArrangement(const vector<vector<string>>& tables) {
    cout << "Sitting Arrangement:\n";
    for (size_t i = 0; i < tables.size(); i++) {
        cout << "Table " << (i + 1) << ": ";
        for (const string& guest : tables[i]) {
            cout << guest << " ";
        }
        cout << endl;
    }
}

int main() {
    // List of invited guests
    vector<string> guests = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank"};

    // Aunt's suggestions on who doesn't like whom
    dislikes["Alice"] = {"Charlie"};
    dislikes["Bob"] = {"Eve"};
    dislikes["Charlie"] = {"Alice", "David"};
    dislikes["David"] = {"Charlie", "Frank"};
    dislikes["Eve"] = {"Bob"};
    dislikes["Frank"] = {"David"};

    // Number of tables
    int numTables = 2;

    // Initialize tables
    vector<vector<string>> tables(numTables);

    // Arrange the sitting scheme
    bool success = arrangeTables(guests, tables);

    if (success) {
        printSittingArrangement(tables);
    } else {
        cout << "Unable to arrange sitting." << endl;
    }

    return 0;
}
