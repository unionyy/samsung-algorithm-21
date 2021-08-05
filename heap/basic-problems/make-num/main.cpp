#include <iostream>
using namespace std;

int A[10];

struct Node {
    int left;
    int cnt;
} nodes[9000];
int nodeCnt;

bool Cmp(Node a, Node b) {
    if(a.cnt == b.cnt) return a.left < b.left;
    else return a.cnt < b.cnt;
}

void Add(int left, int cnt) {
    nodes[nodeCnt].left = left;
    nodes[nodeCnt].cnt = cnt;
    int pivot = nodeCnt;
    nodeCnt++;
    while(pivot > 0) {
        int ppivot = pivot;
        pivot = (pivot - 1) >> 1;
        if(Cmp(nodes[pivot], nodes[ppivot])) return;
        nodes[ppivot] = nodes[pivot];
        nodes[pivot].cnt = cnt;
        nodes[pivot].left = left;
    }
    return;
}

Node Pop() {
    Node rev = nodes[0];

    nodes[0] = nodes[--nodeCnt];

    int pivot = 0;
    while(true) {
        int ppivot = pivot;
        pivot = (pivot << 1) + 1;
        if(nodeCnt <= pivot) break;
        if(pivot + 1 == nodeCnt) {
            if(Cmp(nodes[pivot], nodes[nodeCnt])) {
                nodes[ppivot] = nodes[pivot];
                nodes[pivot] = nodes[nodeCnt];
            } else break;
        } else {
            if(Cmp(nodes[pivot+1], nodes[pivot])) pivot++;
            if(Cmp(nodes[pivot], nodes[nodeCnt])) {
                nodes[ppivot] = nodes[pivot];
                nodes[pivot] = nodes[nodeCnt];
            } else break;
        }
    }
    return rev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for(int tc = 1; tc <=T; tc++) {
        int N, K;
        cin >> N;
        for(int n = 0; n < N; n++) cin >> A[n];
        cin >> K;

        int ans;
        nodeCnt = 0;
        Add(K, 0);
        while(nodeCnt > 0) {
            Node node = Pop();
            int cnt = node.cnt;
            int left = node.left;
            if(left == 0) {
                ans = cnt;
                break;
            }
            bool add = false;
            for(int n = 0; n < N; n++) {
                if(left >= A[n]) {
                    Add(left / A[n], cnt + (left % A[n]));
                    add = true;
                }
            }
            if(!add) Add(0, cnt + left);
        }

        cout << '#' << tc << ' ' << ans << '\n';
    }
}