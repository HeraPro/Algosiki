#include <fstream>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    in >> n;
    short matrix[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            in >> matrix[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == 1) {
                if (matrix[j][i] != 1 || i == j) {
                    out << "NO";
                    return 0;
                }
            }
    out << "YES";
    return 0;
}