int map[10][10];
int mapB[10][10];
int N;

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

struct QNode {
    QNode* next;
    int x;
    int y;
    int dist;
    QNode(int _x, int _y, int _dist, QNode* _next): x(_x), y(_y), dist(_dist), next(_next){}
};

void bfs_init(int _N, int _map[10][10]) {
    N = _N;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            map[i][j] = _map[i][j];
}

int bfs(int y1, int x1, int y2, int x2) {
    x1--;
    y1--;
    x2--;
    y2--;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            mapB[i][j] = map[i][j];
    QNode *head = new QNode(x1, y1, 0, nullptr);
    QNode *tail = head;

    while(head) {
        int x = head->x;
        int y = head->y;
        int dist = head->dist;
        if(x == x2 && y == y2) return dist;
        mapB[x][y] = 2;
        for(int i = 0; i < 4; i++) {
            if(x+dx[i] >= N || x+dx[i] < 0 || y+dy[i] < 0 || y+dy[i] >= N) continue;
            if(mapB[x+dx[i]][y+dy[i]] == 0) {
                tail->next = new QNode(x+dx[i], y+dy[i], dist+1, nullptr);
                tail = tail->next;
            }
        }
        QNode* tmp = head->next;
        delete(head);
        head = tmp;
    }
    return -1;
}