#include <fstream>
#include <vector>
using namespace std;

struct Edges {
    long long len = 0, to = 0;
};

vector<vector<Edges> > graph;

vector<long long> Bellman_Ford(long long n, long long first) {
    vector<long long> d(n, LONG_LONG_MAX);
    d[first] = 0;

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++)
            for (long long k = 0; k < graph[j].size(); k++) {
                long long to = graph[j][k].to;
                long long dist = graph[j][k].len;
                if ((d[j] < LONG_LONG_MAX) && (d[to] > d[j] + dist))
                    d[to] = d[j] + dist;
            }
    }
    return  d;
}

void dfs(long long v, vector<int>& vis) {
    vis[v] = 1;
    for (auto & i : graph[v]) {
        if (!vis[i.to])
            dfs(i.to, vis);
    }
}

int main() {
    ifstream fin("path.in");
    ofstream fout("path.out");

    long long n, m, first, x, y, len;
    fin >> n >> m >> first;
    first--;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> len;
        graph[--x].push_back({len, --y});
    }
    vector<long long> d = Bellman_Ford(n, first);
    vector<int> vis(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            long long to = graph[i][j].to;
            long long dist = graph[i][j].len;
            if ((d[i] < LONG_LONG_MAX) && (d[to] > d[i] + dist) && !vis[to])
                dfs(to, vis);
        }
    }

    for (int i = 0; i < n; i++)
        if (d[i] == LONG_LONG_MAX)
            fout << "*" << endl;
        else if (vis[i] || d[i] < -5e18)
            fout << "-" << endl;
        else
            fout << d[i] << endl;
    return 0;
}