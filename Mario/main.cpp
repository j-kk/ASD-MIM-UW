#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int DIM = 17;
const int MAXN = 100001;
const int MAXINT = 2147483647;

int w[MAXN][DIM + 1];
int pow2[DIM + 1] = {1};
int n, K, U;
string plansza;


inline int power2(int p) {
    return pow2[p];
}


int main() {

    cin >> n >> K >> U;
    cin >> plansza;

    for (int i = 1; i <= DIM; ++i) {
        pow2[i] = pow2[i - 1] * 2;
    }

    for (int x = 0; x < MAXN; ++x) {
        for (int d = 1; d <= DIM; ++d) {
            w[x][d] = MAXINT;
        }
    }

    priority_queue<pair<int, pair<int, int>>> toVisit;


    toVisit.push(make_pair(0, make_pair(1, 1)));
    w[1][1] = 0;

    while (!toVisit.empty()) {
        pair<int, int> actual = toVisit.top().second;
        toVisit.pop();

        switch (plansza[actual.first - 1]) {
            case '.':
                if (w[actual.first][actual.second] + 1 < w[actual.first + 1][actual.second] && actual.first < n) {
                    w[actual.first + 1][actual.second] = w[actual.first][actual.second] + 1;
                    toVisit.push(make_pair(-(w[actual.first][actual.second] + 1),
                                           make_pair(actual.first + 1, actual.second)));
                }
                if (actual.first + power2(actual.second) <= n) {
                    if (w[actual.first][actual.second] + 1 < w[actual.first + power2(actual.second)][actual.second]) {
                        w[actual.first + power2(actual.second)][actual.second] = w[actual.first][actual.second] + 1;
                        toVisit.push(make_pair(-(w[actual.first][actual.second] + 1),
                                               make_pair(actual.first + power2(actual.second),
                                                         actual.second)));
                    }
                }
                break;
            case '*':
                if (actual.second < DIM) {
                    if (w[actual.first][actual.second] + 1 < w[actual.first + 1][actual.second + 1] &&
                        actual.first < n) {
                        w[actual.first + 1][actual.second + 1] = w[actual.first][actual.second] + 1;
                        toVisit.push(make_pair(-(w[actual.first][actual.second] + 1),
                                               make_pair(actual.first + 1, actual.second + 1)));
                    }
                } else {
                    if (w[actual.first][actual.second] + 1 < w[actual.first + 1][actual.second] && actual.first < n) {
                        w[actual.first + 1][actual.second] = w[actual.first][actual.second] + 1;
                        toVisit.push(make_pair(-(w[actual.first][actual.second] + 1),
                                               make_pair(actual.first + 1, actual.second)));
                    }
                }
                if (actual.first + power2(actual.second + 1) <= n) {
                    if (w[actual.first][actual.second] + 1 <
                        w[actual.first + power2(actual.second + 1)][actual.second + 1]) {
                        w[actual.first + power2(actual.second + 1)][actual.second + 1] =
                                w[actual.first][actual.second] + 1;
                        toVisit.push(make_pair(-(w[actual.first][actual.second] + 1),
                                               make_pair(actual.first + power2(actual.second + 1),
                                                         actual.second + 1)));
                    }
                }
                break;
            case '#':
                continue;
            case '>':
                if (w[actual.first][actual.second] < w[actual.first + K][actual.second] && actual.first + K <= n) {
                    w[actual.first + K][actual.second] = w[actual.first][actual.second];
                    toVisit.push(make_pair(-(w[actual.first][actual.second]),
                                           make_pair(actual.first + K, actual.second)));
                }
                break;
            case '<':
                if (w[actual.first][actual.second] < w[actual.first - K][actual.second] && 1 <= actual.first - K) {
                    w[actual.first - K][actual.second] = w[actual.first][actual.second];
                    toVisit.push(make_pair(-(w[actual.first][actual.second]),
                                           make_pair(actual.first - K, actual.second)));
                }
                break;
            case 'U':
                if (w[actual.first][actual.second] + U + 1 < w[actual.first + 1][actual.second] && actual.first < n) {
                    w[actual.first + 1][actual.second] = w[actual.first][actual.second] + U + 1;
                    toVisit.push(make_pair(-(w[actual.first][actual.second] + U + 1),
                                           make_pair(actual.first + 1, actual.second)));
                }
                if (actual.first + power2(actual.second) <= n) {
                    if (w[actual.first][actual.second] + U + 1 <
                        w[actual.first + power2(actual.second)][actual.second]) {
                        w[actual.first + power2(actual.second)][actual.second] = w[actual.first][actual.second] + U + 1;
                        toVisit.push(make_pair(-(w[actual.first][actual.second] + U + 1),
                                               make_pair(actual.first + power2(actual.second),
                                                         actual.second)));
                    }
                }
                break;
            default:
                break;
        }
    }


    int out = MAXINT;
    for (int i = 1; i <= DIM; i++) {
        out = min(out, w[n][i]);
    }
    if (out == MAXINT)
        out = -1;

    cout << out;

    return 0;
}