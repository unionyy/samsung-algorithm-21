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
    head.Alloc();
    nodeCnt = 0;
}

void Add(int start, int end) {
    TrieNode* node = &head;
    bool exist = true;
    for(int i = start; i < end; i++) {
        int anum = str[i] - 'a';
        if(!node->next[anum]) {
            exist = false;
            break;
        }
        node = node->next[anum];
    }

    if(exist && node->end) return;
    node = &head;
    for(int i = start; i < end; i++) {
        int anum = str[i] - 'a';
        if(!node->next[anum]) node->next[anum] = nodes[nodeCnt++].Alloc();
        node->cnt++;
        node = node->next[anum];
    }
    node->cnt++;
    node->end = true;
    return;
}

void Find(int k) {
    TrieNode* node = &head;
    if(node->cnt < k) {
        cout << "none";
        return;
    }
    while(true) {
        if(node->end) k--;
        if(k == 0) return;

        for(int i = 0; i < 26; i++) {
            if(!node->next[i]) continue;
            k -= node->next[i]->cnt;
            if(k < 1) {
                k += node->next[i]->cnt;
                node = node->next[i];
                cout << (char)('a' + i);
                break;
            }
        }
    }
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
        cin >> K >> str;
        int M = 0;
        for(int i = 0; str[i]; i++) M++;

        Init();
        for(int i = 0; i < M; i++)
            for(int j = i + 1; j < M + 1; j++)
                Add(i, j);
        cout << '#' << tc << ' ';
        Find(K);
        cout << '\n';
    }
    return 0;
}