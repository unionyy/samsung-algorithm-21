#include <iostream>
using namespace std;

char names[20000][51];
int sizes[20000];
int idxArr[20000];

int Compare(int aa, int bb) {
    int idxA = idxArr[aa];
    int idxB = idxArr[bb];

    if(idxB == -1) return 0;
    else if(idxA == -1) return 1;

    char *a = names[idxA];
    char *b = names[idxB];
    int sizeA = sizes[idxA];
    int sizeB = sizes[idxB];
    if(sizeA < sizeB) return 0;
    else if(sizeB < sizeA) return 1;
    for(int i = 0; i < sizeA; i++) {
        if(a[i] < b[i]) return 0;
        else if(b[i] < a[i]) return 1;
    }
    idxArr[bb] = -1;
    return 0;
}

void Swap(int a, int b) {
    int tmp = idxArr[a];
    idxArr[a] = idxArr[b];
    idxArr[b] = tmp;
    return;
}

void QuickSort(int l, int r) {
    if(l >= r) return;
    int m = (l + r) / 2;
    int pivotL = l;
    int pivotR = r;
    while(true) {
        while(pivotL < m) {
            int cmp = Compare(pivotL, m);
            if(cmp == 1) break;
            pivotL++;
        }
        while(pivotR > m) {
            int cmp = Compare(m, pivotR);
            if(cmp == 1) break;
            pivotR--;
        }
        if(pivotL == pivotR) break;
        if(pivotL == m) m = pivotR;
        else if(pivotR == m) m = pivotL;
        Swap(pivotL, pivotR);
    }
    QuickSort(l, m - 1);
    QuickSort(m + 1, r);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("s_input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        for(int n = 0; n < N; n++) {
            cin >> names[n];
            int size = 0;
            while(names[n][size]) size++;
            sizes[n] = size;
            idxArr[n] = n;
        }
        QuickSort(0, N - 1);

        cout << '#' << tc << endl;
        for(int n = 0; n < N; n++) {
            if(idxArr[n] == -1) continue;
            cout << names[idxArr[n]] << endl;
        }
    }
    return 0;
}