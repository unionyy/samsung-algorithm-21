#include <iostream>
using namespace std;

#define MAXV 10001

int parents[MAXV];
int children[MAXV][2];
bool check[MAXV];

int CountSubtree(int v) {
    if(v == -1) return 0;
    return CountSubtree(children[v][0]) + CountSubtree(children[v][1]) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int V, E, a, b;
        cin >> V >> E >> a >> b;
        for(int v = 1; v <= V; v++) {
            children[v][0] = -1;
            children[v][1] = -1;
            check[v] = false;
        }
        for(int e = 0; e < E; e++) {
            int child, parent;
            cin >> parent >> child;
            parents[child] = parent;
            if(children[parent][0] == -1) children[parent][0] = child;
            else children[parent][1] = child;
        }
        parents[1] = -1;
        check[1] = false;
        while(a != 1) {
            a = parents[a];
            check[a] = true;
        }
        while(b != 1) {
            b = parents[b];
            if(check[b]) break;
        }
        cout << '#' << tc << ' ' << b << ' ' << CountSubtree(b) << "\n";
    }
    return 0;
}