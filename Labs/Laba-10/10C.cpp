#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Ed {
public:
    int x, y, len;
    bool operator < (Ed &e) {
        return this->len < e.len;
    }
};
int n;
vector<int> p (n);

int dsu_get (int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get (p[v]));
}

int main() {
    ifstream in("spantree3.in");
    ofstream out("spantree3.out");
    int x, y, len, k = 0, m;
    long long cost = 0;
    in >> n >> m;
    vector<Ed> matrix(m);
    vector<int> color(n);
    for (int i = 0; i < m; i++) {
        in >> x >> y >> len;
        x--, y--;
        matrix[i] = {x, y, len};
    }

    sort(matrix.begin(), matrix.end());
    p.resize (n);
    for (int i=0; i<n; ++i)
        p[i] = i;
    for (int i=0; i<m; ++i) {
        int a = matrix[i].x,  b = matrix[i].y,  l = matrix[i].len;
        if (dsu_get(a) != dsu_get(b)) {
            cost += l;
            a = dsu_get (a);
            b = dsu_get (b);
            if (rand() & 1)
                swap (a, b);
            if (a != b)
                p[a] = b;
        }
    }
    out << cost;
    return 0;
}