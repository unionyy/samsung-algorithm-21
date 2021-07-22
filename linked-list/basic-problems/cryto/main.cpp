#include<iostream>
#define MAX_NODE 100000

using namespace std;

struct Node
{
    int data;
    Node* next;
} nodePool[MAX_NODE];

int nodeCnt;

Node* GetNode(int data) {
    nodePool[nodeCnt].data = data;
    nodePool[nodeCnt].next = nullptr;
    return &nodePool[nodeCnt++];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	T = 10;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        cin >> N;

        Node* head;
        nodeCnt = 0;
        head = GetNode(-1);

        Node* cNode = head;
        for(int i = 0; i < N; i++) {
            int num;
            cin >> num;

            cNode->next = GetNode(num);
            cNode = cNode->next;
        }

        int M;
        cin >> M;

        for(int i = 0; i < M; i++) {
            char cmd;
            cin >> cmd;

            if(cmd == 'I') {
                int x, y;
                cin >> x >> y;
                Node* pivot = head;
                for(int j = 0; j < x; j++) pivot = pivot->next;
                Node* tmp = pivot->next;
                for(int j = 0; j < y; j++) {
                    int s;
                    cin >> s;
                    pivot->next = GetNode(s);
                    pivot = pivot->next;
                }
                pivot->next = tmp;
            } else if(cmd == 'D') {
                int x, y;
                cin >> x >> y;
                Node* pivot = head;
                for(int j = 0; j < x; j++) pivot = pivot->next;
                Node* tmp = pivot;
                for(int j = 0; j < y; j++) pivot = pivot->next;
                tmp->next = pivot->next;
            } else {
                int y;
                cin >> y;
                Node* pivot = head;
                while(pivot->next) pivot = pivot->next;
                for(int j = 0; j < y; j++) {
                    int s;
                    cin >> s;
                    pivot->next = GetNode(s);
                    pivot = pivot->next;
                }

            }
        }

        cout << '#' << test_case;

        Node* pivot = head;
        for(int i = 0; i < 10; i++) {
            pivot = pivot->next;
            cout << ' ' << pivot->data;
        }

        cout << endl;

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}