#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector <long long>> matrix;

vector<long long> dikstra(long long n, long long fir) {
    vector<long long> dist(n, LONG_LONG_MAX);
    vector <bool> vis(n);
    dist[fir] = 0;
    for (long long i = 0; i < n; i++) {
        long long vertex = -1;
        for (long long j = 0; j < n; j++)
            if (!vis[j] && (vertex == -1 || dist[j] < dist[vertex]))
                vertex = j;
        if (dist[vertex] == LONG_LONG_MAX)
            break;
        vis[vertex] = true;
        for (long long j = 0; j < n; j++)
            if (matrix[vertex][j] != LONG_LONG_MAX)
                dist[j] = dist[j] > (dist[vertex] + matrix[vertex][j])? (dist[vertex] + matrix[vertex][j]) : dist[j];
    }
    return dist;
}

int main() {
    ifstream in("pathmgep.in");
    ofstream out("pathmgep.out");
    long long n, fir, sec, x;
    in >> n >> fir >> sec;
    fir--, sec--;

    matrix.resize(n, vector<long long>(n, LONG_LONG_MAX));
    for (long long i = 0; i < n; i++) {
        matrix[i].resize(n);
        for (long long j = 0; j < n; j++) {
            in >> x;
            matrix[i][j] = x < 0? LONG_LONG_MAX : x;
        }
    }

    vector<long long> dist = dikstra(n, fir);
    if (dist[sec] >= LONG_LONG_MAX)
        out << -1;
    else
        out << dist[sec];
    return 0;
}