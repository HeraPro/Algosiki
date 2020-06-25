#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
	long long to, maxFlow, flow, num;
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

long long decomposition(long long vertex, long long minFlow = LONG_LONG_MAX) {
	if (vertex == s) {
		ans.emplace_back();
		return minFlow;
	}
	for (int edge : matrix[vertex]) {
		if (edges[edge].flow > 0) {
            long long result = decomposition(edges[edge].to, min(minFlow, edges[edge].flow));
			if (result) {
				ans.back().push_back(edges[edge].num);
				if (vertex == sr) {
					ans.back().push_back(ans[ans.size() - 1].size());
					ans.back().push_back(result);
					reverse(ans.back().begin(), ans.back().end());
				}
				edges[edge].flow -= result;
				return result;
			}
		}
	}
	return 0;
}

int main() {
	ifstream in("decomposition.in");
	ofstream out("decomposition.out");
    long long n, m, x, y, len;
	in >> n >> m;
	matrix.resize(n), ptr.resize(n);
	for (int i = 0; i < m; i++) {
		in >> x >> y >> len;
		x--, y--;
		matrix[x].push_back(edges.size());
		edges.emplace_back(Edge{ y, len, 0, i + 1});
		matrix[y].push_back(edges.size());
		edges.emplace_back(Edge{ x, 0, 0, i + 1});
	}
    s = n - 1;
	while (bfs(n)) {
		while (dfs());
		ptr.assign(n, 0);
	}
	while (decomposition(sr));
	out << ans.size() << "\n";
	for (auto& i : ans) {
		for (auto& j : i)
			out << j << ' ';
		out << '\n';
	}
	return 0;
}