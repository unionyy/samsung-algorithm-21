#define MAXN 100000

struct Node {
    int uid;
    int income;
} top[11];

void init()
{
    for(int i = 0; i < 11; i++) top[i].income = -1;
}

void addUser(int uid, int income) 
{
    top[10].uid = uid;
    top[10].income = income;
    for(int i = 0; i < 10; i++) {
        if(income > top[9 - i].income) {
            Node tmp = top[9 - i];
            top[9 - i] = top[10 - i];
            top[10 - i] = tmp;
        } else break;
    }
    if(top[10].income == -1) return;


}

int getTop10(int result[10]) 
{
    int cnt = 0;
    for(int i = 0; i < 10; i++) {
        if(top[i].income == -1) break;
        cnt++;
        result[i] = top[i].uid;
    }
    return cnt;
}