#include <cstdio>
#include <algorithm>

using namespace std;
using LL = long long;

const int MAXN = 40000;
const int MAXK = 50;

LL w[MAXN];



int n, k;



int main() {

    scanf ("%d %d", &n, &k);

    LL pw = 1;

    for (int ik = 0; ik < k; ++ik) {
        LL id;
        for (int in = 0; in < n; ++in) {
            scanf("%lld", &id);
            if (in >= n / 2)
                w[id - 1] += pw;

        }
        pw = pw << 1;
    }

    sort(w, w + n);

    for (int i = 0; i < n - 1; ++i) {
        if (w[i] == w[i + 1]) {
            printf("NIE\n");
            return 0;
        }

    }
    printf("TAK\n");
    return 0;
}