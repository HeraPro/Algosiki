#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

void dfs2(vector<vector<int>>& matrix, vector<int>& check, int pos, stack<int>& myStack);
void dfs1(vector<vector<int>>& matrix, vector<int>& check, int pos, stack<int>& myStack) {
    if (matrix.empty()) {
        check[pos] = 2;
        return;
    }
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 2) {
            check[pos] = 1;
            return;
        }
        if (check[matrix[pos][i]] == 0)
            dfs2(matrix, check, matrix[pos][i], myStack);
        if (check[matrix[pos][i]] == 1) {
            check[pos] = 1;
            return;
        }
    }
    check[pos] = 2;
}

void dfs2(vector<vector<int>>& matrix, vector<int>& check, int pos, stack<int>& myStack) {
    if (matrix.empty()) {
        check[pos] = 1;
        return;
    }
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 1) {
            check[pos] = 2;
            return;
        }
        if (check[matrix[pos][i]] == 0)
            dfs1(matrix, check, matrix[pos][i], myStack);
        if (check[matrix[pos][i]] == 2) {
            check[pos] = 2;
            return;
        }
    }
    check[pos] = 1;
}

int main() {
    ifstream in("game.in");
    ofstream out("game.out");
    int n, m, start, x, y;
    in >> n >> m >> start;
    start--;
    vector<vector<int>> matrix(n);
    vector<int> check(n);
    for (int i = 0; i < n; i++)
        check[i] = 0;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--, y--;
        matrix[x].push_back(y);
    }
    stack<int> myStack;
    dfs1(matrix, check, start, myStack);
    if (check[start] % 2 != 0)
        out << "First player wins";
    else
        out << "Second player wins";
    return 0;
}