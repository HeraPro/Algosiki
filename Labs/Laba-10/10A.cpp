#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n, m, x, y;
    in >> n >> m;
    vector<int> ans = vector<int>(n);
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        x--, y--;
        ans[x]++, ans[y]++;
    }

    for (int i = 0; i < n; i++) {
        out << ans[i] << ' ';
    }
    return 0;
}