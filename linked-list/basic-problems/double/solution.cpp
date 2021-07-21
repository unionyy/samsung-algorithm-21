#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head = getNode(0);
    head->prev = nullptr;
    head->next = nullptr;
}

void addNode2Head(int data) 
{
    Node* cNode = getNode(data);
    cNode->next = head->next;
    if(cNode->next) cNode->next->prev = cNode;
    cNode->prev = head;
    head->next = cNode;

    return;
}

void addNode2Tail(int data) 
{
    Node* cNode = getNode(data);
    Node* pivot = head;
    while(pivot->next) pivot = pivot->next;
    cNode->prev = pivot;
    pivot->next = cNode;

    return;
}

void addNode2Num(int data, int num) 
{
    Node* cNode = getNode(data);
    Node* pivot = head;
    for(int i = 1; i < num; i++) pivot = pivot->next;
    cNode->next = pivot->next;
    if(cNode->next) cNode->next->prev = cNode;
    cNode->prev = pivot;
    cNode->prev->next = cNode;

    return;
}

int findNode(int data) 
{
    Node* pivot = head;
    int cnt = 1;
    while(pivot->next) {
        if(pivot->next->data == data) break;
        pivot = pivot->next;
        cnt++;
    }

    return cnt;
}

void removeNode(int data) 
{
    Node* pivot = head;
    while(pivot->next) {
        if(pivot->next->data == data) break;
        pivot = pivot->next;
    }
    if(pivot->next == nullptr) return; // Not exist
    pivot->next = pivot->next->next;
    if(pivot->next) {
        pivot->next->prev = pivot;
    }
    
    return;
}

int getList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* pivot = head;
    while(pivot->next) {
        output[cnt] = pivot->next->data;
        pivot = pivot->next;
        cnt++;
    }

    return cnt;
}

int getReversedList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* pivot = head;
    while(pivot->next) pivot = pivot->next;
    while(pivot->prev) {
        output[cnt] = pivot->data;
        pivot = pivot->prev;
        cnt++;
    }
    return cnt;
}