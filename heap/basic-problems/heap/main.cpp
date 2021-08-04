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
        pivot >> 1;
        if(heap[pivot] < heap[ppivot]) {
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
        if((pivot << 1) + 2 > heapCnt) {
            break;
        } else if((pivot << 1) + 2 == heapCnt) {
            int tmp = heap[pivot];
            heap[pivot] = heap[(pivot << 1) + 1];
            heap[pivot << 1 + 1] = tmp;
            break;
        } else {
            int pivot2 = (heap[(pivot << 1) + 1] > heap[(pivot << 1) + 2]) ? (pivot << 1) + 1 : (pivot << 1) + 2;
            int tmp = heap[pivot];
            heap[pivot] = heap[pivot2];
            heap[pivot2] = tmp;
            pivot = pivot2;
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