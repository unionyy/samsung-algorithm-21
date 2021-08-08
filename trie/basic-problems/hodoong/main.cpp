#include <iostream>
using namespace std;

#define MAXN 30000
#define MAXM 30000

struct TrieNode {
    int cnt;
    int ans;
    TrieNode* next[26];

    TrieNode* Alloc() {
        cnt = 0;
        ans = -1;
        for(int i = 0; i < 26; i++) next[i] = nullptr;
        return this;
    }
} nodes[MAXN * 30];
int nodeCnt;
TrieNode head;

void Init() {
    nodeCnt = 0;
    head.Alloc();
}

void Add (char* str) {
    TrieNode* node = &head;
    int ans = 0;
    for(int i = 0; str[i]; i++) {
        node->cnt++;
        ans += node->cnt;
        int anum = str[i] - 'a';
        if(!node->next[anum]) node->next[anum] = nodes[nodeCnt++].Alloc();
        node = node->next[anum];
    }
    node->cnt++;
    ans += node->cnt;
    node->ans = ans;
    return;
}

int Find(char* str) {
    TrieNode* node = &head;
    int ans = 0;
    bool none = false;
    for(int i = 0; str[i]; i++) {
        ans += node->cnt;
        int anum = str[i] - 'a';
        if(!node->next[anum]) {
            none = true;
            break;
        }
        node = node->next[anum];
    }
    if(none) return ans;
    if(node->ans == -1) return ans + node->cnt;
    return node->ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    char str[30];
    for(int tc = 1; tc <= T; tc++) {
        int N, M;
        cin >> N;
        Init();
        for(int n = 0; n < N; n++) {
            cin >> str;
            Add(str);
        }
        cin >> M;
        long long ans = 0;
        for(int m = 0; m < M; m++) {
            cin >> str;
            ans += Find(str);
        }
        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}