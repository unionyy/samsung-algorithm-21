#include <iostream>
using namespace std;

const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};

#define MAXN 100

int map[MAXN][MAXN];
int N;

struct Node {
    int recovery;
    int r, c;
} nodes[MAXN * MAXN];
int nodeCnt;
bool check[MAXN][MAXN];

bool CmpSwap(int idxA, int idxB) {
    if(nodes[idxA].recovery > nodes[idxB].recovery) {
        Node tmp = nodes[idxA];
        nodes[idxA] = nodes[idxB];
        nodes[idxB] = tmp;
        return true;
    } else return false;
    
}

void Init() {
    nodeCnt = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            check[i][j] = false;
        }
    }
    return;
}

void Add(int rec, int r, int c) {
    if(check[r][c]) return;
    nodes[nodeCnt].recovery = rec;
    nodes[nodeCnt].r = r;
    nodes[nodeCnt].c = c;
    int pivot = nodeCnt;
    nodeCnt++;
    while(pivot > 0) {
        int ppivot = pivot;
        pivot = (pivot - 1) >> 1;
        if(!CmpSwap(pivot, ppivot)) break;
    }
    return;
}

Node Pop() {
    Node rev = nodes[0];
    check[rev.r][rev.c] = true;
    nodes[0] = nodes[--nodeCnt];
    int pivot = 0;
    while(true) {
        int ppivot = pivot;
        pivot = (pivot << 1) + 1;
        if(pivot >= nodeCnt) break;
        else if(pivot + 1 == nodeCnt) {
            if(!CmpSwap(ppivot, pivot)) break;
        } else {
            if(nodes[pivot].recovery > nodes[pivot + 1].recovery) pivot++;
            if(!CmpSwap(ppivot, pivot)) break;
        }
    }
    return rev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                char a;
                cin >> a;
                map[i][j] = a - '0';
            }
        }
        Init();
        Add(0, 0, 0);
        int ans;
        while(nodeCnt > 0) {
            Node node = Pop();
            if(node.r == N - 1 && node.c == N -1) {
                ans = node.recovery;
                break;
            }
            for(int i = 0; i < 4; i++) {
                int nr = node.r + dr[i];
                int nc = node.c + dc[i];
                if(nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
                int nrec = node.recovery + map[nr][nc];
                Add(nrec, nr, nc);
            }
        }
        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}