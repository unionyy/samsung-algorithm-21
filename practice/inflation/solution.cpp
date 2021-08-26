#define MAXN 50
#define MAX_ANS 3000
#define PRICE_NUM 8
#define PRICE_SHIFT 50
#define MAX_NAME 20
#define HASH_SHIFT 18
#define HASH_SIZE (1 << HASH_SHIFT)

typedef long long ll;

void priceCpy(ll dst[], const ll src[]) {
	for (int i = 0; i < PRICE_NUM; i++) dst[i] = src[i];
}

void mMul(ll dst[], int a) {
	for (int i = 0; i < PRICE_NUM; i++) dst[i] *= a;
	for (int i = 0; i < PRICE_NUM - 1; i++) {
		dst[i + 1] += dst[i] >> PRICE_SHIFT;
		dst[i] &= ((ll)1 << PRICE_SHIFT) - 1;
	}
}

bool mSub(ll dst[], const ll src[]) {
	for (int i = 0; i < PRICE_NUM - 1; i++) {
		dst[i] -= src[i];
		if (dst[i] < 0) {
			dst[i] += (ll) 1 << PRICE_SHIFT;
			dst[i + 1]--;
		}
	}
	if (dst[PRICE_NUM - 1] >= src[PRICE_NUM - 1]) return true;
	else return false;
}

void makePrice(ll dst[], const char src[]) {
	for (int i = 0; i < PRICE_NUM; i++) dst[i] = 0;
	while (*src) {
		mMul(dst, 10);
		int num = *src - '0';
		src++;
		dst[0] += num;
	}
	mMul(dst, 1);
}

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != 0) ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

struct Product {
	ll price[PRICE_NUM];
	int duration;
	char name[MAX_NAME];
	Product *next;

	Product* Alloc(const char _price[], int _duration, const char _name[], Product *_next) {
		makePrice(price, _price);
		duration = _duration;
		mstrcpy(name, _name);
		next = _next;
		return this;
	}
}products[MAXN];

Product *hashTable[HASH_SIZE];

int getHash(char *a) {
	unsigned long long hash = 5381;
	while (*a) {
		hash = (hash << 5) + hash + *a - 'a' + 1;
		a++;
	}
	return hash & (HASH_SIZE - 1);
}

int N;

void init(int _N, char mName[50][20], char mPrice[50][100], int mDuration[50])
{
	for (int i = 0; i < HASH_SIZE; i++) hashTable[i] = nullptr;

	N = _N;
	for (int i = 0; i < N; i++) {
		int hash = getHash(mName[i]);
		hashTable[hash] = products[i].Alloc(mPrice[i], mDuration[i], mName[i], hashTable[hash]);
	}
}

void priceChange(char mName[20], char mPrice[100])
{
	int hash = getHash(mName);
	Product *pivot = hashTable[hash];
	while (mstrcmp(pivot->name, mName) != 0) {
		pivot = pivot->next;
	}
	makePrice(pivot->price, mPrice);
}

int daySurvivable(char mMoney[100])
{
	ll money[PRICE_NUM];
	makePrice(money, mMoney);
	int l = 0;
	int r = MAX_ANS;
	int ans = 0;
	while (l < r) {
		int m = (l + r) / 2;
		bool pos = true;
		ll tmon[PRICE_NUM];
		priceCpy(tmon, money);
		for (int i = 0; i < N; i++) {
			int mul = (m / products[i].duration);
			if (m % products[i].duration) mul++;
			ll sub[PRICE_NUM];
			priceCpy(sub, products[i].price);
			mMul(sub, mul);
			if (!mSub(tmon, sub)) {
				pos = false;
				break;
			}
		}
		if (pos) {
			ans = m;
			l = m + 1;
		}
		else {
			r = m;
		}
	}
	return ans;
}