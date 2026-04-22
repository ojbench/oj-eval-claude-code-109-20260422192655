#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    // f[i][j]: i and j are directly connected, points [i, j] are in same component
    // g[i][j]: i and j are in same component (connected) via some path in [i, j]
    vector<vector<long long>> f(n, vector<long long>(n, 0));
    vector<vector<long long>> g(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) {
        g[i][i] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;

            // Calculate f[i][j]
            if (a[i][j]) {
                for (int k = i; k < j; ++k) {
                    f[i][j] = (f[i][j] + g[i][k] * g[k + 1][j]) % MOD;
                }
            }

            // Calculate g[i][j]
            for (int k = i + 1; k <= j; ++k) {
                g[i][j] = (g[i][j] + f[i][k] * g[k][j]) % MOD;
            }
        }
    }

    cout << g[0][n - 1] << endl;

    return 0;
}
