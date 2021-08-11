#include <iostream>
using namespace std;

#define MAXN 2000
#define HASH_SIZE (1 << 30)
#define DIV (HASH_SIZE - 1)

int H, W, N, M;

int myPic[MAXN][MAXN], samPic[MAXN][MAXN];
int samHash[MAXN][MAXN], tmp[MAXN][MAXN];

int CalcMul(int num) {
    unsigned long long rev = 1;
    for(int i = 1; i < num; i++) {
        rev = (rev << 5) + rev;
    }
    return (int)rev;
}

int GetHash(int* piv, int num) {
    unsigned long long hash = 0;
    for(int i = 0; i < num; i++) {
        hash = (hash << 5) + hash + *piv++;
    }
    return (int)hash & DIV;
}

int GetNext(int prev, int sub, int mul, int add) {
    unsigned long long hash = prev - (sub * mul);
    hash = (hash << 5) + hash + add;
    return (int) hash & DIV;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> H >> W >> N >> M;
        for(int h = 0; h < H; h++) for(int w = 0; w < W; w++) {
            char a;
            cin >> a;
            if(a == 'o') myPic[h][w] = 2;
            else myPic[h][w] = 1;
        }
        for(int n = 0; n < N; n++) for(int m = 0; m < M; m++) {
            char a;
            cin >> a;
            if(a == 'o') samPic[n][m] = 2;
            else samPic[n][m] = 1;
        }

        // Get My Hash
        for(int i = 0; i < H; i++) tmp[0][i] = GetHash(myPic[i], W);
        int myHash = GetHash(tmp[0], H);

        // Get Sam Hash
        int mulC = CalcMul(W);
        int mulR = CalcMul(H);
        for(int i = 0; i < N; i++) {
            tmp[0][i] = GetHash(samPic[i], W);
            for(int j = 1; j < M - W + 1; j++) {
                tmp[j][i] = GetNext(tmp[j-1][i], samPic[i][j-1], mulC, samPic[i][j+W-1]);
            }
        }
        for(int i = 0; i < M - W + 1; i++) {
            samHash[0][i] = GetHash(tmp[i], H);
            for(int j = 1; j < N - H + 1; j++) {
                samHash[j][i] = GetNext(samHash[j-1][i], tmp[i][j-1], mulR, tmp[i][j+H-1]);
            }
        }

        // Compare
        int cnt = 0;
        for(int i = 0; i < N - H + 1; i++) for(int j = 0; j < M - W + 1; j++)
            if(samHash[i][j] == myHash) cnt++;
        cout << '#' << tc << ' ' << cnt << '\n';
    }
    return 0;
}