#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")


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

const int MAXN = 200000 + 5;
struct Node *New(int,int,Node *,Node *,LL);

struct Node{
    int l,r;
    LL sum; 
    Node *lc,*rc;

    static Node *insert(int l,int r,int pos){
        // int mid = (l + r) >> 1;
        if(l == r) return New(l,r,NULL,NULL,1);
        int mid = (l + r) >> 1;
        if(pos <= mid) return New(l,r,insert(l,mid,pos),NULL,1);
        else return New(l,r,NULL,insert(mid+1,r,pos),1);
    }

}pool[MAXN<<6],*frog = pool,*root[MAXN<<4];
Node *New(int l,int r,Node *lc,Node *rc,LL sum){
    Node *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->sum = sum;
    return ret;
}

LL ans1,ans2;

void merge(Node *&x,Node *&y){
    if(!x){
        x = y;
        return;
    }
    if(!y) return;
    ans1 += ((x->rc) ? x->rc->sum : 0) * ((y->lc) ? y->lc->sum : 0);
    ans2 += ((x->lc) ? x->lc->sum : 0) * ((y->rc) ? y->rc->sum : 0);
    x->sum += y->sum;
    if(x->l == x->r) return;
    if(x->lc || y->lc) merge(x->lc,y->lc);
    if(x->rc || y->rc) merge(x->rc,y->rc);
}

int val[MAXN<<4],cnt=1;
int lc[MAXN<<4],rc[MAXN<<4];
LL ans;int N;

void solve(int pos){
    read(val[pos]);
    if(!val[pos]){
        lc[pos] = ++cnt;
        rc[pos] = ++cnt;
        solve(lc[pos]);solve(rc[pos]);
        ans1 = ans2 = 0;
        merge(root[lc[pos]],root[rc[pos]]);
        root[pos] = root[lc[pos]];
        ans += std::min(ans1,ans2);
    }
    else root[pos] = Node::insert(1,N,val[pos]);
}

int main(){
    read(N);
    solve(0);
    printf("%lld\n",ans);
    return 0;
}