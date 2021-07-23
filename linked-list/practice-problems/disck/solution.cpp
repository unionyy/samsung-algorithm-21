const int MAX = 100000;
const int BUCKET = 1024;

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
NodeD heads[(MAX - 1) / BUCKET + 1];
NodeD tails[(MAX - 1) / BUCKET + 1];
bool tracks[MAX];
int loc;
bool DirLeft;

void init(int track_size, int head){
    T = track_size;
    loc = head;
    DirLeft = true;
    cntS = 0;
    cntD = 0;

    q.Alloc(-1, nullptr);

    for(int i = 0; i < (T - 1) / BUCKET + 1; i++) {
        NodeD* prev = nullptr;
        NodeD* next = nullptr;
        if(i > 0) prev = &heads[i - 1];
        if(i < (T - 1) / BUCKET) next = &heads[i + 1];
        heads[i].Alloc(-1, prev, &tails[i]);
        tails[i].Alloc(-2, &heads[i], next);
    }

    for(int i = 0; i < T; i++) tracks[i] = false;
}

bool FindTgt(int track, NodeD** prev, NodeD** next) {
    NodeD* pivot = &heads[track / BUCKET];

    while(pivot->next) {
        pivot = pivot->next;
        if(pivot->track >= 0) {
            if(!tracks[pivot->track]) pivot->Remove();
            else if(pivot->track >= track) break;
        }
    }
    if(pivot->track == track) {
        *prev = pivot;
        *next = pivot;
        return true;
    }
    if(pivot->track < 0) *next = nullptr;
    else *next = pivot;

    while(pivot->prev) {
        pivot = pivot->prev;
        if(pivot->track >= 0) {
            if(!tracks[pivot->track]) pivot->Remove();
            else break;
        }
    }
    if(pivot->track < 0) *prev = nullptr;
    else *prev = pivot;

    return false;
}

void request(int track){
    tracks[track] = true;

	NodeS* pivot = &q;
    while(pivot->next) pivot = pivot->next;
    pivot->next = bufferS[cntS++].Alloc(track, nullptr);

    NodeD* pivot2 = &heads[track / BUCKET];
    while(pivot2->next->track != -2 && pivot2->next->track < track)
        pivot2 = pivot2->next;
    bufferD[cntD++].Alloc(track, pivot2, pivot2->next);

    return;
}

int fcfs(){
	int track_no = -1;

    while(!tracks[q.next->track]) q.next = q.next->next;

    track_no = q.next->track;
    q.next = q.next->next;
    tracks[track_no] = false;
    loc = track_no;

	return track_no;
}

int sstf(){
	int track_no = -1;

    NodeD* prev;
    NodeD* next;
    FindTgt(loc, &prev, &next);

    NodeD* tgt;
    if(!prev) tgt = next;
    else if(!next) tgt = prev;
    else {
        int gabN = next->track - loc;
        int gabP = loc - prev->track;
        if(gabN < gabP) tgt = next;
        else tgt = prev;
    }

    track_no = tgt->track;
    tgt->Remove();
    tracks[track_no] = false;
    loc = track_no;

	return track_no;
}

int look(){
	int track_no = -1;

    NodeD* prev;
    NodeD* next;
    FindTgt(loc, &prev, &next);

    NodeD* tgt;
    if(!prev) {
        tgt = next;
        DirLeft = false;
    }
    else if(!next) {
        tgt = prev;
        DirLeft = true;
    }
    else if(DirLeft) tgt = prev;
    else tgt = next;

    track_no = tgt->track;
    tgt->Remove();
    tracks[track_no] = false;
    loc = track_no;

	return track_no;
}

int clook(){
	int track_no = -1;

    NodeD* prev;
    NodeD* next;
    FindTgt(loc, &prev, &next);

    NodeD* tgt;
    if(prev) tgt = prev;
    else {
        FindTgt(T - 1, &prev, &next);
        tgt = prev;
    }

    track_no = tgt->track;
    tgt->Remove();
    tracks[track_no] = false;
    loc = track_no;

	return track_no;
}

