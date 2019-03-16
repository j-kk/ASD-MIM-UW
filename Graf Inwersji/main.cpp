#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 1000000;


struct node {
    node* parent;
    int v;
};
int keyCount;
int N;
node nodes[MAXN];
map<int, node*> nodeMap;

multimap<int, int> res;
int amount[MAXN];

inline void makeNode (node* newNode, int v) {
    newNode->parent = NULL;
    newNode->v = v;
    nodeMap[v] = newNode;
}

node* findRoot(node* a) {
    if (a->parent == NULL) {
        return a;
    }
    else {
        a->parent = findRoot(a->parent);
        return a->parent;
    }
}

inline void unionNodes (node* a, node* b) {
    node* aroot = findRoot(a);
    node* broot = findRoot(b);

    broot->parent = aroot;
    nodeMap.erase(broot->v);
    keyCount--;
}



int main() {
    scanf ("%d", &N);
    int t;
    keyCount = N;
    for (int i = 0; i < N; ++i) {
        scanf ("%d", &t);

        makeNode(&nodes[i], t);
        nodeMap[t] = &nodes[i];
        map<int, node*>::iterator it = nodeMap.lower_bound(t);
        ++it;
        while (it != nodeMap.end()) {
            unionNodes(it->second, &nodes[i]);
            ++it;
        }

    }
    for (int i = 0; i < N; ++i) {
        int r = findRoot(&nodes[i])->v;
        amount[r]++;
        res.insert(pair<int, int>(r, i + 1));
    }

    auto it = res.begin();
    printf ("%d\n", keyCount);
    while (it != res.end()) {
        int current = it->first;
        int currentN = amount[current];
        printf("%d ", currentN);
        for (int i = 0; i < currentN; ++i, ++it) {

            printf("%d ", it->second);
        }
        printf("\n");

    }
    return 0;
}