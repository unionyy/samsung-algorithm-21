#define MAX_N 1000
#define MAX_M 20
#define MAX_STAR 20000

struct Result {
	int y, x;
};

int N, M;
int map[MAX_N][MAX_N];
int xx[MAX_STAR];
int yy[MAX_STAR];
int star;

void init(int n, int m, int Map[MAX_N][MAX_N])
{
	N = n;
	M = m;
    star = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			map[i][j] = Map[i][j];
            if(map[i][j] == 1) {
                xx[star] = i;
                yy[star] = j;
                star++;
            }
		}
	}
}

Result findConstellation(int stars[MAX_M][MAX_M])
{
	Result res;

	int xs[19];
	int ys[19];
	int x9, y9;
	int snum = 0;

	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			if(stars[i][j] == 1) {
				xs[snum] = i;
				ys[snum] = j;
				snum++;
			} else if(stars[i][j] == 9) {
				x9 = i;
				y9 = j;
			}
		}
	}

	for (int rot = 0; rot < 4; rot++)
	{
        for (int pivot = 0; pivot < star; pivot++) {
            if(xx[pivot] == -1) {
                continue;
            } else if(map[xx[pivot]][yy[pivot]] == 0) {
                xx[pivot] = -1;
                yy[pivot] = -1;
                continue;
            }
            int pivotX = xx[pivot] - x9;
            int pivotY = yy[pivot] - y9;

            if(pivotX < 0 || pivotX >= N || pivotY < 0 || pivotY >=N) continue;

            for (int i = 0; i < snum; i++)
				{
					if (map[pivotX + xs[i]][pivotY + ys[i]] == 0)
					{
						break;
					}
					else if (i == snum - 1)
					{
						res.y = pivotX + x9;
						res.x = pivotY + y9;

                        xx[pivot] = -1;
                        yy[pivot] = -1;

                        for(int j = 0; j < snum; j++) {
                            map[pivotX + xs[i]][pivotY + ys[i]] = 0;
                        }
                        map[pivotX + x9][pivotY + y9] = 0;

						return res;
					}
				}
        }

		// for (int pivotX = 0; pivotX < N - M + 1; pivotX++)
		// {
		// 	for (int pivotY = 0; pivotY < N - M + 1; pivotY++)
		// 	{
		// 		for (int i = 0; i < snum; i++)
		// 		{
		// 			if (map[pivotX + xs[i]][pivotY + ys[i]] == 0)
		// 			{
		// 				break;
		// 			}
		// 			else if (i == snum - 1)
		// 			{
		// 				if (map[pivotX + x9][pivotY + y9] == 1)
		// 				{
		// 					res.y = pivotX + x9;
		// 					res.x = pivotY + y9;

		// 					return res;
		// 				}
		// 			}
		// 		}
		// 	}
		// }

		// Rotation
		for (int i = 0; i < snum; i++)
		{
			int tmp = xs[i];
			xs[i] = ys[i];
			ys[i] = M - tmp - 1;
		}
		int tmp = x9;
		x9 = y9;
		y9 = M - tmp - 1;
	}

	res.y = res.x = 0;
	return res;
}