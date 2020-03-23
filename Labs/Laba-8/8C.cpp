#include <fstream>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m, x, y;
    in >> n >> m;
    short matrix[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 0; i < m; i++){
        in >> x >> y;
        if(matrix[x - 1][y - 1] == 1 || matrix[y - 1][x - 1] == 1){
            out << "YES";
            return 0;
        }
        matrix[x - 1][y - 1] = 1;
    }
    out << "NO";
    return 0;
}