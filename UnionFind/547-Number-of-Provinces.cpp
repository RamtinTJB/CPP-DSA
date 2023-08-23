/*
547. Number of Provinces
There are n cities. Some of them are connected, while some are not. If city 'a'
is connected directly with city 'b', and city 'b' is connected directly with city 'c',
then city 'a' is connected indirectly with city 'c'.

A province is a group of directly or indirectly connected cities and no other cities outside
of the group.

You are given an nxn matrix isConnected where isConnected[i][j] = 1 if the ith
city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.
*/

/*
Approach:
With a small addition, we can store the number of components in the UnionFind data structure.
Initially, the number of components is equal to the number of elements because none of them are connected.
But every time we successfully unite two elements, the number of components decrease by one.
This logic is implemented below. Using this method, after connecting all the cities, we can
just return the number of provinces (connected components) right away.
*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class DisjointSet {
private:
    int provinceCount;
    vector<int> root;
    vector<int> rank;
public:
    DisjointSet(int size) : root(size), rank(size), provinceCount(size) {
        for (size_t i = 0; i < size; i++) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int findRoot(int node) {
        // This implementation uses the Path Compression Optimization
        if (root[node] == node) {
            return node;
        }
        return root[node] = findRoot(root[node]);
    }

    void unionSets(int nodeX, int nodeY) {
        // The root that has a larger height becomes the root of the combined components
        // to avoid lengthening the tree as much as possible
        int rootX = findRoot(nodeX);
        int rootY = findRoot(nodeY);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
            } else if (rank[rootY] > rank[rootX]) {
                root[rootX] = rootY;
            } else {
                root[rootX] = rootY;
                rank[rootY]++;
            }
            // Decrease the number of provinces after every union
            provinceCount--;
        }
    }

    int getProvinceCount() const { return provinceCount; }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        if (isConnected.size() == 0) return 0;
        DisjointSet uf(isConnected.size());
        for (size_t i = 0; i < isConnected.size(); ++i) {
            for (size_t j = 0; j < isConnected.size(); ++j) {
                if (isConnected[i][j] == 1) {
                    uf.unionSets(i, j);
                }
            }
        }

        return uf.getProvinceCount();
    }
};

int main(int argc, const char** argv) {
    // Some sample test cases
    Solution solution;
    vector<vector<int>> v1 {{1,1,0}, {1,1,0}, {0,0,1}};
    vector<vector<int>> v2 {{1,0,0}, {0,1,0}, {0,0,1}};
    vector<vector<int>> v3 {{1,1,1,1}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};

    assert((solution.findCircleNum(v1) == 2));
    assert((solution.findCircleNum(v2) == 3));
    assert((solution.findCircleNum(v3) == 1));

    return 0;
}