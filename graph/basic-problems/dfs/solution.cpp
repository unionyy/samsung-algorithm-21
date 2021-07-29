int children[100][5];

void dfs_init(int N, int path[100][2])
{
    for(int n = 0; n < 100; n++) {
        for(int i = 0; i < 5; i++) {
            children[n][i] = -1;
        }
    }
    for(int n = 0; n < N - 1; n++) {
        int i = 0;
        while(children[path[n][0]][i] > 0) i++;
        children[path[n][0]][i] = path[n][1];
    }
}

int MyDFS(int n, int king) {
    if(n > king || n == -1) return n;
    for(int i = 0; i < 5; i++) {
        int a = MyDFS(children[n][i], king);
        if(a > 0) return a;
    }
    return -1;
}

int dfs(int n)
{
	return MyDFS(n, n);
}
