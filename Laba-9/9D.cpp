#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
vector<int> ord;
vector<int> components;
void dfs1(vector<vector<int>>& matrix, vector<int>& check, int pos) {
    check[pos] = 1;
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 0) {
            dfs1(matrix, check, matrix[pos][i]);
        }
    }
    ord.push_back(pos);
}

void dfs2(vector<vector<int>>& matrix, vector<int>& check, int pos, int comp) {
    components[pos] = comp;
    check[pos] = 1;
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 0) {
            dfs2(matrix, check, matrix[pos][i], comp);
        }
    }
}

int main() {
    ifstream in ("cond.in");
    ofstream out ("cond.out");
    int n, m, x, y;
    in >> n >> m;
    vector<vector<int>> matrixG = vector<vector<int>>(n);
    vector<vector<int>> matrixH = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--, y--;
        matrixG[x].push_back(y);
        matrixH[y].push_back(x);
    }

    vector<int> check = vector<int>(n);
    components.resize(n);
    for (int i = 0; i < n; i++) {
        check[i] = 0;
        components[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (check[i] == 0) {
            dfs1(matrixG, check, i);
        }
    }

    for (int i = 0; i < n; i++)
        check[i] = 0;
    int comp = 1;
    for (int i = 0; i < ord.size(); i++) {
        if (components[ord[ord.size() - i - 1]] == 0) {
            dfs2(matrixH, check, ord[ord.size() - i - 1], comp);
            comp++;
        }
    }
    out << --comp << '\n';
    for (int i = 0; i < n; i++)
        out << components[i] << ' ';
    return 0;
}