#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
struct Flow {
    long long to = 0, flow = 0, len = 0;
    unsigned long long backflow = 0;
};

long long n, iteration = 0;
vector<long long> visited;
vector<vector <Flow>> graph;

long long Ford(long long u, long long Cmin) {
    if (u == n - 1)
        return Cmin;
    visited[u] = iteration;
    for (auto & v : graph[u]) {
        if (visited[v.to] != iteration && v.flow < v.len) {
            long long delta = Ford(v.to, min(Cmin, v.len - v.flow));
            if (delta > 0) {
                v.flow += delta;
                graph[v.to][v.backflow].flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}
int main() {
    ifstream in("maxflow.in");
    ofstream out("maxflow.out");
    ios_base::sync_with_stdio(false);
    in.tie(nullptr);
    long long m, x, y, len;
    in >> n >> m;
    graph.resize(n);
    for (int i = 0; i < m; i++){
        in >> x >> y >> len;
        x--, y--;
        graph[x].push_back({y , 0, len});
        graph[y].push_back({x, len, len});
        graph[x].back().backflow = graph[y].size() - 1;
        graph[y].back().backflow = graph[x].size() - 1;
    }
    visited.resize(n);
    long long ans = 0, res;
    while(true) {
        iteration++;
        res = Ford(0, LONG_LONG_MAX);
        if (res > 0)
            ans += res;
        else
            break;
    }
    out << ans;
    return 0;
}