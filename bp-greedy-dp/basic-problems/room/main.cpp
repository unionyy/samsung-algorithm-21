#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);

	cin>>T;

    int road[200];
	for(test_case = 1; test_case <= T; ++test_case)
	{
        for(int i = 0; i < 200; i++) road[i] = 0;

        int N;
        cin >> N;

        for(int i = 0; i < N; i++) {
            int a, b;
            cin >> a >> b;

            a--;
            b--;
            a /= 2;
            b /= 2;

            int small, big;
            if(a > b) {
                small = b;
                big = a;
            } else {
                small = a;
                big = b;
            }

            for(int j = small; j <= big; j++) road[j]++;
        }

        int max = 0;

        for(int i = 0; i < 200; i++) {
            if(road[i] > max) max = road[i];
        }

        cout << '#' << test_case << ' ' << max << endl;
	}
	return 0;
}