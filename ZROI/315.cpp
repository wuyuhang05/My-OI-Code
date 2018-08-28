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
#define R register
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

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
    void print(LL x){
        if(x < 0){
            putchar('-');
            x = -x;
        }
        if(x >= 10) print(x/10);
        putchar(x%10+'0');
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

int N;
LL f[MAXN],c[MAXN],d[MAXN],a[MAXN];
bool vis[MAXN],ed[MAXN];
LL val1[MAXN],val2[MAXN],F[MAXN];

LL ans = 0ll,min;
int s,t;bool flag;

void dfs(int v,int fa){
    vis[v] = true;
    if(ed[f[v]]) return;
    if(vis[f[v]]){
        s = f[v];t = v;
    }
    else dfs(f[v],v);
    if(s && s != v){
        if(F[v] != fa || !a[v]) flag = 1;
        min = std::min(min,(LL)val1[v]-val2[v]);
    }
    else if(s == v){
        s = 0;
        if(F[v] != t || !a[v]) flag = 1;
        min = std::min(min,(LL)val1[v]-val2[v]);
        if(!flag && v != t) ans -= min;
    }
    ed[v] = 1;
}

int main(){
    read(N);
    FOR(i,1,N){
        read(f[i]);read(c[i]);read(d[i]);read(a[i]);
    }
    FOR(i,1,N){
        int v = f[i];
        if(d[v] > c[i]){
            if(d[v] - c[i] > val1[v]){
                val2[v] = val1[v];
                val1[v] = d[v] - c[i];
                F[v] = i;
            }
            else
                if(d[v] - c[i] > val2[v])
                    val2[v] = d[v] - c[i];
        }
    }
    FOR(i,1,N) ans += 1ll * val1[i] * a[i];
    FOR(i,1,N){ 
        if(!vis[i]){
            s = t = flag = 0;
            min = LLONG_MAX;
            dfs(i,0);
        }
    }
    print(ans);
    return 0;
}
/*
5
5 9 2 2
1 1 7 4
2 3 6 3
2 2 9 6
1 4 5 1
 */ 
