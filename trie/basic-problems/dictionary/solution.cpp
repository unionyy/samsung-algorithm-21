struct TrieNode {
    int cnt;
    TrieNode* next[26];

    TrieNode* Alloc() {
        cnt = 0;
        for(int i = 0; i < 26; i++) next[i] = nullptr;
        return this;
    }
} nodes[1000000];
int nodeCnt;
TrieNode head;

void init(void) {
    nodeCnt = 0;
    head.Alloc();
}

void insert(int buffer_size, char *buf) {
    TrieNode* node = &head;
    for(int i = 0; i < buffer_size; i++) {
        int anum = buf[i] - 'a';
        if(!node->next[anum]) node->next[anum] = nodes[nodeCnt++].Alloc();
        node->cnt++;
        node = node->next[anum];
    }
    node->cnt++;
    return;
}

int query(int buffer_size, char *buf) {
    TrieNode* node = &head;
    for(int i = 0; i < buffer_size; i++) {
        int anum = buf[i] - 'a';
        if(!node->next[anum]) return 0;
        node = node->next[anum];
    }
	return node->cnt;
}