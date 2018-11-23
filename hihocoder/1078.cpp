#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 100000
    static char buf[SIZE],*p1 = buf+SIZE,*pend = buf+SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,SIZE,stdin);
        if(p1 == pend) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;char ch = nc();
    int flag = 1;
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    x *= flag;
}

const int MAXN = 100000+5;

struct Node *New(int ,int ,Node *,Node *);

struct Node{
    int l,r,sum,tag;
    Node *lc,*rc;

    static Node *build(int l,int r){
        int mid = (l + r) >> 1;
        return l == r ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        sum = lc->sum + rc->sum;
    }

    inline void cover(int delta){
        sum = (r-l+1)*delta;
        tag = delta;
    }

    inline void pushdown(){
        if(tag != -1){
            lc->cover(tag);
            rc->cover(tag);
            tag = -1;
        }
    }

    void modify(int L,int R,int delta){
        if(l == L && r == R){
            cover(delta);return;
        }
        pushdown();
        int mid = (l+r)>>1;
        if(R <= mid) lc->modify(L,R,delta);
        else if(L > mid) rc->modify(L,R,delta);
        else lc->modify(L,mid,delta),rc->modify(mid+1,R,delta);
        pushup();
    }

    int query(int L,int R){
        if(l == L && r == R) return sum;
        pushdown();
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        else if(L > mid) return rc->query(L,R);
        return lc->query(L,mid)+rc->query(mid+1,R);
    }
}pool[MAXN<<2],*frog = pool,*segt;

Node *New(int l,int r,Node *lc,Node *rc){
    Node *ret = ++frog;
    ret->l = l;ret->r = r;ret->lc = lc;ret->rc = rc;
    ret->sum = 0;ret->tag = -1;
    return ret;
}

int N,Q;

int main(){
    read(N);segt = Node::build(1,N);
    FOR(i,1,N){
        int x;read(x);
        segt->modify(i,i,x);
    }
    read(Q);
    while(Q--){
        int opt,l,r;read(opt);read(l);read(r);
        if(!opt){
            printf("%d\n",segt->query(l,r));
        }
        else{
            int x;read(x);
            segt->modify(l,r,x);
        }
    }
    system("pause");
    return 0;
}