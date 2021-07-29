#include <iostream>
using namespace std;

#define MAXN 12
#define MAXM 12

const int dr[4] = {0, 0, 1, -1};
const int dc[4] = {1, -1, 0, 0};

int N, M;
int map[MAXN][MAXN];
int cores[MAXM][2];
int maxCore;
int minEdge;

struct Node {
    int core;
    int cNum;
    int eNum;
    int **cmap;
    Node* prev;
    Node(int _core, int _cNum, int _eNum, Node* _prev, int** _cmap):
        core(_core), cNum(_cNum), eNum(_eNum), prev(_prev), cmap(_cmap) {}
};

int** CpyMap(int **cmap) {
    int** nmap = new int*[N];
    for(int i = 0; i < N; i++) {
        nmap[i] = new int[N];
        for(int j = 0; j < N; j++) nmap[i][j] = cmap[i][j];
    }
    return nmap;
}

void DelMap(int** omap) {
    for(int i = 0; i < N; i++) {
        delete [] omap[i];
    }
    delete [] omap;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        M = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                cin >> map[i][j];
                if(map[i][j] == 1) {
                    cores[M][0] = i;
                    cores[M][1] = j;
                    M++;
                }
            }
        }
        maxCore = 0;
        minEdge = 0;

        int** dmap = new int*[N];
        for(int i = 0; i < N; i++) {
            dmap[i] = new int[N];
            for(int j = 0; j < N; j++) dmap[i][j] = map[i][j];
        }

        Node* sp = new Node(0, 0, 0, nullptr, dmap);

        while(sp) {
            int core = sp->core;
            int cNum = sp->cNum;
            int eNum = sp->eNum;
            int** cmap = sp->cmap;
            Node* tmp = sp->prev;
            delete sp;
            sp = tmp;
            if(core == M) {
                if(maxCore < cNum || (maxCore == cNum && minEdge > eNum)) {
                    maxCore = cNum;
                    minEdge = eNum;
                }
                DelMap(cmap);
                continue;
            }
            if(M - core < maxCore - cNum) {
                DelMap(cmap);
                continue;
            }
            sp = new Node(core+1, cNum, eNum, sp, CpyMap(cmap)); // X
            for(int i = 0; i < 4; i++) {
                int r = cores[core][0];
                int c = cores[core][1];
                int cnt = 0;
                int** nmap = CpyMap(cmap);
                while(true) {
                    r += dr[i];
                    c += dc[i];
                    if(r < 0 || r >= N || c < 0 || c >= N) {
                        sp = new Node(core+1, cNum+1, eNum + cnt, sp, nmap);
                        break;
                    }
                    if(nmap[r][c] != 0) {
                        DelMap(nmap);
                        break;
                    }
                    nmap[r][c] = 2;
                    cnt++;
                }
            }
            DelMap(cmap);
        }
        cout << '#' << tc << ' ' << minEdge << "\n";
    }
}