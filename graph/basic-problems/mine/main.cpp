#include <iostream>
using namespace std;

#define MAXN 300

const int dr[8] = {-1, -1, -1,  0,  0,  1,  1,  1};
const int dc[8] = {-1,  0,  1, -1,  1, -1,  0,  1};

int N;
int map[MAXN][MAXN];

void Bomb(int r, int c) {
    if(r < 0 || r >= N || c < 0 || c >= N) return;
    int val = map[r][c];
    if(val > 0) map[r][c] = -1;
    else if(val == 0) {
        map[r][c] = -1;
        for(int i = 0; i < 8; i++) {
            Bomb(r + dr[i],c + dc[i]);
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
        cin >> N;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                char a;
                cin >> a;
                if(a == '.') map[i][j] = 0;
                else map[i][j] = -2;
            }
        }
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(map[i][j] == -2) {
                    for(int k = 0; k < 8; k++) {
                        int ii = i + dr[k];
                        int jj = j + dc[k];
                        if(ii < 0 || ii >= N || jj < 0 || jj >= N) continue;
                        if(map[ii][jj] >= 0) map[ii][jj]++;
                    }
                }
            }
        }
        int cnt = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(map[i][j] != 0) continue;
                Bomb(i, j);
                cnt++;
            }
        }
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(map[i][j] > 0) cnt++;
            }
        }
        cout << '#' << tc << ' ' << cnt << "\n";
    }
}