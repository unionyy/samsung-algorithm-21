#include <iostream>
using namespace std;

#define MAX_N 100
#define MAX_K 1000

int items[MAX_N][2];
int dp[MAX_N][MAX_K + 1];
int N, K;

int Max(int a, int b) {return a > b ? a : b;}

int knapsack(int item, int capacity) {
    if(item == N) return 0;
    if(dp[item][capacity] >= 0) return dp[item][capacity];

    if(items[item][0] > capacity) return dp[item][capacity] = knapsack(item + 1, capacity);
    return dp[item][capacity] = Max(knapsack(item + 1, capacity), knapsack(item + 1, capacity - items[item][0]) + items[item][1]);
}

int main() {
    int T;
    freopen("input.txt", "r", stdin);
    cin >> T;
    for(int t = 0; t < T; t++) {
        N, K;
        cin >> N >> K;
        for(int n = 0; n < N; n++) {
            int v, c;
            cin >> v >> c;
            items[n][0] = v;
            items[n][1] = c;
            for(int k = 0; k <= K; k++) {
                dp[n][k] = -1;
            }
        }
        cout << '#' << t + 1 << ' ' << knapsack(0, K) << endl;
    }
}