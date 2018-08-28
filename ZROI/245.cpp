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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define lowbit(x) x&-x

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

const int MAXN = 500000 + 5;

struct Query{
    int l,r,pos;
    bool operator < (const Query &other) const {
        return r < other.r;
    }
}q[MAXN];

int N,M;
int a[MAXN],sum[MAXN],cnt;
int ans[MAXN],last;

int tree[MAXN];
std::map<int,int> S;

inline void add(int pos,int x){
    for(R int i = pos;i;i-=lowbit(i)){
        tree[i] ^= x;
    }
}

inline int calc(int x){
    int ret = 0;
    for(R int i = x;i < last;i += lowbit(i))
        ret ^= tree[i];
    return ret;
}

int main(){
    read(N);read(M);
    FOR(i,1,N){
        read(a[i]);
        sum[i] = sum[i-1]^a[i];
    }
    FOR(i,1,M){
        int opt,l,r;
        read(opt);read(l);read(r);
        if(opt == 1 || opt == 2)
            ans[i] = sum[r] ^ sum[l-1];
        else{
            q[++cnt] = (Query){l,r,i};
        }
    }
    std::sort(q+1,q+cnt+1);
    FOR(i,1,cnt){
        while(last <= q[i].r){
            add(S[a[last]],a[last]);
            S[a[last]] = last;last++;
        }
        ans[q[i].pos] = calc(q[i].l);
    }
    FOR(i,1,M) printf("%d\n",ans[i]);
    return 0;
}
