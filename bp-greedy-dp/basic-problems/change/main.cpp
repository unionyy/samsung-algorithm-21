#include<iostream>

using namespace std;

#define COIN_NUM 8

const int COIN[COIN_NUM] {50000, 10000, 5000, 1000, 500, 100, 50, 10};

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        cin >> N;

        cout << "#" << test_case << endl;

        for(int i = 0; i < COIN_NUM; i++) {
            int coin = COIN[i];
            int cnt = 0;

            while(N >= coin) {
                N -= coin;
                cnt++;
            }

            cout << cnt << ' ';
        }

        cout << endl;
	}
	return 0;
}