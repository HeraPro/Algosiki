#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Ed {
public:
    int x, y, len;
};

bool check(const vector<vector<int>>& matrix, int root) {
    queue<int> Q;
    vector<int> check(matrix.size(), 0);
    check[root] = 1;
    Q.push(root);
    while (!Q.empty()) {
        int b = Q.front();
        for (int i : matrix[b])
            if (check[i] == 0) {
                check[i] = 1;
                Q.push(i);
            }
        Q.pop();
    }
    for (int i : check) {
        if (i == 0)
            return false;
    }
    return true;
}

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


int Condensation(int n, vector<Ed>& edges) {
    vector<vector<int>> matrixG(n);
    vector<vector<int>> matrixH(n);
    for (auto e : edges) {
        matrixG[e.x].push_back(e.y);
        matrixH[e.y].push_back(e.x);
    }

    vector<int> check = vector<int>(n);
    components.resize(n);
    for (int i = 0; i < n; i++) {
        check[i] = 0;
        components[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (check[i] == 0) {
            dfs1(matrixG, check, i);
        }
    }

    for (int i = 0; i < n; i++)
        check[i] = 0;
    int comp = 0;
    for (int i = 0; i < ord.size(); i++) {
        if (components[ord[ord.size()-i-1]] == -1) {
            dfs2(matrixH, check, ord[ord.size()-i-1], comp++);
        }
    }

    return comp;
}

long long findMST(int n, const vector<Ed>& edges, int root, const vector<vector<int>>& matrix) {
    long long res = 0;
    vector<int> minEdges(n, INT_MAX);
    for (auto e : edges)
        minEdges[e.y] = e.len < minEdges[e.y]? e.len: minEdges[e.y];

    for (int v = 0; v < n; v++)
        if (v != root)
            res += minEdges[v];

    vector<Ed> zeroEdges;
    vector<vector<int>> zeroMatrix(n);

    for (auto e: edges) {
        if (e.len == minEdges[e.y]) {
            zeroEdges.push_back({e.x, e.y, 0});
            zeroMatrix[e.x].push_back(e.y);
        }
    }

    if (check(zeroMatrix, root))
        return res;
    int compc = Condensation(n, zeroEdges);
    vector<int> comp = components;
    vector<Ed> newEd;
    vector<vector<int>> newMat(compc);
    for (auto e : edges) {
        if (comp[e.x] != comp[e.y]) {
            newEd.push_back({comp[e.x], comp[e.y], e.len - minEdges[e.y]});
            newMat[comp[e.x]].push_back(comp[e.y]);
        }
    }
    res += findMST(compc, newEd, comp[root], newMat);
    return res;
}

int main() {
    ifstream in("chinese.in");
    ofstream out("chinese.out");
    int n, x, y, len, m;
    in >> n >> m;
    vector<Ed> matrixLen(m);
    vector<vector<int>> matrix(n);
    vector<int> color(n);
    for (int i = 0; i < m; i++) {
        in >> x >> y >> len;
        x--, y--;
        matrix[x].push_back(y);
        matrixLen[i] = {x, y, len};
    }
    if (!check(matrix, 0)) {
        out << "NO";
        return 0;
    }
    out << "YES\n" << findMST(n, matrixLen, 0, matrix);
    return 0;
}