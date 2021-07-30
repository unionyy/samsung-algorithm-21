#include <iostream>
using namespace std;

#define MAXN 100000

int N;
int parents[MAXN][17];

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
Child *childtails[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        childCnt = 0;
        for(int i = 0; i < N; i++) {
            children[i].next = nullptr;
            childtails[i] = &children[i];
            for(int j = 0; j < 17; j++) {
                parents[i][j] = -1;
            }
        }
        for(int i = 1; i < N; i++) {
            int p;
            cin >> p;
            p--;
            parents[i][0] = p;
            childtails[p]->next = childPool[childCnt++].Alloc(nullptr, i);;
            childtails[p] = childtails[p]->next;
        }

        for(int i = 1; i < N; i++) {
            for(int j = 1; j < 17; j++) {
                if(parents[i][j-1] == -1) continue;
                parents[i][j] = parents[parents[i][j-1]][j-1];
            }
        }

        nodeCnt = 0;
        Node* head = pool[nodeCnt++].Alloc(nullptr, 0, 0);
        Node* tail = head;
        long long ans = 0;
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
                nodeN = parents[nodeN][0];
                cnt++;
            }
            while(node != nodeN) {
                if(parents[node][0] == parents[nodeN][0]) {
                    cnt += 2;
                    break;
                }
                int i = 1;
                int mul = 2;
                while(i < 17) {
                    if(parents[node][i] == parents[nodeN][i]) break;
                    mul *= 2;
                    i++;
                }
                cnt += mul;
                node = parents[node][i-1];
                nodeN = parents[nodeN][i-1];
            }
            ans += cnt;
        }

        cout << '#' << tc << ' ' << ans << "\n";
    }
    return 0;
}