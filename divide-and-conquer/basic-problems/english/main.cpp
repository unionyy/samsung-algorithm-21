#include <iostream>
using namespace std;

#define MAXDAY 1000000

int days[MAXDAY];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int N, P;
        cin >> N >> P;
        for(int i = 0; i < MAXDAY; i++) days[i] = 0;
        for(int n = 0; n < N; n++) {
            int day;
            cin >> day;
            days[day] = 2;
        }
        int pivot = 0;
        for(int p = 0; p < P; p++) {
            if(days[pivot] == 0) days[pivot] = 1;
            else p--;
            pivot++;
        }
        while(days[pivot] == 2) pivot++;

        int start = 0;
        int max = pivot - start;
        while(pivot < MAXDAY) {
            while(days[start] == 2) start++;
            start++;
            while(days[pivot] > 0) pivot++;
            days[pivot] = 1;
            while(days[pivot] > 0) pivot++;

            int tmp = pivot - start;
            if(tmp > max) max = tmp;
        }

        cout << '#' << tc << ' ' << max << "\n";
    }
}