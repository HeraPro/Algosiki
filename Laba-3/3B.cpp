#include <fstream>
using namespace std;
int n;
double h[100000];
/*
 * h[i] = (h[i - 1] + h[i + 1]) / 2 - 1
 * 2 * h[i] = h[i - 1] + h[i + 1] - 2
 * h[i + 1] = 2 * h[i] - h[i - 1] + 2
 */
double garland() {
    double left = h[0], right = 0;
    while (left - right > 0.000001) {
        h[1] = (left + right) / 2;
        bool down = true;
        for (int i = 2; i < n; i++) {
            h[i] = 2 * h[i - 1] - h[i - 2] + 2;
            if (h[i] < 0) {
                down = false;
                break;
            }
        }
        if (down)
            left = h[1];
        else
            right = h[1];
    }
    return h[n - 1];
}
 
int main() {
    ifstream fin("garland.in");
    ofstream fout("garland.out");
    fin >> n;
    fin >> h[0];
    fout << fixed;
    fout.precision(2);
    fout << garland() << endl;
    return 0;
}