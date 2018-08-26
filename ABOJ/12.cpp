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

const int MAXN = 200000 + 5;

int N;
struct Line{
    int l,r,pos;

    bool operator < (const Line &other) const {
        return l < other.l;
    }
}l[MAXN];

struct Num{
    int x;
    bool operator < (const Num &other) const {
        return l[x].r > l[other.x].r;
    }
};

inline bool cmp(const Line &a,const Line &b){
    return a.l < b.l;
}

std::priority_queue<Num,std::vector<Num> > q; // fuck greater!!!
int ans=0;
int pp[MAXN];

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

int main(){
    freopen("meizi.in","r",stdin);
    freopen("meizi.out","w",stdout);
    read(N);
    FOR(i,1,N){
        read(l[i].l);read(l[i].r);
        l[i].pos = i;
    }
    std::sort(l + 1,l + N + 1);
    FOR(i,1,N){
        if(!q.empty()){
            int v = q.top().x;
            if(l[v].r >= l[i].l){
                ans++;
                q.push((Num){i});
                pp[l[i].pos] = ans;
            }
            else{
                q.pop();
                q.push((Num){i});
                pp[l[i].pos] = pp[l[v].pos];
            }
        }
        else{
            q.push((Num){i});
            ans++;
            pp[l[i].pos] = ans;
        }
    }
    printf("%d\n",ans);
    return 0;
}
