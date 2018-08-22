#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define gmin(x,y) std::min(x,y)
#define R register

const int MAXN = 1000000 + 5;

struct SegmentTree;

int N,M;

inline char getc(){
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}

inline void Read(int &x){
    x = 0;int flag = 1;
    R char ch = getc();
    for(;!isdigit(ch);ch = getc())
        if(ch == '-') flag = -1;
    for(;isdigit(ch);ch = getc())
        x = (x << 1) + (x << 3) + (ch ^ '0');
    x *= flag;
}

SegmentTree *New(int,int,SegmentTree *,SegmentTree *);

struct SegmentTree{
    int l,r,min,tag;
    SegmentTree *lc,*rc;
    
    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid + 1,r));
    }
    
    inline void cover(int delta){
        tag += delta;
        min += delta;
    }
    
    inline void pushup(){
        min = gmin(lc->min,rc->min);
    }
    
    inline void pushdown(){
        if(tag){
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
        //pushup();
    }
    
    inline void update(int pos,int x){
        if(l == r){
            min = x;tag = 0;return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }
    
    inline void modify(int left,int right,int delta){
        if(left == l && right == r){
            cover(delta);return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) lc->modify(left,right,delta);
        else if(left > mid) rc->modify(left,right,delta);
        else{
            lc->modify(left,mid,delta);
            rc->modify(mid + 1,right,delta);
        }
        pushup();
    }
    
    inline int query(int left,int right){
        if(left == l && right == r) return min;
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) return lc->query(left,right);
        else if(left > mid) return rc->query(left,right);
        else return gmin(lc->query(left,mid),rc->query(mid + 1,right));
    }
}pool[MAXN * 3],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->min = INT_MAX;ret->tag = 0;
    return ret;
}

void DEBUG(){
    printf("DEBUG MESSAGE:   ");
    for(R int i = 1;i <= N;i++)
        printf("%d%c",segt->query(i,i),(i == N) ? '\n' : ' ');
}

int main(){
    Read(N);Read(M);
    segt = SegmentTree::build(1,N);
    for(R int r,i = 1;i <= N;i++){
        Read(r);segt->update(i,r);
    }
    int l,r,delta;
    for(R int i = 1;i <= M;i++){
        //DEBUG();
        Read(delta);Read(l);Read(r);
        segt->modify(l,r,-delta);
        if(segt->min < 0){
            printf("%d\n%d\n",-1,i);
            return 0;
        }
    }
    printf("%d\n",0);
    getchar();getchar();
    return 0;
}
