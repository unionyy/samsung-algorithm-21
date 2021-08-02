#include <iostream>
using namespace std;

#define MAXN 100

int N;

struct Node {
    char alpha;
    int children[2];
} nodes[MAXN];

char text[MAXN];
int textCnt;

void Inorder(int idx) {
    if(nodes[idx].children[0] != -1) Inorder(nodes[idx].children[0]);
    text[textCnt++] = nodes[idx].alpha;
    if(nodes[idx].children[1] != -1) Inorder(nodes[idx].children[1]);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    for(int tc = 1; tc <= 10; tc++) {
        cin >> N;
        for(int n = 0; n < N; n++) {
            int idx;
            cin >> idx;
            idx--;
            char alpha;
            cin >> alpha;
            int children[2] = {0, };
            if(cin.get() != '\n') {
                cin >> children[0];
                if(cin.get() != '\n') cin >> children[1];
            }
            children[0]--;
            children[1]--;
            nodes[idx].alpha = alpha;
            nodes[idx].children[0] = children[0];
            nodes[idx].children[1] = children[1];
        }
        textCnt = 0;
        Inorder(0);
        cout << '#' << tc << ' ';
        for(int i = 0; i < textCnt; i++) cout << text[i];
        cout << '\n';
    }
    return 0;
}