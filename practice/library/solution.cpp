#define MAX_N			5

#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

#define TAG_HASH        (1 << 18)
#define MAX_BOOK        50000

struct TrieNode {
    int bookNum;
    TrieNode* nexts[52];

    TrieNode* Alloc(int _bookNum) {
        bookNum = _bookNum;
        for(int i = 0; i < 52; i++) nexts[i] = nullptr;

        return this;
    }
} nodes[MAX_BOOK * 6];
int nodeCnt;
TrieNode trieHead;

struct ClassNode {
    int bookNum;
    int tag;
    ClassNode *prev, *next;

    ClassNode* Alloc(int _bookNum, int _tag, ClassNode *_prev, ClassNode *_next) {
        bookNum = _bookNum;
        tag = _tag;
        prev = _prev;
        next = _next;
        if(prev) prev->next = this;
        if(next) next->prev = this;

        return this;
    }
} classPool[MAX_BOOK * 5];
int classCnt;
ClassNode classes[100][500];

int tagHash[TAG_HASH];
int tagCnt;
struct Book {
    TrieNode* trieNode;
    ClassNode* classNodes[5];

    Book* Alloc(TrieNode* _trieNode, ClassNode* _classNodes[5]) {
        trieNode = _trieNode;
        for(int i = 0; i < 5; i++) classNodes[i] = _classNodes[i];

        return this;
    }
} books[MAX_BOOK];
int bookCnt;

int M;

int getTypeIdx(char *type) {
    int hash = 0;
    while(*type) {
        int num;
        if(*type <= 'Z' && *type >= 'A') num = *type - 'A' + 27;
        else num = *type - 'a' + 1;
        hash = (hash << 6) + num;
        type++;
    }
    if(tagHash[hash] == -1) tagHash[hash] = tagCnt++;

    return tagHash[hash];
}

// #include <stdio.h>
// void showBooks() {
//     printf("@@@\n");
//     for(int i = 0; i < M; i++) {
//         for(int j = 0; j < tagCnt; j++) {
//             ClassNode *pivot = classes[i][j].next;
//             while(pivot){
//                 if(pivot->prev)
//                     printf("Section: %d, Tag: %d, Num: %d, prev: %d\n", i, j, pivot->bookNum, pivot->prev->bookNum);
//                 else
//                     printf("Section: %d, Tag: %d, Num: %d, prev: X\n", i, j, pivot->bookNum);
//                 pivot = pivot->next;
//             }
//         }
//     }
// }

void init(int _M)
{
    M = _M;
    nodeCnt = 0;
    trieHead.Alloc(-1);
    classCnt = 0;
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < 500; j++) classes[i][j].Alloc(-1, -1, nullptr, nullptr);
    }

    for(int i = 0; i < TAG_HASH; i++) tagHash[i] = -1;

    bookCnt = 0;
    tagCnt = 0;

    return;
}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
    mSection--;
    int cTag[5] = {-1, -1, -1, -1, -1};
    for(int i = 0; i < mTypeNum; i++) {
        cTag[i] = getTypeIdx(mTypes[i]);
    }

    TrieNode* pivot = &trieHead;
    while(*mName) {
        int num;
        if(*mName >='A' && *mName <= 'Z') num = *mName - 'A' + 26;
        else num = *mName - 'a';
        if(!pivot->nexts[num]) pivot->nexts[num] = nodes[nodeCnt++].Alloc(-1);
        pivot = pivot->nexts[num];
        mName++;
    }

    pivot->bookNum = bookCnt;
    ClassNode *cPivots[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    for(int i = 0; i < mTypeNum; i++) {
        cPivots[i] = classPool[classCnt++].Alloc(bookCnt, cTag[i], &classes[mSection][cTag[i]], classes[mSection][cTag[i]].next);
    }
    books[bookCnt++].Alloc(pivot, cPivots);

    return;
}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
    mFrom--; mTo--;
    int tag = getTypeIdx(mType);

    ClassNode *pivot = &classes[mFrom][tag];
    int cnt = 0;
    while(pivot->next) {
        Book *book = &books[pivot->next->bookNum];
        for(int i = 0; i < 5; i++) {
            if(!book->classNodes[i]) break;
            ClassNode *tmp = book->classNodes[i];
            if(tmp->next) tmp->next->prev = tmp->prev;
            if(tmp->prev) tmp->prev->next = tmp->next;
            tmp->next = classes[mTo][tmp->tag].next;
            if(tmp->next) tmp->next->prev = tmp;
            tmp->prev = &classes[mTo][tmp->tag];
            classes[mTo][tmp->tag].next = tmp;
        }
        cnt++;
    }

	return cnt;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{
    mSection--;
    TrieNode *pivot = &trieHead;
    while(*mName) {
        int num;
        if(*mName >='A' && *mName <= 'Z') num = *mName - 'A' + 26;
        else num = *mName - 'a';
        mName++;
        pivot = pivot->nexts[num];
    }
    Book *book = &books[pivot->bookNum];
    for(int i = 0; i < 5; i++) {
        if(!book->classNodes[i]) break;
        ClassNode *tmp = book->classNodes[i];
        if(tmp->next) tmp->next->prev = tmp->prev;
        if(tmp->prev) tmp->prev->next = tmp->next;
        tmp->next = classes[mSection][tmp->tag].next;
        if(tmp->next) tmp->next->prev = tmp;
        tmp->prev = &classes[mSection][tmp->tag];
        classes[mSection][tmp->tag].next = tmp;
    }

    return;
}

void deleteName(char mName[MAX_NAME_LEN])
{
    TrieNode *pivot = &trieHead;
    while(*mName) {
        int num;
        if(*mName >='A' && *mName <= 'Z') num = *mName - 'A' + 26;
        else num = *mName - 'a';
        mName++;
        pivot = pivot->nexts[num];
    }
    Book *book = &books[pivot->bookNum];
    for(int i = 0; i < 5; i++) {
        if(!book->classNodes[i]) break;
        ClassNode *tmp = book->classNodes[i];
        if(tmp->next) tmp->next->prev = tmp->prev;
        if(tmp->prev) tmp->prev->next = tmp->next;
    }

    return;
}

int countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection)
{
    mSection--;
    bool check[MAX_BOOK] = {false, };
    for(int i = 0; i < mTypeNum; i++) {
        int tag = getTypeIdx(mTypes[i]);
        ClassNode *pivot = classes[mSection][tag].next;
        while(pivot) {
            check[pivot->bookNum] = true;
            pivot = pivot->next;
        }
    }
    int cnt = 0;
    for(int i = 0; i < MAX_BOOK; i++) if(check[i]) cnt++;

	return cnt;
}