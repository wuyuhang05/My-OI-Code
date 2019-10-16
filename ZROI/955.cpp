/*
 * Author: RainAir
 * Time: 2019-09-02 20:37:19
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 1e6 + 5;
const int ha = 1e9 + 7;
const int BASE = 31;
int n,m;
char str[MAXN];
LL row[MAXN],col[MAXN],_s[MAXN];
int _p[MAXN],p[MAXN],N;
bool pre[MAXN],suf[MAXN];

inline void calc(int n,bool dp[]){
    dp[1] = true;
    for(int i = 2,lst = 1;i <= n;++i){
        dp[i] = p[i] >= i-lst;
        if(dp[i]) lst = i;
    }
}

inline void manacher(){
    int mid = 0,maxlen = 0;
    FOR(i,1,N){
        if(i < maxlen) _p[i] = std::min(_p[mid*2-i],_p[mid]-(i-mid));
        else _p[i] = 1;
        while(_s[i-_p[i]] == _s[i+_p[i]]) _p[i]++;
        if(_p[i]+i > maxlen){
            maxlen = _p[i]+i;
            mid = i;
        }
    }
}

inline void init(){
    N = 0;CLR(pre,0);CLR(suf,0);
    CLR(_p,0);CLR(p,0);CLR(_s,0);
}

inline int solve(LL s[],int n){
    init();
    _s[++N] = -19491001;_s[++N] = -19260817;
    FOR(i,1,n) _s[++N] = s[i],_s[++N] = -19260817;
    manacher();
    FOR(i,1,n) p[i] = _p[i<<1] >> 1;
    calc(n,pre);
    FOR(i,1,n) p[i] = _p[(i+1)<<1] >> 1;
//    FOR(i,1,n) printf("%d ",p[i]);puts("");
    std::reverse(p+1,p+n+1);
    calc(n,suf); 
    std::reverse(suf+1,suf+n+1);
    int ans = 0,sm = 0;
    FOR(i,1,n){
        sm += pre[i];
        ans += sm*suf[i];
    }
    return ans;
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n){
        scanf("%s",str+1);
        FOR(j,1,m){
            row[i] = row[i]*BASE%ha+(str[j]-'a'+1);
            col[j] = col[j]*BASE%ha+(str[j]-'a'+1);
            row[i] %= ha;col[j] %= ha;
        }
    }
    printf("%lld\n",solve(row,n)*solve(col,m));
    return 0;
}

