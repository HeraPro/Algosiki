#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#define INF (LLONG_MAX/2)
using namespace std;

struct Edges {
    long long from, to, len;
};

int main() {
    ifstream in("negcycle.in");
    ofstream out("negcycle.out");
    long long n, value, x;
    in >> n;
    vector<Edges> matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> value;
            if (value != 1000000000)
                matrix.push_back({i, j, value});
        }
    }
    x = -1;
    vector<long long> dist(n, INF), parent(n, -1);
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto & j : matrix) {
            if (dist[j.from] + j.len < dist[j.to]) {
                dist[j.to] = dist[j.from] + j.len;
                parent[j.to] = j.from;
                if (i == n - 1)
                    x = j.to;
            }
        }
    }

    if (x == -1) {
        out << "NO" << endl;
    } else {
        for (int i = 0; i < n; i++)
            x = parent[x];
        vector <int> way;
        way.push_back(x);
        long long cur = parent[x];
        while (cur != x) {
            way.insert(way.begin() + 1, cur);
            cur = parent[cur];
        }
        way.push_back(x);
        out << "YES" << endl;
        out << way.size() << endl;
        for (auto i : way)
            out << i + 1 << ' ';
    }
    return 0;
}

