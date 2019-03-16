#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 100000;
const int MAXM = 500000;

int N, M, K;
int price[MAXN];
vector<vector<int> > conn;
int req[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin >> N >> M >> K;

    for (int i = 0; i < N; ++i) {
        cin >> price[i];
    }

    conn.resize(N);

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        conn[b].push_back(a);
        req[a]++;
    }

    priority_queue<pair<int, int> > q;
    for (int i = 0; i < N; ++i) {
        if (req[i] == 0)
           q.push({-price[i], i});
    }
    int found = 0;
    int minprice = 0;
    int actual;
    while (found < K) {

        minprice = max(minprice, -q.top().first);
        actual = q.top().second;
        found++;
        q.pop();

        for (auto &rel: conn[actual]) {
            req[rel]--;
            if (req[rel] == 0) {
                q.push({-price[rel], rel});
            }
        }

    }
    cout<<minprice<<endl;
    return 0;
}