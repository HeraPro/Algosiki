#include <fstream>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m, first, second;
    in >> n >> m;
    short matrix[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;

    for (int i = 0; i < m; i++) {
        in >> first >> second;
        matrix[first - 1][second - 1] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            out << matrix[i][j] << " ";
        out << '\n';
    }
    return 0;
}