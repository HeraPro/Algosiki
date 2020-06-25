#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector <long long>> matrix;

int main() {
    ifstream in("pathsg.in");
    ofstream out("pathsg.out");
    long long n, m, x, y, len;
    in >> n >> m;

    matrix.resize(n, vector<long long>(n, INT_MAX));
    for (long long j = 0; j < m; j++) {
        in >> x >> y >> len;
        matrix[--x][--y] = len;
    }
    for (int i = 0; i < n; i++) {
        matrix[i][i] = 0;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j =0 ; j < n ; j++)
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            out << matrix[i][j] << ' ';
        out << '\n';
    }
    return 0;
}