#include <iostream>
using namespace std;

#define MAXN 100000
#define MAX_LENGTH 51
#define HASH_SIZE (1 << 18)
#define DIV (HASH_SIZE - 1)

void StrCpy(char *empty, char *str) {
    while(*str) *empty++ = *str++;
    *empty = 0;
    return;
}

bool StrCmp(char *strA, char *strB) {
    while(*strA) {
        if(*strA++ != *strB++) return false;
    }
    return *strA == *strB;
}

int GetHash(char* str) {
    unsigned long long hash = 5381;
    while(*str) {
        hash = (hash << 5) + hash + *str - 'a';
        *str++;
    }
    return (int)hash & DIV; 
}

struct HashNode {
    char str[MAX_LENGTH];
    HashNode* next;
    HashNode* Alloc(char *_str, HashNode* _next) {
        StrCpy(str, _str);
        next = _next;
        return this;
    }
} nodes[MAXN];

HashNode* hashTable[HASH_SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    int N, M;
    char str[MAX_LENGTH];
    for(int tc = 1 ; tc <= T; tc++) {
        cin >> N >> M;
        int nodeCnt = 0;
        for(int i = 0; i < HASH_SIZE; i++) hashTable[i] = nullptr;
        for(int n = 0; n < N; n++) {
            cin >> str;
            int hash = GetHash(str);
            hashTable[hash] = nodes[nodeCnt++].Alloc(str, hashTable[hash]);
        }
        int ans = 0;
        for(int m = 0; m < M; m++) {
            cin >> str;
            int hash = GetHash(str);
            HashNode* node = hashTable[hash];
            while(node) {
                if(StrCmp(node->str, str)) {
                    ans++;
                    break;
                } else node = node->next;
            }
        }
        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}