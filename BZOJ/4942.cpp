#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 1000000+5;
const int BASE = (1<<30)-1;
const int S = (1<<30);
bool ok;

struct Node *New(int ,int ,Node *,Node *);

struct Node{
    int l,r,c,tag,num;
    Node *lc,*rc;

    static Node *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ?  New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        c = (lc->c == rc->c) ? lc->c : -1;
    }

    inline void calc(int x){
        c = tag = x;
        num = x ? BASE : 0;
    }

    inline void pushdown(){
        if(~tag){
            lc->calc(tag);
            rc->calc(tag);
            tag = -1;
        }
    }

    inline int query(int pos){
        if(l == r) return num;
        pushdown();
        int mid = (l + r) >> 1;
        if(pos <= mid) return lc->query(pos);
        else return rc->query(pos);
    }

    inline void work(int pos,int x){
        if(l == r){
            num = x;c = -1;
            if(!x) calc(x);
            if(x == BASE) calc(1);
            return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->work(pos,x);
        else rc->work(pos,x);
        pushup();
    }

    inline void findadd(int pos){
        if(c == 1) {calc(0);return;}
        if(l == r){
            num++;
            if(num == BASE) c = 1;
            else c = -1;
            ok = true;
            return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(pos <= mid){
            lc->findadd(pos);
            if(!ok) rc->findadd(pos);
        }
        else rc->findadd(pos);
        pushup();
    }

    inline void findel(int pos){
        if(!c) {calc(1);return;}
        if(l == r){
            if(!--num) c = 0;
            else{
                c = -1;
            }
            ok = true;
            return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(pos <= mid){
            lc->findel(pos);
            if(!ok) rc->findel(pos);
        }
        else rc->findel(pos);
        pushup();
    }
}pool[MAXN<<2],*frog = pool,*segt;

Node *New(int l,int r,Node *lc,Node *rc){
    Node *ret = ++frog;
    ret->l = l;ret->r = r;ret->lc = lc;ret->rc = rc;
    ret->tag = -1;ret->c = ret->num = 0;
    return ret;
}

void add(int x,int y){
    int t = segt->query(x);
    segt->work(x,(t+y)%(BASE+1));
    ok = false;
    if(t + y > BASE) segt->findadd(x+1);
}

void del(int x,int y){
    int t = segt->query(x);
    segt->work(x,(t-y+(BASE+1))%(BASE+1));
    ok = false;
    if(t-y < 0) segt->findel(x+1);
}

int N;

signed main(){
    scanf("%lld%*d%*d%*d",&N);
    segt = Node::build(1,N);
    while(N--){
        int opt;scanf("%lld",&opt);
        if(opt & 1){
            int a,b;scanf("%lld%lld",&a,&b);
            int c = b/30;
            if(a > 0){
                add(c+1,(a<<(b%30))&BASE);
                add(c+2,a>>(30-b%30));
            }
            else{
                a = -a;
                del(c+1,(a<<(b%30))&BASE);
                del(c+2,a>>(30-b%30));
            }
        }
        else{
            int x;scanf("%lld",&x);
            int t = segt->query(x/30+1);
            printf("%lld\n",(t&(1<<(x%30))) ? 1ll : 0ll);
        }
    }
    return 0;
}