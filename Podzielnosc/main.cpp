#include <iostream>

typedef long long ll;

const int MAXN = 100005;
const int P = 1<<17;

int n, q;
ll tree[P * 2];
int psum[MAXN][3];
short chaintype[MAXN][3];
int typetree[P * 2][3];

void insert(int x, int v, short type) {
    x += P - 1;
    tree[x] = v;
    typetree[x][type] = 1;
    while (x > 1) {
        x /= 2;
        tree[x] = tree[2 * x] + tree[2 * x + 1];
        for (int u = 0; u < 3; ++u)
            typetree[x][u] = typetree[2 * x][u] + typetree[2 * x + 1][u];
    }
}

void addtype(ll* types, int* toadd) {
    for (int u = 0; u < 3; ++u) {
        types[u] += (ll)toadd[u];
    }
}
ll query(int a, int b) {
    int pa = a;
    long long types[3] = {0, 0, 0};
    if (b < a)
        return 0;
    a += P - 1;
    b += P - 1;

    ll sum = tree[a];
//    addtype(types, typetree[a]);
    addtype(types, typetree[a]);
    if (a != b) {
        sum += tree[b];
        addtype(types, typetree[b]);
    }
    while (a / 2 < b / 2) {
        if (a % 2 == 0) {
            sum += tree[a + 1];
            addtype(types, typetree[a + 1]);
        }
        if (b % 2 == 1) {
            sum += tree[b - 1];
            addtype(types, typetree[b - 1]);
        }
        a /= 2;
        b /= 2;
    }

    for (int ch1 = 0; ch1 < 3; ++ch1) {
        for (int ch2 = 0; ch2 < 3; ++ch2) {
            if (ch1 == chaintype[pa - 1][ch2]) {
                sum -= (ll)types[ch1] * (ll)psum[pa - 1][ch2];
            }
        }
    }

    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin>>n>>q;

    int temp;
    short type = 0;
    chaintype[0][0] = 0;
    chaintype[0][1] = 1;
    chaintype[0][2] = 2;
    for (int i = 1; i <= n; i++) {
        std::cin>>temp;
        temp %= 3;
        psum[i][temp] = 1;
        for (int u = 0; u < 3; u ++) {
            psum[i][(u + temp) % 3] += psum[i - 1][u];
            chaintype[i][(u + temp) % 3] = chaintype[i - 1][u];
        }
        insert(i, psum[i][0], chaintype[i][0]);
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        ll sum = query(a, b);

        std::cout<< sum <<std::endl;
    }

    return 0;
}