#include <fstream>
#include <stack>
#include <vector>

using namespace std;

bool dfs(vector<vector<int>>& matrix, vector<int>& check, int pos, stack<int>& myStack) {
    check[pos] = 1;
    for (int i = 0; i < matrix[pos].size(); i++) {
        if (check[matrix[pos][i]] == 0)
            if(!dfs(matrix, check, matrix[pos][i], myStack))
                return false;
        if (check[matrix[pos][i]] == 1)
            return false;
    }
    myStack.push(pos);
    check[pos] = 2;
    return true;
}

int main()
{

    ifstream in ("hamiltonian.in");
    ofstream out ("hamiltonian.out");
    int n, m, x, y;
    in >> n >> m;

    vector<vector<int>> matrix(n);

    for (int i = 0; i < m; i++)
    {
        in >> x >> y;
        x--, y--;
        matrix[x].push_back(y);
    }

    vector<int> color(n);

    for (int i = 0; i < n; i++)
        color[i] = 0;
    stack<int> sort;

    for (int i = 0; i < n; i++)
        if (color[i] == 0)
            dfs(matrix, color, i, sort);

    bool flag = true;

    while ((sort.size() > 1) && (flag)) {
        x = sort.top();
        sort.pop();
        flag = false;

        for (int i : matrix[x])
            if (i == sort.top())
                flag = true;
    }

    if (flag)
        out << "YES";
    else
        out << "NO";

    return 0;
}