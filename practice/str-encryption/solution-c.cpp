#define MAXN 50005

char str[MAXN];
int N;

int getHash(char *A) {
    int hash = *A++ - 'a';
    hash = (hash << 5) + *A++ - 'a';
    hash = (hash << 5) + *A - 'a';
    return hash;
}

int getNext(int hash, char *A) {
    hash &= (1 << 10) - 1;
    hash = (hash << 5) + *(A+3) - 'a';

    return hash;
}

void mstrcpy(char *dst, char *src) {
    while(*src) *dst++ = *src++;
    *dst = 0;
    return;
}

void init(int _N, char init_string[]) {
    N = _N;
    mstrcpy(str, init_string);

    return;
}

int change(char A[], char B[]) {
    int hashA = getHash(A);

    char *pivot = str;
    int hash = getHash(pivot);

    int cnt = 0;
    while(true) {
        if(hash == hashA) {
            cnt++;
            for(int i = 0; i < 3; i++) {
                pivot[i] = B[i];
            }
            pivot += 3;
            if(pivot[2] == 0) break;
            hash = getHash(pivot);
        }
        else {
            if(pivot[3] == 0) break;
            hash = getNext(hash, pivot);
            pivot++;
        }
    }

    return cnt;
}

void result(char ret[]) {
    mstrcpy(ret, str);
    return;
}