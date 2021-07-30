#include <iostream>
using namespace std;

#define MAXN 100000

int N;
int parents[MAXN];

struct Node {
    Node* next;
    int node;
    int depth;
    Node* Alloc(Node* _next, int _node, int _depth) {
        next = _next;
        node = _node;
        depth = _depth;
        return this;
    }
} pool[MAXN];
int nodeCnt;

struct Child {
    Child* next;
    int node;
    Child* Alloc(Child* _next, int _node) {
        next = _next;
        node = _node;
        return this;
    }
} childPool[MAXN];
int childCnt;
Child children[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    parents[0] = -1;

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        childCnt = 0;
        for(int i = 0; i < N; i++) children[i].next = nullptr;
        for(int i = 1; i < N; i++) {
            int p;
            cin >> p;
            p--;
            parents[i] = p;
            Child* child = &children[p];
            while(child->next) child = child->next;
            child->next = childPool[childCnt++].Alloc(nullptr, i);
        }
        nodeCnt = 0;
        Node* head = pool[nodeCnt++].Alloc(nullptr, 0, 0);
        Node* tail = head;
        int ans = 0;
        while(true) {
            int node = head->node;
            int depth = head->depth;
            Child* child = &children[node];
            while(child->next) {
                tail->next = pool[nodeCnt++].Alloc(nullptr, child->next->node, depth+1);
                tail = tail->next;
                child = child->next;
            }
            if(!(head->next)) break;
            head = head->next;
            int nodeN = head->node;
            int depthN = head->depth;
            int cnt = 0;
            if(depth < depthN) {
                nodeN = parents[nodeN];
                cnt++;
            }
            while(node != nodeN) {
                cnt += 2;
                node = parents[node];
                nodeN = parents[nodeN];
            }
            ans += cnt;
        }

        cout << '#' << tc << ' ' << ans << "\n";
    }
}