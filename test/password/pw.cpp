#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <windows.h>

#define N              4
#define MAX_QUERYCOUNT 1000000

static int digits[N];
static int digits_c[10];

static int T;

extern void doUserImplementation(int guess[]);

static int querycount; 

// the value of limit_query will be changed in evaluation
static const int limit_query = 234;

typedef struct {
	int hit;
	int miss;
} Result;

static bool isValid(int guess[]) {
	int guess_c[10];
	
	for (int count = 0; count < 10; ++count) guess_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		if (guess[idx] < 0 || guess[idx] >= 10 || guess_c[guess[idx]] > 0) return false;
		guess_c[guess[idx]]++;
	}
	return true;
}

// API : return a result for comparison with digits[] and guess[]
Result query(int guess[]) {
	Result result;
	
	if (querycount >= MAX_QUERYCOUNT) {
		result.hit = -1;
		result.miss = -1;
		return result;
	}
	
    querycount++;
		
	if (!isValid(guess)) {
		result.hit = -1;
		result.miss = -1;
		return result;
	}
	
	result.hit = 0;
	result.miss = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.hit++;
		else if (digits_c[guess[idx]] > 0)
			result.miss++;

	return result;
}

static void initialize() {
	for (int count = 0; count < 10; ++count) digits_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		char c;
		do scanf("%c", &c); while(c < '0' || c > '9');
		digits[idx] = c - '0';
		digits_c[digits[idx]]++;
	}
	
	querycount = 0;
}

static bool check(int guess[]) {
	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] != digits[idx]) return false;
	return true;
}

int main() {
	int total_score = 0;
	int total_querycount = 0;;
	
    // freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T);
    for (int testcase = 1; testcase <= T; ++testcase) {
        initialize();

        int guess[N];
		doUserImplementation(guess);

		if (!check(guess)) querycount = MAX_QUERYCOUNT;
        if (querycount <= limit_query) total_score++;
		printf("#%d %d\n", testcase, querycount);
		total_querycount += querycount;
    }
	if (total_querycount > MAX_QUERYCOUNT) total_querycount = MAX_QUERYCOUNT;
	printf("total score = %d\ntotal query = %d\n", total_score * 100 / T, total_querycount);
	return 0;
}

// MY CODE

#define N 4


struct gNode {
	int digits[N];
	gNode* next;
};
 
// API
extern Result query(int guess[]);

typedef struct ResultPair {
	int digits[N];
	int hit;
	int miss;
} RPair;

Result query2(int guess[], int digits[]) {
	Result result;
	int digits_cc[10] = {0, };

	for (int idx = 0; idx < N; ++idx) {
		digits_cc[digits[idx]]++;
	}
	
	result.hit = 0;
	result.miss = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.hit++;
		else if (digits_cc[guess[idx]] > 0)
			result.miss++;

	return result;
}

void doUserImplementation(int guess[])
{
	// Implement a user's implementation function
	//
	// The array of guess[] is a return array that
	// is your guess for what digits[] would be.

	gNode *sNode;

	int MAX = 1;
	for (int i = 0; i < N; i++)
	{
		MAX *= 10;
	}

	for (int i = 0; i < MAX; i++)
	{
		gNode *cNode = new gNode;
		int num = i;
		bool valid = true;
		for (int j = 0; j < N; j++)
		{
			cNode->digits[j] = num % 10;
			for (int k = 0; k < j; k++)
			{
				if (cNode->digits[k] == cNode->digits[j])
				{
					valid = false;
					break;
				}
			}
			if (!valid)
				break;
			num /= 10;
		}

		if (valid)
		{
			cNode->next = sNode;
			sNode = cNode;
		}
	}

	RPair rPool[20];
	int cnt = 0;

	while(sNode) {
		for(int i = 0; i < cnt; i++) {
			Result chk = query2(sNode->digits, rPool[i].digits);
			if(chk.hit != rPool[i].hit || chk.miss != rPool[i].miss) {
				sNode = sNode->next;
				i = -1;
				continue;
			}
		}

		printf("%d%d%d%d\n", sNode->digits[0], sNode->digits[1], sNode->digits[2], sNode->digits[3]);
		Sleep(1000);

		Result rst = query(sNode->digits);

		if(rst.hit == 4) {
			for(int i = 0; i < N; i++) {
				guess[i] = sNode->digits[i];
			}
			printf("YES\n");
			return;
		} else {
			RPair rPair;
			for(int i = 0; i < N; i++) {
				rPool[cnt].digits[i] = sNode->digits[i];
			}
			rPool[cnt].hit = rst.hit;
			rPool[cnt].miss = rst.miss;
			sNode = sNode->next;
			cnt++;
		}
	}


}
