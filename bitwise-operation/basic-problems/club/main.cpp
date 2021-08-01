#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        char chiefs[10000];
        int pivot = 0;
        int *counts = new int[16];

        cin >> chiefs;

        for(int i = 0; i < 16; i++) counts[i] = 0;

        counts[1]++;

        while(chiefs[pivot]) {
            int *newCnts = new int[16];
            for(int i = 0; i < 16; i++) newCnts[i] = 0;

            int chief = chiefs[pivot] - 'A';

            for(int i = 0; i < 16; i++) {
                if(!(i & 1 << chief)) continue;

                long long cnt = 0;
                for(int j = 0; j < 16; j++) {
                    if(!(j & i)) continue;

                    cnt += counts[j];

                    if(cnt > 1000000007) cnt %= 1000000007;
                }
                
                newCnts[i] = cnt;
            }

            delete counts;
            counts = newCnts;
            
            pivot++;
        }

        int sum = 0;
        for(int i = 0; i < 16; i++) {
            sum += counts[i];
            if(sum > 1000000007) sum %= 1000000007;
        }

        delete counts;

        cout << '#' << test_case << ' ' << sum << endl;
	}
	return 0;
}