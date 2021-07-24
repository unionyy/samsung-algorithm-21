const int MAX = 100000;
const int BUCKET = 64;
const int DIV = 6;

struct NodeS {
    int track;
    NodeS* next;

    NodeS* Alloc(int _track, NodeS* _next) {
        track = _track;
        next = _next;

        return this;
    }
} bufferS[MAX];

struct NodeD {
    int track;
    NodeD* prev;
    NodeD* next;

    NodeD* Alloc(int _track, NodeD* _prev, NodeD* _next) {
        track = _track;
        prev = _prev;
        next = _next;
        if(_prev) _prev->next = this;
        if(_next) _next->prev = this;
        return this;
    }

    void Remove() {
        prev->next = next;
        next->prev = prev;
    }
} bufferD[MAX];

int cntS, cntD;

int T; // Track Size
NodeS q;
NodeS* qTail;
NodeD heads[((MAX - 1) >> DIV) + 1];
NodeD tails[((MAX - 1) >> DIV) + 1];
bool tracks[MAX];
int loc;
bool DirLeft;

NodeD* prevG;
NodeD* nextG;
bool validG;

void RemoveD(NodeD* node) {
    node->Remove();
    if(node == prevG) {
        NodeD* pivot = node;
        while(pivot->prev) {
            pivot = pivot->prev;
            if(pivot->track < 0) continue;
            if(!tracks[pivot->track]) pivot->Remove();
            else break;
        }
        if(pivot->track < 0) prevG = nullptr;
        else prevG = pivot;
    }
    if(node == nextG) {
        NodeD* pivot = node;
        while(pivot->next) {
            pivot = pivot->next;
            if(pivot->track < 0) continue;
            if(!tracks[pivot->track]) pivot->Remove();
            else break;
        }
        if(pivot->track < 0) nextG = nullptr;
        else nextG = pivot;
    }
    return;
}

void init(int track_size, int head){
    T = track_size;
    loc = head;
    DirLeft = true;
    cntS = 0;
    cntD = 0;

    q.Alloc(-1, nullptr);
    qTail = &q;

    for(int i = 0; i < ((T - 1) >> DIV) + 1; i++) {
        NodeD* prev = nullptr;
        NodeD* next = nullptr;
        if(i > 0) prev = &tails[i - 1];
        if(i < (T - 1) >> DIV) next = &heads[i + 1];
        heads[i].Alloc(-1, prev, &tails[i]);
        tails[i].Alloc(-2, &heads[i], next);
    }

    for(int i = 0; i < T; i++) tracks[i] = false;

    prevG = nullptr;
    nextG = nullptr;
    validG = false;

    return;
}

bool FindTgt() {
    NodeD* pivot = &heads[loc >> DIV];

    while(pivot->next) {
        pivot = pivot->next;
        if(pivot->track >= 0) {
            if(!tracks[pivot->track]) pivot->Remove();
            else if(pivot->track >= loc) break;
        }
    }
    if(pivot->track == loc) {
        prevG = pivot;
        nextG = pivot;
        return true;
    }
    if(pivot->track < 0) nextG = nullptr;
    else nextG = pivot;

    while(pivot->prev) {
        pivot = pivot->prev;
        if(pivot->track >= 0) {
            if(!tracks[pivot->track]) pivot->Remove();
            else break;
        }
    }
    if(pivot->track < 0) prevG = nullptr;
    else prevG = pivot;

    validG = true;

    return false;
}

void request(int track){
    tracks[track] = true;

    qTail->next = bufferS[cntS++].Alloc(track, nullptr);
    qTail = qTail->next;

    NodeD* pivot2 = &heads[track >> DIV];
    while(pivot2->next->track != -2 && pivot2->next->track < track) pivot2 = pivot2->next;
    NodeD* cNode = bufferD[cntD++].Alloc(track, pivot2, pivot2->next);

    if(validG) {
        if(track == loc) {
            prevG = cNode;
            nextG = cNode;
        } else if(track < loc) {
            if(!prevG) prevG = cNode;
            else if(prevG->track < track) prevG = cNode;
        } else {
            if(!nextG) nextG = cNode;
            else if(nextG->track > track) nextG = cNode;
        }
    }

    return;
}

int fcfs(){
	int track_no = -1;

    while(!tracks[q.next->track]) q.next = q.next->next;

    track_no = q.next->track;
    q.next = q.next->next;
    tracks[track_no] = false;
    loc = track_no;
    validG = false;

    if(!q.next) qTail = &q;

	return track_no;
}

int sstf(){
	int track_no = -1;

    if(!validG) FindTgt();

    NodeD* tgt;
    if(!prevG) tgt = nextG;
    else if(!nextG) tgt = prevG;
    else {
        int gabN = nextG->track - loc;
        int gabP = loc - prevG->track;
        if(gabN < gabP) tgt = nextG;
        else tgt = prevG;
    }

    track_no = tgt->track;
    RemoveD(tgt);
    tracks[track_no] = false;
    loc = track_no;

	return track_no;
}

int look(){
	int track_no = -1;

    if(!validG) FindTgt();

    NodeD* tgt;
    if(!prevG) {
        tgt = nextG;
        DirLeft = false;
    }
    else if(!nextG) {
        tgt = prevG;
        DirLeft = true;
    }
    else if(DirLeft) tgt = prevG;
    else tgt = nextG;

    track_no = tgt->track;
    RemoveD(tgt);
    tracks[track_no] = false;
    loc = track_no;

	return track_no;
}

int clook(){
	int track_no = -1;

    if(!validG) FindTgt();

    NodeD* tgt;
    if(prevG) tgt = prevG;
    else {
        loc = T - 1;
        FindTgt();
        tgt = prevG;
    }

    track_no = tgt->track;
    RemoveD(tgt);
    tracks[track_no] = false;
    loc = track_no;

	return track_no;
}

