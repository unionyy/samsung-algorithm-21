#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{

}

void addNode2Head(int data) 
{

}

void addNode2Tail(int data) 
{

}

void addNode2Num(int data, int num) 
{

}

void removeNode(int data) 
{

}

int getList(int output[MAX_NODE]) 
{

}