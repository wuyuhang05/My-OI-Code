// Codeforces is the best!!!!!!!!!!
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define U unsigned
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define LD long double

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

const int MAXN = 100000 + 5;

struct SegmentTree;

SegmentTree *New(int,int,SegmentTree*,SegmentTree*);

struct SegmentTree{
    int l,r;
    SegmentTree *lc,*rc;
    LD sum,tag1,tag2; // 1 = +;2 = *;
    
    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid + 1,r));
    }

    inline void cover1(LD delta){
        sum += (r - l + 1) * delta;
        tag1 += delta;
    }

    inline void cover2(LD delta){
        sum *= delta;
        tag1 *= delta;
        tag2 *= delta;
    }

    inline void pushup(){
        sum = lc->sum + rc->sum;
    }

    inline void pushdown(){
        lc->cover2(tag2);rc->cover2(tag2);
        lc->cover1(tag1);rc->cover1(tag1);
        tag1 = 0.0;tag2 = 1.0;
    }

    inline void update(int pos,int x){
        if(l == r){
            sum = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }

    void modify1(int left,int right,LD delta){
        if(left == l && right == r){
            cover1(delta);return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) lc->modify1(left,right,delta);
        else if(left > mid) rc->modify1(left,right,delta);
        else{
            lc->modify1(left,mid,delta);
            rc->modify1(mid + 1,right,delta);
        }
        pushup();
    }

    void modify2(int left,int right,LD delta){
        if(left == l && right == r){
            cover2(delta);return;
        }
        pushdown();
        int mid = (l+ r) >> 1;
        if(right <= mid) lc->modify2(left,right,delta);
        else if(left > mid) rc->modify2(left,right,delta);
        else{
            lc->modify2(left,mid,delta);
            rc->modify2(mid + 1,right,delta);
        }
        pushup();
    }

    double query(int left,int right){
        if(left == l && right == r) return sum;
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) return lc->query(left,right);
        if(left > mid) return rc->query(left,right);
        return lc->query(left,mid) + rc->query(mid + 1,right);
    }
}pool[MAXN*4],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->sum = ret->tag1 = 0.0;
    ret->tag2 = 1.0;
    ret->lc = lc;ret->rc = rc;
    return ret;
}

int N,M;
int a[MAXN];

int main(){
    freopen("random.in","r",stdin);
    freopen("random.out","w",stdout);
    read(N);read(M);
    FOR(i,1,N) read(a[i]);
    segt = SegmentTree::build(1,N);
    FOR(i,1,N)
        segt->update(i,a[i]);
    while(M--){
        int opt;read(opt);
        if(opt == 1){
            int l1,r1,l2,r2;
            read(l1);read(r1);read(l2);read(r2);
            double sum1 = segt->query(l1,r1),sum2 = segt->query(l2,r2);
            double len1 = r1-l1+1,len2 = r2-l2+1;
            segt->modify2(l1,r1,(len1-1)/len1);
            segt->modify2(l2,r2,(len2-1)/len2);
            segt->modify1(l1,r1,1.0/len1 * (sum2/len2));
            segt->modify1(l2,r2,1.0/len2 * (sum1/len1));
        }
        else{
            int l,r;
            read(l);read(r);
            printf("%f\n",segt->query(l,r));
        }
    }
    return 0;
}
