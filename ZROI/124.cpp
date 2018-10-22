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

const int MAXN = 500000+5;

int a[MAXN],N,Q;
int BASE;

struct Query{
    int l,r,pos,ans;
    bool operator < (const Query &other) const {
        int x=l/BASE,y=other.l/BASE;
        if(x == y) return r < other.r;
        return x < y;
    }
}q[MAXN];

int ans[MAXN];
int cnt[MAXN],tot;

inline void add(int x){
    x = a[x];
    cnt[x]++;
    if(cnt[x]==2) tot++;
    if(cnt[x]==3) tot--;
}

inline void del(int x){
    x = a[x];
    cnt[x]--;
    if(cnt[x] == 1) tot--;
    if(cnt[x] == 2) tot++;
}

inline void Solve(){
    int L=1,R=0;
    tot=0;
    FOR(i,1,Q){
        while(L<q[i].l) del(L++);
        while(L>q[i].l) add(--L);
        while(R<q[i].r) add(++R);
        while(R>q[i].r) del(R--);
        // printf("%d\n",tot);
        ans[q[i].pos]=tot;
    }
    FOR(i,1,Q) printf("%d\n",ans[i]);
}

std::map<int,int> S;

int main(){
    read(N);read(Q);
    BASE = (int)std::sqrt(N*1.0);
    FOR(i,1,N){
        read(a[i]);S.insert(std::make_pair(a[i],0));
    }
    int tN=0;
    for(std::map<int,int>::iterator it=S.begin();it!=S.end();it++){
        it->second = ++tN;
    }
    FOR(i,1,N) a[i]=S[a[i]];
    FOR(i,1,Q) read(q[i].l),read(q[i].r),q[i].pos=i;
    std::sort(q+1,q+Q+1);
    Solve();
    return 0;
}
