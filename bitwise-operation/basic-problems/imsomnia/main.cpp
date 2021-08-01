#include<iostream>
using namespace std;

int main()
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        int check = 0;
        int CN = 0;

        cin >> N;

        while(true) {
            CN += N;

            int tmp = CN;

            while(tmp > 0) {
                check |= 1 << (tmp % 10);
                tmp /= 10;
            }

            if(check == (1 << 10) - 1) break;
        }

        cout << '#' << test_case << ' ' << CN << endl;
	}
	return 0;
}