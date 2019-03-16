#include <cstdio>

using namespace std;

using LL = long long;

const int MAXN = 20000;
const int MAXK = 10;
const LL MOD = 1000000000;

int N, K;
int tab[MAXN];
LL dp[MAXN][MAXK];

const int treeSize = 1<<15;
LL treeTab[MAXK][treeSize * 2];

void insert(LL tree[], int key, LL val) {
    int pos = key + treeSize - 1;
    tree[pos] += val;
    while (pos > 1) {
        pos /= 2;
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
    }
}

LL query (LL tree[], int start, int end) {
    LL w = 0;
    int l = start + treeSize - 1, p = end + treeSize - 1;
    w = tree[l] + ( l != p ? tree[p] : 0);

    while (l / 2 < p / 2) {
        if (l % 2 == 0)
            w += tree[l + 1];
        if (p % 2 == 1)
            w += tree[p - 1];
        l /= 2;
        p /= 2;
        w %= MOD;
    }
    return w;
}



int main() {
    scanf ("%d %d", &N, &K);

    for (int i = 0; i < N; i++) {
        scanf ("%d", &tab[i]);
    }

    for (int nx = 1; nx < N; ++nx) {
        dp[nx - 1][0] = 1;
        insert(treeTab[0], tab[nx - 1], 1);
        for (int kx = 1; kx < K; ++kx) {
            dp[nx][kx] = query(treeTab[kx - 1], tab[nx] + 1, N) % MOD;
            if (dp[nx][kx] > 0)
                insert(treeTab[kx], tab[nx], dp[nx][kx]);
        }
    }

    LL sum = 0;
    for (int nx = 1; nx < N; ++nx) {
        sum = (sum + dp[nx][K - 1]) % MOD;
    }

    printf("%lld\n", sum);

    return 0;
}