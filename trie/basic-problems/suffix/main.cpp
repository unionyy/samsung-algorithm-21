#include <iostream>
using namespace std;

#define MAXM 400

char str[MAXM];

struct TrieNode {
    int cnt;
    bool end;
    TrieNode* next[26];

    TrieNode* Alloc() {
        cnt = 0;
        end = false;
        for(int i = 0; i < 26; i++) next[i] = nullptr;
        return this;
    }
} nodes[MAXM * MAXM];
int nodeCnt;
TrieNode head;

void Init() {
    nodeCnt = 0;
    head.cnt = 0;
    for(int i = 0; i < 26; i++) head.next[i] = nullptr;
}

void Add(char* s) {
    int pivot = 0;
    TrieNode* node = &head;
    while(s[pivot]) {
        int alpn = s[pivot] - 'a';
        if(!node->next[alpn]) {
            node->next[alpn] = nodes[nodeCnt++].Alloc();
        }
        node->cnt++;
        node = node->next[alpn];
        pivot++;
    }
    node->cnt++;
    node->end = true;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int K;
        cin >> K;
        cin >> str;
        for(int i = 0; str[i]; i++) Add(&str[i]);
    }
    return 0;
}