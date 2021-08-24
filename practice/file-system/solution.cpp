#define MAX_CALL 10000
#define MAX_USER 20
#define MAX_GROUP 10
#define MAX_DEPTH 50

typedef unsigned long long int ll;

struct Group {
    int idx;
    ll name;

    Group* Alloc(int _idx, ll _name) {
        idx = _idx;
        name = _name;
        return this;
    }
} groups[MAX_GROUP];
int groupCnt;

struct User {
    int idx;
    ll name;
    int groupIdx;

    User* Alloc(int _idx, ll _name, ll groupName) {
        idx = _idx;
        name = _name;

        for(int i = 0; i < groupCnt; i++) {
            if(groups[i].name == groupName) {
                groupIdx = i;
                return this;
            }
        }
        groups[groupCnt].Alloc(groupCnt, groupName);
        groupIdx = groupCnt++;
        return this;
    }
} users[MAX_USER];
int userCnt;

struct File {
    ll name;
    ll ext;
    File* sibling;

    File* Alloc(ll _name, ll _ext, File* _sibling) {
        name = _name;
        ext = _ext;
        sibling = _sibling;
        return this;
    }
} files[MAX_CALL];
int fileCnt;

struct Dir {
    int permission;
    ll name;
    int maker;
    Dir* next;
    Dir* sibling;
    File* file;

    Dir* Alloc(int _permission, ll _name, int userIdx, int groupIdx, Dir* _sibling) {
        permission = _permission;
        name = _name;
        next = nullptr;
        sibling = _sibling;
        file = nullptr;

        if(permission == 0) {
            maker = userIdx;
        } else if(permission == 1) {
            maker = groupIdx;
        } else maker = -1;

        return this;
    }
} dirs[MAX_CALL];
int dirCnt;

Dir rootDir;

ll getHash(char* name) {
    ll hash = 0;
    while(*name) {
        hash = (hash << 5) + *name - 'a' + 1;
        name++;
    }
    return hash;
}

ll getNextPathHash(char* path, int* cntRet) {
    ll hash = 0;
    int cnt = 1;
    while(*path && *path != '/') {
        hash = (hash << 5) + *path - 'a' + 1;
        path++;
        cnt++;
    }
    *cntRet = cnt;
    return hash;
}

ll getNextPattern(char* pattern, int* cntRet) {
    ll hash = 0;
    int cnt = 1;
    while(*pattern && *pattern != '/' && *pattern != '.') {
        hash = (hash << 5) + *pattern - 'a' + 1;
        pattern++;
        cnt++;
    }
    *cntRet = cnt;
    if(*pattern == '.') *cntRet += 9;
    return hash;
}

// #include <stdio.h>
// void showTables() {
//     printf("groups\n");
//     for(int i = 0; i < groupCnt; i++)
//         printf("idx: %d, name: %d\n", groups[i].idx, groups[i].name);
//     printf("users\n");
//     for(int i = 0; i < userCnt; i++)
//         printf("idx: %d, name %d, group: %d\n", users[i].idx, users[i].name, users[i].groupIdx);
//     printf("dirs\n");
//     for(int i = 0; i < dirCnt; i++) 
//         printf("permission: %d, name: %d, maker: %d\n", dirs[i].permission, dirs[i].name, dirs[i].maker);
//     printf("files\n");
//     for(int i = 0; i < fileCnt; i++) 
//         printf("name: %d, ext: %d\n", files[i].name, files[i].ext);

//     return;
// }

void init()
{
    groupCnt = userCnt = fileCnt = dirCnt = 0;

    char admin[6] = "admin";
    ll adminHash = getHash(admin);
    users[userCnt].Alloc(userCnt++, adminHash, adminHash);

    rootDir.Alloc(2, 0, 0, 0, nullptr);

}

void createUser(char userName[], char groupName[])
{
    ll userHash = getHash(userName);
    ll groupHash = getHash(groupName);
    users[userCnt].Alloc(userCnt++, userHash, groupHash);

    return;
}

int createDirectory(char userName[], char path[], char directoryName[], int permission)
{
    ll userHash = getHash(userName);
    int user, group;
    for(int i = 0; i < userCnt; i++) {
        if(users[i].name == userHash) {
            user = i;
            break;
        }
    }
    group = users[user].groupIdx;

    Dir *pivot = &rootDir;
    path++;
    while(*path) {
        int adder;
        ll dirHash = getNextPathHash(path, &adder);

        Dir *nextPivot = pivot->next;
        while(nextPivot) {
            if(nextPivot->name == dirHash) break;
            nextPivot = nextPivot->sibling;
        }
        pivot = nextPivot;

        if(pivot->permission == 0) {
            if(pivot->maker != user) return 0;
        } else if(pivot->permission == 1) {
            if(pivot->maker != group) return 0;
        }
        path += adder;
    }

    pivot->next = dirs[dirCnt++].Alloc(permission, getHash(directoryName), user, group, pivot->next);

    return 1;
}


int createFile(char userName[], char path[], char fileName[], char fileExt[])
{
    ll userHash = getHash(userName);
    int user, group;
    for(int i = 0; i < userCnt; i++) {
        if(users[i].name == userHash) {
            user = i;
            break;
        }
    }
    group = users[user].groupIdx;

    Dir *pivot = &rootDir;
    path++;
    while(*path) {
        int adder;
        ll dirHash = getNextPathHash(path, &adder);

        Dir *nextPivot = pivot->next;
        while(nextPivot) {
            if(nextPivot->name == dirHash) break;
            nextPivot = nextPivot->sibling;
        }
        pivot = nextPivot;

        if(pivot->permission == 0) {
            if(pivot->maker != user) return 0;
        } else if(pivot->permission == 1) {
            if(pivot->maker != group) return 0;
        }
        path += adder;
    }

    pivot->file = files[fileCnt++].Alloc(getHash(fileName), getHash(fileExt), pivot->file);

    return 1;
}

Dir *Q1[MAX_CALL];
Dir *Q2[MAX_CALL];
int find(char userName[], char pattern[])
{
    ll userHash = getHash(userName);
    int user, group;
    for(int i = 0; i < userCnt; i++) {
        if(users[i].name == userHash) {
            user = i;
            break;
        }
    }
    group = users[user].groupIdx;

    Dir **Q = Q1;
    Q[0] = &rootDir;
    int Qcnt = 1;
    pattern++;
    while(Qcnt) {
        int newQcnt = 0;
        Dir **newQ;
        if(Q == Q1) newQ = Q2;
        else newQ = Q1;

        int cnt;
        ll hash = getNextPattern(pattern, &cnt);
        bool wild = false;
        if(*pattern == '*') {
            wild = true;
            pattern += 2;
        }
        if(cnt > 9) {
            cnt -= 9;
            if(!wild) pattern += cnt;

            bool wildExt = false;
            if(*pattern == '*') wildExt = true;
            ll extHash = getHash(pattern);

            int ans = 0;
            for(int i = 0; i < Qcnt; i++) {
                File* pivot = Q[i]->file;
                while(pivot) {
                    if(wild || pivot->name == hash) {
                        if(wildExt || pivot->ext == extHash) {
                            ans++;
                        }
                    }
                    pivot = pivot->sibling;
                }
            }
            return ans;
        }
        if(!wild) pattern += cnt;

        for(int i = 0; i < Qcnt; i++) {
            Dir* pivot = Q[i]->next;
            while(pivot) {
                if(pivot->permission == 0) {
                    if(pivot->maker != user) {
                        pivot = pivot->sibling;
                        continue;
                    }
                } else if(pivot->permission == 1) {
                    if(pivot->maker != group) {
                        pivot = pivot->sibling;
                        continue;
                    }
                }

                if(wild) {
                    newQ[newQcnt++] = pivot;
                    pivot = pivot->sibling;
                    continue;
                }
                if(pivot->name == hash) {
                    newQ[newQcnt++] = pivot;
                    break;
                }
                pivot = pivot-> sibling;
            }
        }

        Q = newQ;
        Qcnt = newQcnt;
    }

    return 0;
}
