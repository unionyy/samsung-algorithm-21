#include <iostream>
using namespace std;

char str[20];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    for(int tc = 1; tc <= 10; tc++) {
        int N;
        cin >> N;
        bool pos = true;
        for(int n = 0; n < N; n++) {
            if(!pos) {
                cin.getline(str, 20);
                continue;
            }
            int idx;
            cin >> idx;
            if(idx * 2 < N) {
                char a;
                cin >> a;
                if(a >= '0' && a <= '9') {
                    pos = false;
                    cin.getline(str, 20);
                    continue;
                }
                int b, c;
                cin >> b >> c;
            } else if(idx * 2 == N) {
                pos = false;
                cin.getline(str, 20);
                continue;
            } else {
                char a;
                cin >> a;
                if(a < '0' || a > '9') {
                    pos = false;
                    cin.getline(str, 20);
                    continue;
                }
            }
        }
        cout << '#' << tc << ' ' << pos << '\n';
    }
    return 0;
}