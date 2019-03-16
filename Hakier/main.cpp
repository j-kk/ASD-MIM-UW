#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

const int MAXN = 100000;

const int pow2 = 1<<17; 

struct node{
    set<pair<int, int>> elements;
    //       b    id
    tuple<int, int, int> min {1000000, 1000000, 1000000};
    tuple<int, int, int> max {-1000000, -1000000, -1000000};
    //    a  , b , id
};

int n, q;
node tree[pow2 * 2];

tuple<int, int, int> minT(tuple<int, int, int> a, tuple<int, int, int> b) {
    if (get<1>(a) < get<1>(b)) {
        return a;
    }
    else {
        if (get<1>(a) > get<1>(b))
            return b;
        else {
            if (get<2>(a) < get<2>(b))
                return a;
            else return b;
        }
    }
}

tuple<int, int, int> maxT(tuple<int, int, int> a, tuple<int, int, int> b) {
    if (get<1>(a) > get<1>(b)) {
        return a;
    }
    else {
        if (get<1>(a) < get<1>(b))
            return b;
        else {
            if (get<2>(a) < get<2>(b))
                return a;
            else return b;
        }
    }
}

void insert(int id, int a, int b) {
    int x = a + pow2 - 1;
    pair<int, int> toInsert {b, id};
    tree[x].elements.insert(toInsert);
    tree[x].min = (tuple<int,int,int>){a, (*tree[x].elements.begin()).first , (*tree[x].elements.begin()).second};
    tree[x].max = (tuple<int,int,int>){a, (*tree[x].elements.rbegin()).first, (*tree[x].elements.rbegin()).second};
    
    while (x > 1) {
        x /= 2;
        tree[x].min = minT(tree[x * 2].min, tree[x * 2 + 1].min);
        tree[x].max = maxT(tree[x * 2].max, tree[x * 2 + 1].max);
    }
}


tuple<int, int, int> queryMin(int a, int b) {

    int xa = a + pow2 - 1;
    int xb = b + pow2 - 1;

    tuple<int, int, int> res;
    res = minT(tree[xa].min, tree[xb].min);

    while (xa / 2 < xb / 2) {

        if (xa % 2 == 0)
            res = minT(res, tree[xa + 1].min);

        if (xb % 2 == 1)
            res = minT(res, tree[xb - 1].min);

        xa /= 2;
        xb /= 2;
    }

    return res;
}
tuple<int, int, int> queryMax(int a, int b) {

    int xa = a + pow2 - 1;
    int xb = b + pow2 - 1;

    tuple<int, int, int> res;
    res = maxT(tree[xa].max, tree[xb].max);

    while (xa / 2 < xb / 2) {

        if (xa % 2 == 0) {
            res = maxT(res, tree[xa + 1].max);
        }
        if (xb % 2 == 1) {
            res = maxT(res, tree[xb - 1].max);
        }
        xa /= 2;
        xb /= 2;
    }

    return res;
}
//                a    b    id
void remove(tuple<int, int, int> v) {
    
    int x = get<0>(v) + pow2 - 1;

    tree[x].elements.erase(pair<int, int>(get<1>(v), get<2>(v)));

    if (tree[x].elements.empty()) {
        tree[x].min = (tuple<int,int,int>) {1000000, 1000000, 1000000};
        tree[x].max = (tuple<int,int,int>) {-1000000, -1000000, -1000000};
    }
    else {//                               na pewno?
        tree[x].min = (tuple<int,int,int>) {get<0>(tree[x].min), (*tree[x].elements.begin() ).first, (*tree[x].elements.begin()).second };
        tree[x].max = (tuple<int,int,int>) {get<0>(tree[x].max), (*tree[x].elements.rbegin()).first, (*tree[x].elements.rbegin()).second};
    }

    while (x > 1) {
        x /= 2;
        tree[x].min = minT(tree[x * 2].min, tree[x * 2 + 1].min);
        tree[x].max = maxT(tree[x * 2].max, tree[x * 2 + 1].max);
    }
    
}

int main(int argc, const char * argv[]) {
    cin>>n;

    int a, b;

    for (int i = 0; i < n; ++i) {
        cin>>a>>b;
        insert(i + 1, a, b);
    }
    cin>>q;
    string s;
    while (q > 0) {
        q--;
        cin >> s >> a >> b;
        tuple<int, int, int> candidate;
        if (s == "in") {
            candidate = queryMin(a, b);
            if (get<1>(candidate) <= b) {
                int id = get<2>(candidate);
                remove (candidate);
                cout<<id<<endl;
//                cout<<1<<endl;
                continue;
            } else {
                cout<<-1<<endl;
            }
        } else {
            if (s == "over") {
                candidate = queryMax(1, a);
                if (get<1>(candidate) >= b) {
                    int id = get<2>(candidate);
                    remove (candidate);
                    cout<<id<<endl;
//                    cout<<1<<endl;
                    continue;
                } else {
                    cout<<-1<<endl;
                }
            } else {
                if (s == "none") {
                    candidate = queryMin(1, a - 1);
                    if (get<1>(candidate) < a) {
                        int id = get<2>(candidate);
                        remove (candidate);
                        cout<<id<<endl;
//                        cout<<1<<endl;
                        continue;
                    } else {
                        candidate = queryMin(b + 1, MAXN);
                        if (get<1>(candidate) <= MAXN) {
                            int id = get<2>(candidate);
                            remove (candidate);
                            cout<<id<<endl;
//                            cout<<1<<endl;
                            continue;
                        } else {
                            cout<<-1<<endl;
                        }
                    }
                } else {
                    if (s == "some") {
                    candidate = queryMax(1, b);
                    if (get<1>(candidate) >= a) {
                        int id = get<2>(candidate);
                        remove (candidate);
                        cout<<id<<endl;
//                        cout<<1<<endl;
                        continue;
                    } else {
                        cout<<-1<<endl;
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}
