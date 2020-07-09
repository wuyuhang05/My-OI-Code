/*
 * Author: RainAir
 * Time: 2019-08-05 20:51:45
 */
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;
const int MAXM = 168;
std::bitset<MAXM+1> b[MAXN];
int ts[MAXM+1];
std::bitset<MAXM+1> x;

inline void insert(int big,int ps=0){
    if(big != 1){
        if(!ts[big]){
            ts[big] = ps;
            b[big] = x;
            return;
        }
        else{
            std::swap(b[big],x);
            std::swap(ts[big],ps);
            x ^= b[big];
        }
    }
    ROF(i,MAXM,1){
        if(x[i]){
            if(!ts[i]){
                ts[i] = ps;
                b[i] = x;
                return;
            }
            else if(ps <= ts[i]){
                std::swap(b[i],x);
                std::swap(ts[i],ps);
                x ^= b[i];
            }
            else x ^= b[i];
        }
    }
}

inline int query(int big){
    int res = 0;
    if(big != 1){
        if(ts[big]){
            x ^= b[big];
            res = std::max(res,ts[big]);
        }
        else return -1;
    }
    ROF(i,MAXM,1){
        if(x[i]){
            if(!ts[i]) return -1;
            res = std::max(res,ts[i]);
            x ^= b[i];
        }
    }
    return res;
}

bool p[MAXN];
int prime[MAXN],cnt;
int f[MAXN],d[MAXN];

inline void prework(){
    FOR(i,2,MAXN-1){
        if(!p[i]) prime[++cnt] = i,f[i] = cnt,d[i] = i;
        for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
            p[i*prime[j]] = 1;d[i*prime[j]] = prime[j];
            if(!(i%prime[j])) break;
        }
    }
}

int n,ans[MAXN];

int main(){
    prework();
    scanf("%d",&n);
    ROF(i,n,1){
        std::bitset<MAXM+1> bk;int t = i;x.reset();
        while(t != 1){
            if(f[d[t]] > MAXM) break;
            x[f[d[t]]].flip();
            t /= d[t];
        }
        bk = x;
        ans[i] = query(t);
        if(ans[i] != -1) ans[i] = std::max(ans[i],i);
        x = bk;
        insert(t,i);
    }
    std::vector<int> S;
    FOR(i,1,n) if(ans[i] == n) S.pb(i);
    printf("%d\n",(int)S.size());
    for(auto x:S) printf("%d\n",x);
    return 0;
}
