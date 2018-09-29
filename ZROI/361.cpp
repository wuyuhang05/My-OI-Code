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
#undef LL
#define LL double
long long a[50];
int opt[30]; // +:1 -:2 *:3 /:4
long long ans;

void dfs(int step){
#define min(x,y) x < y ? x : y
    if(step == 4){
        LL aa[50];
        FOR(i,1,4) aa[i] = (double)a[i];

        // printf("%d %d %d\n",opt[1],opt[2],opt[3]);
        FOR(i,1,3){
            if(opt[i] >= 3){
                int last = i;
                while(last && aa[last] == LLONG_MAX) last--;
                if(opt[i] == 3){
                    aa[last] *= aa[i+1];
                    aa[i+1] = LLONG_MAX;
                }
                if(opt[i] == 4){
                    // if(aa[last] % aa[i+1]) return;
                    aa[last] /= aa[i+1];
                    aa[i+1] = LLONG_MAX;
                }
            }
        }
        FOR(i,1,3){
            if(opt[i] <= 2){
                int last = i;
                while(last && aa[last] == LLONG_MAX) last--;
                if(opt[i] == 1){
                    aa[last] += aa[i+1];
                    aa[i+1] = LLONG_MAX;
                }
                if(opt[i] == 2){
                    aa[last] -= aa[i+1];
                    aa[i+1] = LLONG_MAX;
                }
            }
        }
        // FOR(i,1,4) printf("aa:%d %d %d %d\n",aa[1],aa[2],aa[3],aa[4]);
        LL cnt = 0;
        FOR(i,1,4) if(aa[i] != LLONG_MAX) cnt = aa[i];
        cnt = std::fabs(cnt);// DEBUG(cnt);
        if(cnt == double(int(cnt))) ans = min(ans,cnt);
        return;
    }
    FOR(i,1,4){
        opt[step] = i;
        dfs(step+1);
    }
#undef min
}


int main(){
    FOR(i,1,4) read(a[i]);
    if(a[1] == a[2] && a[2] == a[3] && a[3] == a[4] && a[4] == 0){
        puts("0");return 0;
    }
    ans = INT_MAX;
    dfs(1);
    printf("%lld\n",ans);
    return 0;
}