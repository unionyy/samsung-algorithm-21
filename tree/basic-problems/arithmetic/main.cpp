#include <iostream>
using namespace std;

#define MAXN 1000

int N;

struct Node {
    bool isNum;
    int num;
    int children[2];
} nodes[MAXN];

double Calc(int idx) {
    if(nodes[idx].isNum) return (double) nodes[idx].num;
    double c1 = Calc(nodes[idx].children[0]);
    double c2 = Calc(nodes[idx].children[1]);
    switch(nodes[idx].num) {
        case '+': return c1 + c2;
        case '-': return c1 - c2;
        case '*': return c1 * c2;
        case '/': return c1 / c2;
        default : return -1;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    for(int tc = 1; tc <=10; tc++) {
        cin >> N;
        for(int n = 0; n < N; n++) {
            int idx;
            cin >> idx;
            idx--;
            char str[10];
            cin >> str;
            if(str[0] >= '0' && str[0] <= '9') {
                nodes[idx].isNum = true;
                int num = 0;
                for(int i = 0; str[i]; i++) {
                    num *= 10;
                    num += str[i] - '0';
                }
                nodes[idx].num = num;
            } else {
                nodes[idx].isNum = false;
                int num = str[0];
                int c1, c2;
                cin >> c1 >> c2;
                c1--;c2--;
                nodes[idx].num = num;
                nodes[idx].children[0] = c1;
                nodes[idx].children[1] = c2;
            }
        }
        cout << '#' << tc << ' ' << Calc(0) << '\n';
    }
    
    return 0;
}