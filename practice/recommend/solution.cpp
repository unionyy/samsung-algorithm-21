//#include <stdio.h>

#define MAXN 10001
#define MAXE 1000001
#define BUCKET_SIZE 64
#define BUCKET_SHIFT 6


struct Edge {
	int end;
	Edge* next;

	Edge* Alloc(int _end, Edge* _next) {
		end = _end;
		next = _next;

		return this;
	}
}edges[MAXE];
int edgeCnt;

struct Node {
	Edge edges[(MAXN >> BUCKET_SHIFT) + 1];
} nodes[MAXN];

int N;

int check[MAXN];

//void showFriends() {
//	for (int n = 0; n < N; n++) {
//		printf("%d: ", n);
//		Edge* pivot = &nodes[n].edges[0];
//		while (pivot->next) {
//			if (pivot->next->end != -1) printf("%d ", pivot->next->end);
//			pivot = pivot->next;
//		}
//		printf("\n");
//	}
//}


void init(int _N) {
	edgeCnt = 0;
	N = _N + 1;
	for (int n = 1; n < N; n++) {
		for (int i = 0; i < (N >> BUCKET_SHIFT) + 1; i++) {
			if(i == (N >> BUCKET_SHIFT)) nodes[n].edges[i].Alloc(-1, nullptr);
			else nodes[n].edges[i].Alloc(-1, &nodes[n].edges[i + 1]);
		}
	}

	return;
}

void add(int id, int F, int ids[]) {
	int bnum = id >> BUCKET_SHIFT;
	
	for (int i = 0; i < F; i++) {
		int fbnum = ids[i] >> BUCKET_SHIFT;
		nodes[id].edges[fbnum].next = edges[edgeCnt++].Alloc(ids[i], nodes[id].edges[fbnum].next);
		nodes[ids[i]].edges[bnum].next = edges[edgeCnt++].Alloc(id, nodes[ids[i]].edges[bnum].next);
	}

	return;
}

void del(int id1, int id2) {
	int bnum1 = id1 >> BUCKET_SHIFT;
	int bnum2 = id2 >> BUCKET_SHIFT;

	Edge* pivot = &nodes[id1].edges[bnum2];
	while (true) {
		if (pivot->next->end == id2) break;
		pivot = pivot->next;
	}
	pivot->next = pivot->next->next;

	pivot = &nodes[id2].edges[bnum1];
	while (true) {
		if (pivot->next->end == id1) break;
		pivot = pivot->next;
	}
	pivot->next = pivot->next->next;

	return;
}

int recommend(int id, int list[]) {
	for (int n = 1; n < N; n++) {
		check[n] = 0;
	}
	check[id] = -1;

	Edge* pivot = &nodes[id].edges[0];

	while (pivot->next) {
		if (pivot->next->end != -1) {
			check[pivot->next->end] = -1;
			Edge* pivot2 = &nodes[pivot->next->end].edges[0];
			while (pivot2->next) {
				if (pivot2->next->end != -1) {
					if (check[pivot2->next->end] != -1) check[pivot2->next->end]++;
				}
				pivot2 = pivot2->next;
			}
		}
		pivot = pivot->next;
	}

	int max[5] = { 0, };
	for (int n = 1; n < N; n++) {
		int c = check[n];
		if (c > max[4]) { 
			max[4] = c;
			list[4] = n;
		}
		for (int i = 4; i > 0; i--) {
			if (max[i] > max[i - 1]) {
				int tmp = max[i];
				max[i] = max[i - 1];
				max[i - 1] = tmp;
				tmp = list[i];
				list[i] = list[i - 1];
				list[i - 1] = tmp;
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < 5; i++) {
		if (max[i] > 0) cnt++;
	}

	return cnt;
}