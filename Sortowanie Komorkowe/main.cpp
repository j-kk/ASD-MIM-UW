#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

using LL = long long;


const LL MOD = 1000000000;
const int tabsize = 1000;
int n;
int tab[tabsize];
LL dp[tabsize][tabsize][2];

LL f (int i, int j, int k) {
    if (dp[i][j][k] == -1 and i != j) {
        dp[i][j][0] = dp[i][j][1] = 0;

        if (tab[i] < tab[i + 1])
            dp[i][j][0] += f(i + 1, j, 0);

        if (tab[i] < tab[j])
            dp[i][j][0] += f(i + 1, j, 1);

        if (tab[j] > tab[j - 1])
            dp[i][j][1] += f(i, j - 1, 1);

        if (tab[j] > tab[i])
            dp[i][j][1] += f(i, j - 1, 0);

        dp[i][j][0] %= MOD;
        dp[i][j][1] %= MOD;
    }
    return dp[i][j][k];
}


int main() {
    scanf ("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf ("%d", &tab[i]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j][0] = (i == j ? 1 : -1);
            dp[i][j][1] = (i == j ? 0 : -1);
        }
    }

    printf ("%lld", (f(0, n - 1, 0) + f(0, n - 1, 1)) % MOD);

    return 0;
}