#define MAX_USER 1000
#define MAX_AREA 10
#define MAX_FRIENDS 20
#define MAX_ADD 40001
#define HASH_SIZE 100003

struct User {
	int uid;
	int friends[MAX_FRIENDS];
	int friendCnt;
	int area[MAX_AREA];

	void Init(int _uid) {
		uid = _uid;
		for (int i = 0; i < MAX_FRIENDS; i++) friends[i] = -1;
		friendCnt = 0;
		for (int i = 0; i < MAX_AREA; i++) area[i] = 0;
		return;
	}
} users[MAX_USER];
int N;

struct Product {
	int pid, price, area;
	bool reserved;
	Product *next;

	Product* Alloc(int _pid, int _price, int _area, Product *_next) {
		pid = _pid;
		price = _price;
		area = _area;
		reserved = false;
		next = _next;
		return this;
	}
} products[MAX_ADD];
int productCnt;

Product hashTable[HASH_SIZE];

Product *areas[MAX_AREA][MAX_ADD];
int areaCnt[MAX_AREA];
int M;

bool productCmp(Product* a, Product* b) {
	if (a->price > b->price) return false;
	else if (a->price < b->price) return true;
	if (a->pid > b->pid) return false;
	else return true;
}

void switchProducts(int area, int a, int b) {
	Product* tmp = areas[area][a];
	areas[area][a] = areas[area][b];
	areas[area][b] = tmp;
	return;
}

void addHeap(Product *area[], int num) {
	int pivot = num - 1;
	while (pivot > 0) {
		int parent = (pivot - 1) / 2;
		if (productCmp(area[parent], area[pivot])) break;
		else {
			Product *tmp = area[parent];
			area[parent] = area[pivot];
			area[pivot] = tmp;
			pivot = parent;
		}
	}
	return;
}

void popHeap(int area) {
	int num = areaCnt[area] - 1;
	areaCnt[area]--;
	areas[area][0] = areas[area][num];
	int pivot = 0;
	while (pivot * 2 + 1 < num) {
		int left = pivot * 2 + 1;
		int right = pivot * 2 + 2;

		if (right == num) {
			if(!productCmp(areas[area][pivot], areas[area][left]))
				switchProducts(area, pivot, left);
			break;
		}

		if (productCmp(areas[area][left], areas[area][right])) right = left;
		if (!productCmp(areas[area][right], areas[area][pivot])) break;
		switchProducts(area, right, pivot);
		pivot = right;
	}

	return;
}

//#include <stdio.h>
//void showProducts() {
//	printf("products\n");
//	for (int i = 0; i < M; i++) {
//		printf("Area %d: ", i);
//		for (int j = 0; j < areaCnt[i]; j++) {
//			printf("%d ", areas[i][j]->pid);
//		}
//		printf("\n");
//	}
//	return;
//}

void init(int _N, int _M) {
	N = _N;
	M = _M;
	productCnt = 0;
	for (int n = 0; n < N; n++) users[n].Init(n);
	for (int m = 0; m < M; m++) areaCnt[m] = 0;

	for (int i = 0; i < HASH_SIZE; i++) hashTable[i].Alloc(-1, -1, -1, nullptr);

	return;
}

void befriend(int uid1, int uid2) {
	uid1--; uid2--;
	users[uid1].friends[users[uid1].friendCnt] = uid2;
	users[uid1].friendCnt++;
	users[uid2].friends[users[uid2].friendCnt] = uid1;
	users[uid2].friendCnt++;

	return;
}

void add(int pid, int area, int price) {
	area--;
	int hash = pid % HASH_SIZE;
	Product *product = products[productCnt++].Alloc(pid, price, area, hashTable[hash].next);
	hashTable[hash].next = product;
	areas[area][areaCnt[area]] = product;
	areaCnt[area]++;
	addHeap(areas[area], areaCnt[area]);

	return;
}

void reserve(int uid, int pid) {
	uid--;
	int hash = pid % HASH_SIZE;
	Product *pivot = &hashTable[hash];
	while (true) {
		if (pivot->next->pid == pid) break;
		else pivot = pivot->next;
	}
	users[uid].area[pivot->next->area]++;
	pivot->next->reserved = true;
	pivot->next = pivot->next->next;

	return;
}

int recommend(int uid) {
	uid--;
	int check[10] = { 0, };
	for (int i = 0; i < M; i++) {
		check[i] += users[uid].area[i];
	}
	for (int i = 0; i < users[uid].friendCnt; i++) {
		for (int j = 0; j < M; j++) {
			check[j] += users[users[uid].friends[i]].area[j];
		}
	}

	while (true) {
		int max = 0;
		for (int i = 0; i < M; i++) {
			if (max < check[i]) max = check[i];
		}
		int maxAreas[10];
		int maxCnt = 0;
		for (int i = 0; i < M; i++) {
			if (max == check[i]) {
				maxAreas[maxCnt++] = i;
				check[i] = -1;
			}
		}
		int recomArea = -1;
		for (int i = 0; i < maxCnt; i++) {
			int area = maxAreas[i];
			Product *product = areas[area][0];
			while (areaCnt[area] > 0 && areas[area][0]->reserved) {
				popHeap(area);
			}
			if (areaCnt[area] == 0) continue;
			else {
				if (recomArea == -1) recomArea = area;
				else {
					if (productCmp(areas[area][0], areas[recomArea][0])) {
						recomArea = area;
					}
				}
			}
		}
		if (recomArea != -1) {
			int ret = areas[recomArea][0]->pid;
			return ret;
		}
	}
}