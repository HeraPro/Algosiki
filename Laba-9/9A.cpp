#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

bool dfs(vector<vector<int>>& matrix, vector<int>& check, int pos, stack<int>& myStack) {
    check[pos] = 1;
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 0)
            if(!dfs(matrix, check, matrix[pos][i], myStack))
                return false;
        if (check[matrix[pos][i]] == 1)
            return false;
    }
    myStack.push(pos);
    check[pos] = 2;
    return true;
}

int main() {
    ifstream in ("topsort.in");
    ofstream out ("topsort.out");
    int n, m, x, y;
    in >> n >> m;
    vector<vector<int>> matrix = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--, y--;
        matrix[x].push_back(y);
    }

    stack<int> ans;
    vector<int> check = vector<int>(n);
    for (int i = 0; i < n; i++)
        check[i] = 0;

    for (int i = 0; i < n; i++) {
        if (check[i] == 0)
            if (!dfs(matrix, check, i, ans)) {
                out << "-1";
                return 0;
            }
    }

    for (int i = 0; i < n; i++) {
        out << ans.top() + 1 << " ";
        ans.pop();
    }
    return 0;
}