#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> matrix;
vector<int> visited, px, py;
bool dfs(int v) {
    if (visited[v])
        return false;
    visited[v] = true;
    for (int y = 0; y < matrix[v].size(); y++) {
        if (matrix[v][y] == 1) {
            if (py[y] == -1) {
                py[y] = v;
                px[v] = y;
                return true;
            } else {
                if (dfs(py[y])) {
                    py[y] = v;
                    px[v] = y;
                    return true;
                }
            }
        }
    }
    return false;
}

/*func fordFulkerson():
    fill(px, -1)
    fill(py, -1)
    isPath = true
    while isPath
        isPath = false
        fill(vis, false)
        for x∈L
            if px[x] == -1
                if dfs(x)
                    isPath = true*/

void Ford(int n1, int n2) {
    px.resize(n1, -1);
    py.resize(n2, -1);
    bool isPath = true;
    while (isPath) {
        isPath = false;
        visited = vector<int>(n1, 0);
        for (int i = 0; i < n1; i++) {
            if (px[i] == -1)
                if (dfs(i))
                    isPath = true;
        }
    }
}

int main() {
    ifstream in("matching.in");
    ofstream out("matching.out");
    ios_base::sync_with_stdio(false);
    in.tie(nullptr);
    int n1, n2, m, x, y;
    in >> n1 >> n2 >> m;
    matrix.resize(n1, vector<int>(n2));
    for (int i = 0; i < m; i++){
        in >> x >> y;
        x--, y--;
        matrix[x][y] = 1;
    }

    Ford(n1, n2);

    int ans = 0;

    for (auto i : px) {
        if (i != -1)
            ans++;
    }
    out << ans;
    return 0;
}