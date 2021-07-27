#include <iostream>
using namespace std;

#define MAX_N 50000
#define MAX_M 500000
#define INF 1000000000

int Max(int a, int b) {return a > b ? a : b;};

struct Node {
    int dest;
    int dist;
    Node* next;
    Node* Alloc(int _dest, int _dist, Node* _next) {
        dest = _dest;
        dist = _dist;
        next = _next;
        return this;
    }
} pool[MAX_M * 2];
int nodeCnt;

Node heads[MAX_N];
Node headsR[MAX_N];
int dists[MAX_N];
int distsR[MAX_N];

struct QNode {
    int tgt;
    QNode* next;
    QNode* Alloc(int _tgt, QNode* _next) {
        tgt = _tgt;
        next = _next;
        return this;
    }
} qPool[MAX_M];
int qCnt;
QNode q;
QNode* tail;

void InitQ() {
    qCnt = 0;
    q.Alloc(-1, nullptr);
    tail = &q;
}
void Push(int tgt) {
    tail->next = qPool[qCnt++].Alloc(tgt, nullptr);
    tail = tail->next;
    return;
}
int Pop() {
    int ret = q.next->tgt;
    q.next = q.next->next;
    if(!q.next) InitQ();
    return ret;
}

int N, M, X;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T;
    freopen("input.txt", "r", stdin);
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N >> M >> X;
        X--;
        nodeCnt = 0;
        for(int n = 0; n < N; n++) {
            heads[n].Alloc(-1, -1, nullptr);
            headsR[n].Alloc(-1, -1, nullptr);
            dists[n] = INF;
            distsR[n] = INF;
        }

        for(int m = 0; m < M; m++) {
            int s, e, t;
            cin >> s >> e >> t;
            s--;
            e--;
            heads[s].next = pool[nodeCnt++].Alloc(e, t, heads[s].next);
            headsR[e].next = pool[nodeCnt++].Alloc(s, t, headsR[e].next);
        }

        InitQ();
        dists[X] = 0;
        Push(X);
        while(q.next) {
            int tgt = Pop();
            Node* pivot = &heads[tgt];
            while(pivot->next) {
                pivot = pivot->next;
                int dest = pivot->dest;
                int dist = pivot->dist;
                if(dists[dest] > dists[tgt] + dist) {
                    dists[dest] = dists[tgt] + dist;
                    Push(dest);
                }
            }
        }


        InitQ();
        distsR[X] = 0;
        Push(X);
        while(q.next) {
            int tgt = Pop();
            Node* pivot = &headsR[tgt];
            while(pivot->next) {
                pivot = pivot->next;
                int dest = pivot->dest;
                int dist = pivot->dist;
                if(distsR[dest] > distsR[tgt] + dist) {
                    distsR[dest] = distsR[tgt] + dist;
                    Push(dest);
                }
            }
        }


        int max = 0;
        for(int n = 0; n < N; n++) max = Max(max, dists[n] + distsR[n]);

        cout << '#' << tc << ' ' << max << endl;
    }
    return 0;
}