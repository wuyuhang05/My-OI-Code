/*
 * Author: RainAir
 * Time: 2019-10-25 18:47:48
 */
#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 5e5 + 5;

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
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

int n,m,k,y[MAXN],a[MAXN],s[MAXN],z[MAXN];
double c[MAXN],x[MAXN],add[MAXN];

inline double calc(){
    int now = -1;
    double ans = 0;
    FOR(i,1,k){
        double sld = y[s[i]];
        if(now != -1){
            ++now;
            sld *= (1-c[now]);
        }
        sld *= add[i];
        double gx = a[i]*(1-std::max((double)0,(1-sld/z[i]))*std::max(0.0,(1-sld/z[i])));
        if(gx < a[i]*0.64) now = 0;
        ans += gx;
    }
    return ans;
}

namespace Subtask1{
    inline void Solve(){
        FOR(i,1,k) add[i] = 1;
        printf("%.2lf\n",calc());
        exit(0);
    }
}

namespace Subtask2{
    inline void Solve(){
        double ans = 0;
        FOR(i,1,k) add[i] = 1;
        FOR(i,1,k){
            add[i] = 1+x[1];
            ans = std::max(ans,calc());
            add[i] = 1;
        }
        printf("%.2lf\n",ans);
        exit(0);
    }
}

const int MAXM = 10;

namespace Subtask3{
    double f[(1<<MAXM)+1][101],g[(1<<MAXM)+1];
    inline void Solve(){
        FOR(i,1,k) f[0][i] = add[i] = 1;
        g[0] = calc();
        FOR(S,0,(1<<n)-1){
           FOR(i,1,k) add[i] = f[S][i];
            FOR(i,0,n-1){
                if((1<<i)&S) continue;
                int ps = 0;double mx = g[S|(1<<i)];
                FOR(j,1,k){
                    double t = add[j];
                    add[j] *= (1+x[i+1]);
                    double tt = calc();
                    if(tt > mx) mx = tt,ps = j;
                    add[j] = t;
                }
                if(ps){
                    g[S|(1<<i)] = mx;
                    FOR(j,1,k) f[S|(1<<i)][j] = f[S][j];
                    f[S|(1<<i)][ps] *= (1+x[i+1]);
                }
            }
        }
        printf("%.2lf\n",g[(1<<n)-1]);
        exit(0);
    }
}

signed main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    read(n);read(m);read(k);
    FOR(i,1,n){
        int t;read(t);
        x[i] = 1.0*t/100;
    }
    std::sort(x+1,x+n+1);
    FOR(i,1,m) read(y[i]);
    FOR(i,1,k-1){
        int t;read(t);
        c[i] = 1.0*t/100;
    }
    FOR(i,1,k) read(a[i]),read(s[i]),read(z[i]);
    if(!n) Subtask1::Solve();
    if(n == 1) Subtask2::Solve();
    Subtask3::Solve();
    return 0;
}
