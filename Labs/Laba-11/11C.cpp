#include <fstream>
#include <vector>
#include <set>
using namespace std;

struct E {
    long long len = 0, to = 0;

    bool operator<(const E &a) const {
        if (this->len < a.len)
            return true;
        return this->len == a.len && this->to < a.to;
    }

};
vector<vector<E>> matrix;

vector<long long> dikstra(long long n) {
    vector<long long> d(n, LONG_MAX);
    d[0] = 0;
    set < E > q;
    q.insert ({0, 0});
    while (!q.empty()) {
        E u = *q.begin();
        q.erase(q.begin());
        for (auto& e : matrix[u.to]) {
            if (d[u.to] + e.len < d[e.to]) {
                q.erase({d[e.to], e.to});
                d[e.to] = d[u.to] + e.len;
                q.emplace(E{d[e.to], e.to});
            }
        }
    }
    return d;
}




int main() {
    ifstream in("pathbgep.in");
    ofstream out("pathbgep.out");
    long long n, m, x, y, len;
    in >> n >> m;
    matrix.resize(n);
    for (long long j = 0; j < m; j++) {
        in >> x >> y >> len;
        x--, y--;
        matrix[x].push_back({len, y});
        matrix[y].push_back({len, x});
    }

    vector<long long> dist = dikstra(n);
    for (auto i : dist)
        out << i << ' ';
    return 0;
}