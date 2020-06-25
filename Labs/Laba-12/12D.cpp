#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    long long to, maxFlow, flow;
};
vector<vector<long long>> ans, matrix;
vector<Edge> edges;
vector<long long> ptr, level;
long long sr = 0, s = 0;

bool bfs(long long n) {
    level.assign(n, 0);
    queue<int> q;
    q.push(sr);
    level[sr] = 1;
    while (!q.empty() && !level[s]) {
        long long from = q.front();
        q.pop();
        for (auto& edge : matrix[from]) {
            if (!level[edges[edge].to] && edges[edge].maxFlow > edges[edge].flow) {
                q.push(edges[edge].to);
                level[edges[edge].to] = level[from] + 1;
            }
        }
    }
    return level[s];
}

long long dfs(long long vertex = sr, long long flow = LONG_LONG_MAX) {
    if (!flow)
        return 0;
    if (vertex == s)
        return flow;
    while (ptr[vertex] < matrix[vertex].size()) {
        long long edge = matrix[vertex][ptr[vertex]];
        if (level[vertex] + 1 == level[edges[edge].to]) {
            long long pushed = dfs(edges[edge].to, min(flow, edges[edge].maxFlow - edges[edge].flow));
            if (pushed) {
                edges[edge].flow += pushed;
                edges[edge ^ 1].flow -= pushed;
                return pushed;
            }
        }
        ptr[vertex]++;
    }
    return 0;
}

int main() {
    ifstream in("circulation.in");
    ofstream out("circulation.out");
    long long n, m, x, y, minLen, maxLen;
    in >> n >> m;
    n += 2;
    matrix.resize(n), ptr.resize(n);
    s = n - 1;
    for (int i = 0; i < m; i++) {
        in >> x >> y >> minLen >> maxLen;

        matrix[sr].push_back(edges.size());
        edges.emplace_back(Edge{y, minLen, 0});
        matrix[y].push_back(edges.size());
        edges.emplace_back(Edge{sr, 0, 0});

        matrix[x].push_back(edges.size());
        edges.emplace_back(Edge{y, maxLen - minLen, 0});
        matrix[y].push_back(edges.size());
        edges.emplace_back(Edge{x, 0, 0});

        matrix[x].push_back(edges.size());
        edges.emplace_back(Edge{s, minLen, 0});
        matrix[s].push_back(edges.size());
        edges.emplace_back(Edge{x, 0, 0});

    }
    while (bfs(n)) {
        while (dfs());
        ptr.assign(n, 0);
    }

    for (int edge : matrix[0]) {
        if (edges[edge].flow < edges[edge].maxFlow) {
            out << "NO\n";
            return 0;
        }
    }
    out << "YES\n";
    for (int i = 0; i < edges.size(); i += 6)
        out << edges[i + 2].flow + edges[i + 4].flow << endl;
    return 0;
}