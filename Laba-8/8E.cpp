#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int find(vector<short> matrix, int y) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i] == y)
            return i;
    }
    return -1;
}

int main() {
    ifstream in("pathbge1.in");
    ofstream out("pathbge1.out");
    int n, m, x, y;
    short count = 1;
    in >> n >> m;
    short vertex[n];
    vector<vector<short>> matrix;
    matrix.resize(n);
    for(int i = 0; i < n; i++){
        vertex[i] = (short)n;
    }
    for(int i = 0; i < m; i++){
        in >> x >> y;
        if (find(matrix[x - 1], y - 1) == -1) {
            matrix[x - 1].push_back(y - 1);
        }
        if (find(matrix[y - 1], x - 1) == -1)
            matrix[y - 1].push_back(x - 1);
    }
    queue<short> A;
    A.push(0);
    vertex[0] = 0;
    while (!A.empty()) {
        short b = A.front();
        for (int i = 0; i < matrix[b].size(); i++) {
            if (vertex[matrix[b][i]] == n) {
                int element = matrix[b][i];
                A.push(element);
                vertex[element] = vertex[b] - 1;
                int position = find(matrix[element], b);
                matrix[element].erase(matrix[element].begin() + position, matrix[element].begin() + position + 1);
            }
        }
        A.pop();
    }
    for (int i = 0; i < n; i++)
        out << vertex[n - i - 1] << ' ';
    return 0;
}