#define MAX_NODE 200000

void mstrcpy(char dst[], const char src[])
{
	int c = 0;
	while ((dst[c] = src[c]) != 0)
		++c;
}

int mstrlen(const char str[])
{
	int ret = 0;
	while (str[ret])
		++ret;
	return ret;
}

int mstrcmp(const char str1[], const char str2[])
{
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c])
		++c;
	return str1[c] - str2[c];
}

struct TrieNode {
    char str[20];
    int cnt, time;
    TrieNode *best, *parent, *next[26];
    bool ban;

    TrieNode* Alloc(TrieNode *_parent) {
        str[0] = 0;
        cnt = 0;
        time = 0;
        best = this;
        parent = _parent;
        for(int i = 0; i < 26; i++) next[i] = nullptr;
        ban = false;

        return this;
    }

    void init(char *_str, int _time, bool _ban) {
        if(ban) return;
        mstrcpy(str, _str);
        time = _time;
        cnt = 1;
        ban = _ban;

        return;
    }

    void Add(int _time) {
        time = _time;
        cnt ++;
        return;
    }

    void Ban() {
        ban = true;

        return;
    }
} nodes[MAX_NODE];
int nodeCnt;
TrieNode* head;
int wordCnt;

bool nodecmp(TrieNode* a, TrieNode* b) {
    if(!b) return true;
    if(a->ban) return false;
    if(b->ban) return true;
    if(a->cnt > b->cnt) return true;
    if(a->cnt < b->cnt) return false;
    if(a->time > b->time) return true;
    return false;
}

void init()
{
    nodeCnt = 0;
    wordCnt = 0;
    head = nodes[nodeCnt++].Alloc(nullptr);

    return;
}

void inputWord(char mWord[20])
{
    TrieNode* pivot = head;
    char* a = mWord;

    while(*a) {
        int num = *a++ - 'a';
        if(!pivot->next[num]) 
            pivot->next[num] = nodes[nodeCnt++].Alloc(pivot);
        pivot = pivot->next[num];
    }
    if(pivot->cnt) pivot->Add(wordCnt++);
    else pivot->init(mWord, wordCnt++, false);

    TrieNode* pivot2 = pivot;
    while(pivot2) {
        if(nodecmp(pivot, pivot2->best)) pivot2->best = pivot;
        pivot2 = pivot2->parent;
    }

    return;
}

int recommend(char mUser[20], char mAnswer[20])
{
    TrieNode *pivot = head;
    char *a = mUser;
    while(*a) {
        int num = *a++ - 'a';
        if(!pivot->next[num]) {
            mstrcpy(mAnswer, mUser);
            return mstrlen(mUser);
        }
        pivot = pivot->next[num];
    }
    pivot = pivot->best;
    if(pivot->cnt == 0 || pivot->ban) {
        mstrcpy(mAnswer, mUser);
        return mstrlen(mUser);
    }
    mstrcpy(mAnswer, pivot->str);

	return mstrlen(mAnswer);
}

void banWord(char mWord[20])
{
    TrieNode *pivot = head;
    char *a = mWord;
    while(*a) {
        int num = *a++ - 'a';
        if(!pivot->next[num])
            pivot->next[num] = nodes[nodeCnt++].Alloc(pivot);
        pivot = pivot->next[num];
    }
    pivot->Ban();

    TrieNode *pivot2 = pivot;
    while(pivot2) {
        if(pivot2->best == pivot) {
            for(int i = 0; i < 26; i++) {
                if(pivot2->next[i]) {
                    if(nodecmp(pivot2->next[i]->best, pivot2->best))
                        pivot2->best = pivot2->next[i]->best;
                }
            }
            pivot2 = pivot2->parent;
        } else break;
    }

    return;

}