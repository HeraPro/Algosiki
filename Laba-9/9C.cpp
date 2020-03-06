#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int dfs2(vector<vector<int>>& matrix, vector<int>& check, int pos);
int dfs1(vector<vector<int>>& matrix, vector<int>& check, int pos) {
    check[pos] = 1;
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 0) {
            int ans = dfs2(matrix, check, matrix[pos][i]);
            if (ans == 1) {
                return 1;
            }
        } else if (check[matrix[pos][i]] == 1)
            return 1;
    }
    return 0;
}

int dfs2(vector<vector<int>>& matrix, vector<int>& check, int pos) {
    check[pos] = 2;
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 0) {
            int ans = dfs1(matrix, check, matrix[pos][i]);
            if (ans == 1) {
                return 1;
            }
        } else if (check[matrix[pos][i]] == 2)
            return 1;
    }
    return 0;
}

int main() {
    ifstream in ("bipartite.in");
    ofstream out ("bipartite.out");
    int n, m, x, y;
    in >> n >> m;
    vector<vector<int>> matrix = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--, y--;
        matrix[x].push_back(y);
        matrix[y].push_back(x);
    }

    vector<int> check = vector<int>(n);
    for (int i = 0; i < n; i++)
        check[i] = 0;

    for (int i = 0; i < n; i++) {
        if (check[i] == 0) {
            int ans = dfs1(matrix, check, i);
            if (ans == 1) {
                out << "NO";
                return 0;
            }
        }
    }
    out << "YES";
    return 0;
}