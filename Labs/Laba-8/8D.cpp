#include <fstream>
#include <vector>
using namespace std;

void Counting(vector<vector<int>>& matrix, int* vertex, int number, int count) {
    for (int i = 0; i < matrix[number].size(); i++) {
        if (vertex[matrix[number][i]] == 0) {
            vertex[matrix[number][i]] = count;
            Counting(matrix, vertex, matrix[number][i], count);
        }
    }
}

int find(vector<int> matrix, int y) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i] == y)
            return i;
    }
    return -1;
}

int main() {
    ifstream in("components.in");
    ofstream out("components.out");
    int n, m, x, y;
    int count = 1;
    in >> n >> m;
    int vertex[n];
    vector<vector<int>> matrix;
    matrix.resize(n);
    for(int i = 0; i < n; i++){
        vertex[i] = 0;
    }
    for(int i = 0; i < m; i++){
        in >> x >> y;
        if (find(matrix[x - 1], y - 1) == -1) {
            matrix[x - 1].push_back(y - 1);
        }
        if (find(matrix[y - 1], x - 1) == -1)
            matrix[y - 1].push_back(x - 1);
    }
	/* привет кравцову */
    for (int i = 0; i < n; i++) {
        while (vertex[i] != 0 && i++ < n);
        if (i >= n)
            break;
        vertex[i] = count;
        Counting(matrix, vertex, i, count);
        count++;
    }
    out << count - 1 << '\n';
    for (int i = 0; i < n; i++)
        out << vertex[i] << ' ';
    return 0;
}