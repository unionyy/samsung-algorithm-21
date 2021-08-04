#include <iostream>
using namespace std;

#define MAXN 200000

int N;

int maxHeap[MAXN + 2];
int minHeap[MAXN + 1];

int maxCnt, minCnt;

void AddMax(int val) {
    int pivot = maxCnt;
    maxHeap[maxCnt++] = val;
    
    while(pivot > 0) {
        int ppivot = pivot;
        pivot = pivot - 1 >> 1;
        if(maxHeap[pivot] < val) {
            maxHeap[ppivot] = maxHeap[pivot];
            maxHeap[pivot] = val;
        } else return;
    }
}

void AddMin(int val) {
    int pivot = minCnt;
    minHeap[minCnt++] = val;
    
    while(pivot > 0) {
        int ppivot = pivot;
        pivot = pivot - 1 >> 1;
        if(minHeap[pivot] > val) {
            minHeap[ppivot] = minHeap[pivot];
            minHeap[pivot] = val;
        } else return;
    }
}

int PopMax() {
    int val = maxHeap[0];
    maxHeap[0] = maxHeap[--maxCnt];

    int pivot = 0;
    while(true) {
        int ppivot = pivot;
        pivot = (pivot << 1) + 1;

        if(maxCnt <= pivot) break;
        if(maxCnt == pivot + 1) {
            if(maxHeap[pivot] > maxHeap[ppivot]) {
                int tmp = maxHeap[pivot];
                maxHeap[pivot] = maxHeap[ppivot];
                maxHeap[ppivot] = tmp;
            } else break;
        } else {
            if(maxHeap[pivot] < maxHeap[pivot + 1]) pivot++;
            if(maxHeap[pivot] > maxHeap[ppivot]) {
                int tmp = maxHeap[pivot];
                maxHeap[pivot] = maxHeap[ppivot];
                maxHeap[ppivot] = tmp;
            } else break;
        }
    }
    return val;
}

int PopMin() {
    int val = minHeap[0];
    minHeap[0] = minHeap[--minCnt];

    int pivot = 0;
    while(true) {
        int ppivot = pivot;
        pivot = (pivot << 1) + 1;

        if(minCnt <= pivot) break;
        if(minCnt == pivot + 1) {
            if(minHeap[pivot] < minHeap[ppivot]) {
                int tmp = minHeap[pivot];
                minHeap[pivot] = minHeap[ppivot];
                minHeap[ppivot] = tmp;
            } else break;
        } else {
            if(minHeap[pivot] > minHeap[pivot + 1]) pivot++;
            if(minHeap[pivot] < minHeap[ppivot]) {
                int tmp = minHeap[pivot];
                minHeap[pivot] = minHeap[ppivot];
                minHeap[ppivot] = tmp;
            } else break;
        }
    }
    return val;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for(int tc = 1; tc <=T; tc++) {
        int A;
        cin >> N >> A;
        maxCnt = minCnt = 0;
        AddMax(A);
        int sum = 0;
        for(int n = 0; n < N; n++) {
            int X, Y;
            cin >> X >> Y;
            if(X > maxHeap[0]) AddMin(X);
            else AddMax(X);
            if(Y > maxHeap[0]) AddMin(Y);
            else AddMax(Y);
            if(maxCnt < minCnt) AddMax(PopMin());
            else if(maxCnt - 1 > minCnt) AddMin(PopMax());
            sum += maxHeap[0];
            if(sum >= 20171109) sum %= 20171109;
        }
        cout << '#' << tc << ' ' << sum << '\n';
    }
}