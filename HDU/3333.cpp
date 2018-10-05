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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
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

#define int long long

const int MAXN = 30000 + 5;
const int MAXQ = 100000 + 5;
const int MAXV = 1000000000 + 5;

struct Query{
    int l,r,pos;

    bool operator < (const Query &other) const {
        return r < other.r || (r == other.r && l < other.l);
    }
}q[MAXQ];

int N,Q;
int tree[MAXN<<2];
#define lowbit(x) x&-x;

inline void add(int pos,int delta){
    while(pos <= N){
        tree[pos] += delta;
        pos += lowbit(pos);
    }
}

inline int calc(int pos){
    int ret = 0;
    while(pos){
        ret += tree[pos];
        pos -= lowbit(pos);
    }
    return ret;
}
#undef lowbit

int a[MAXN],ans[MAXQ];
std::map<int,int> last;

inline void Solve(){
    CLR(tree,0);
    last.clear();
    read(N);
    FOR(i,1,N) read(a[i]);
    read(Q);
    FOR(i,1,Q){
        read(q[i].l);read(q[i].r);
        q[i].pos = i;
    }
    std::sort(q + 1,q + Q + 1);
    int j = 1;
    FOR(i,1,Q){
        while(j <= q[i].r){
            if(!last[a[j]]) add(j,a[j]);
            else{
                add(last[a[j]],-a[j]);
                add(j,a[j]);
            }
            last[a[j]] = j;j++;
        }
        ans[q[i].pos] = calc(q[i].r) - calc(q[i].l-1);
    }
    FOR(i,1,Q) printf("%lld\n",ans[i]);
}
#undef int
int main(){
    int T;read(T);
    while(T--) Solve();
    return 0;
}