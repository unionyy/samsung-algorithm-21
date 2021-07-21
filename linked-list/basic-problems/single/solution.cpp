#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    head.next = nullptr;
    nodeCnt = 0;
}

void addNode2Head(int data) 
{
    Node* cnode = getNode(data);
    cnode->next = head.next;
    head.next = cnode;

    return;
}

void addNode2Tail(int data) 
{
    Node* cnode = &head;
    while(cnode->next) cnode = cnode->next;
    cnode->next = getNode(data);

    return;
}

void addNode2Num(int data, int num) 
{
    Node* cnode = &head;
    for(int i = 1; i < num; i++) cnode = cnode->next;
    Node* nnode = getNode(data);
    nnode->next = cnode->next;
    cnode->next = nnode;

    return;
}

void removeNode(int data) 
{
    Node* cnode = &head;
    while(cnode->next) {
        if(cnode->next->data == data) {
            cnode->next = cnode->next->next;
            break;
        } else {
            cnode = cnode->next;
        }
    }
}

int getList(int output[MAX_NODE]) 
{
    Node* cnode = &head;
    int cnt = 0;
    while(cnode->next) {
        cnode = cnode->next;
        output[cnt] = cnode->data;
        cnt++;
    }

    return cnt;
}