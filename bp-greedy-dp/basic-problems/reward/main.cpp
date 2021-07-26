#include<iostream>

using namespace std;

bool dp[720][10];
int numbers[720];
int nums[6];
int chn, N, Nfac;

void play(int idx, int left) {
    if(dp[idx][left]) return;
    dp[idx][left] = true;

    if(left == 0) return;

    for(int i = 1; i < N; i++) {
        for(int j = 0; j < i; j++) {
            int number = numbers[idx];
            int a = 1, b = 1;
            for(int k = 0; k < i; k++) a *= 10;
            for(int k = 0; k < j; k++) b *= 10;

            int aa, bb;

            aa = (number / a) % 10;
            bb = (number / b) % 10;

            number = number - (aa * a) - (bb * b) + (aa * b) + (bb * a);

            for(int k = 0; k < Nfac; k++) {
                if(numbers[k] == number) play(k, left - 1);
            }
        }
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int mny;
        cin >> mny >> chn;

        N = 0;
        while(mny > 0) {
            nums[N] = mny % 10;
            mny /= 10;
            N++;
        }
        Nfac = 1;
        for(int i = 2; i <= N; i++) Nfac *= i;
        for(int i = 0; i < Nfac; i++) {
            bool used[6] = {false, };
            int mul = 1;
            int idx = i;
            int number = 0;
            for(int j = N; j > 0; j--) {
                int tmp = idx % j;
                idx /= j;
                int pivot = 0;
                for(int k = 0; k < N; k++) {
                    if(used[k]) pivot--;
                    if(pivot == tmp) {
                        pivot = k;
                        break;
                    }
                    pivot++;
                }
                used[pivot] = true;
                number += nums[pivot] * mul;
                mul *= 10;
            }

            numbers[i] = number;

            for(int j = 0; j <= chn; j++) {
                dp[i][j] = false;
            }
        }

        play(0, chn);

        int max = 0;

        int ccnt = 0;
        for(int i = 0; i < Nfac; i++) {
            if(dp[i][0] && numbers[i] > max) max = numbers[i];
            
        }
        cout << '#' << test_case << ' ' << max << endl;
        
	}
	return 0;
}