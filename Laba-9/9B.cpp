#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> dfs(vector<vector<int>>& matrix, vector<int>& check, int pos) {
    check[pos] = 1;
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 0) {
            vector<int> ans = dfs(matrix, check, matrix[pos][i]);
            if (!ans.empty()) {
                if (ans.front() != ans.back() || ans.size() == 1) {
                    ans.push_back(pos);
                    return  ans;
                } else
                    return ans;
            }
        }
        if (check[matrix[pos][i]] == 1)
            return {matrix[pos][i], pos};
    }
    check[pos] = 2;
    return {};
}

int main() {
    ifstream in ("cycle.in");
    ofstream out ("cycle.out");
    int n, m, x, y;
    in >> n >> m;
    vector<vector<int>> matrix = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--, y--;
        matrix[x].push_back(y);
    }

    vector<int> check = vector<int>(n);
    for (int i = 0; i < n; i++)
        check[i] = 0;

    for (int i = 0; i < n; i++) {
        if (check[i] == 0) {
            vector<int> ans = dfs(matrix, check, i);
            if (!ans.empty()) {
                out << "YES\n";
                for (int j = 1; j < ans.size(); j++) {
                    out << ans[ans.size() - j] + 1 << ' ';
                }
                return 0;
            }
        }
    }
    out << "NO";
    return 0;
}