#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct entry {
    string name;
    int dist;
};

map<string, int> build_relation_tree(map<string, vector<string> > database) {
    map<string, int> answer;
    
    set<string> visited;
    queue<entry> queue;
    
    entry current;
    current.name = "Erdos, P.";
    current.dist = 0;
    
    queue.push(current);
    
    while (!queue.empty()) {
        current = queue.front();
        if (visited.count(current.name) == 0) {
            answer[current.name] = current.dist;
            visited.insert(current.name);
            for (int i = 0; i < database[current.name].size(); i++) {
                entry next;
                next.name = database[current.name][i];
                next.dist = current.dist + 1;
                queue.push(next);
            }
        }
        queue.pop();
    }
    
    return answer;
}

int main() {
    int t;
    int p, n;
    string line;
    string name;
    
    string author;
    string coauthor;
    
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> p >> n;
        getline(cin, line);
        map<string, vector<string> > database;

        for (int j = 0; j < p; j++) {
            vector<string> authors;
            name = "";
            getline(cin, line);
            for (int k = 0; k < line.length(); k++) {
                if ((line[k] == ',' || line[k] == ':') && line[k-1] == '.') {
                    authors.push_back(name);
                    name = "";
                    k++;
                } else {
                    name += line[k];
                }
            }
            for (int k = 0; k < authors.size(); k++) {
                author = authors[k];
                if (database.count(author) == 0) {
                    database[author] = vector<string>();
                }
                for (int l = 0; l < authors.size(); l++) {
                    coauthor = authors[l];
                    if (author != coauthor) {
                        database[author].push_back(coauthor);
                    }
                }
            }
        }
        
        map<string, int> erdos = build_relation_tree(database);
        /*
        for (map<string, int>::iterator it = erdos.begin(); it != erdos.end(); ++it) {
            cout << it->first << " -> " << it->second << endl;
        }
        */
        cout << "Scenario " << (i+1) << endl;
        for (int j = 0; j < n; j++) {
            getline(cin, name);
            cout << name << " ";
            if (erdos.count(name) > 0) {
                cout << erdos[name];
            } else {
                cout << "infinity";
            }
            cout << endl;
        }
    }
    
    return 0;
}
