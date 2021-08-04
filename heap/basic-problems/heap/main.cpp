#include <iostream>
using namespace std;

#define MAXN 100000

int heap[MAXN];
int heapCnt;

void Add(int val) {
    int pivot = heapCnt;
    heap[heapCnt++] = val;
    while(pivot > 0) {
        int ppivot = pivot;
        pivot--;
        pivot = pivot >> 1;
        if(heap[pivot] < val) {
            heap[ppivot] = heap[pivot];
            heap[pivot] = val;
        } else return;
    }
    return;
}
int Pop() {
    if(heapCnt == 0) return -1;
    int val = heap[0];
    heapCnt--;
    heap[0] = heap[heapCnt];
    int pivot = 0;
    while(true) {
        int ppivot = pivot;
        pivot = pivot << 1;
        pivot++;
        if(pivot >= heapCnt) {
            break;
        } else if(pivot + 1 == heapCnt) {
            if(heap[ppivot] > heap[pivot]) break;
            int tmp = heap[ppivot];
            heap[ppivot] = heap[pivot];
            heap[pivot] = tmp;
            break;
        } else {
            if(heap[pivot] < heap[pivot + 1]) pivot++;
            if(heap[ppivot] > heap[pivot]) break;
            int tmp = heap[pivot];
            heap[pivot] = heap[ppivot];
            heap[ppivot] = tmp;
        }
    }
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cout << '#' << tc << ' ';
        heapCnt = 0;
        int N;
        cin >> N;
        for(int n = 0; n < N; n++) {
            int act;
            cin >> act;
            if(act == 1) {
                int num;
                cin >> num;
                Add(num);
            } else {
                cout << Pop() << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}