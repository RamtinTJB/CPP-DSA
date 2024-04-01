#include <vector>
#include <string>
#include <iostream>

using namespace std;

class DisjointSet {
private:
    vector<int> root;
    vector<int> rank;
public:
    DisjointSet(int size) : root(size), rank(size) {
        for (int i = 0; i < size; ++i) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int find(int node) {
        if (root[node] == node) return node;
        return root[node] = find(root[node]);
    }
};

