/*
 * Time: 2019-11-13 17:39:38
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

const int MAXN = 1e6 + 5;
const int MAXM = 1e7 + 5e6;
const int MAXL = 30;
int ch[MAXM][2],tot = 1,rt = 1;
int n,k;
int a[MAXN],sm[MAXN],sz[MAXM];

inline void insert(int val){
    int v = rt;
    ROF(i,MAXL,0){
        int x = (bool)(val&(1<<i));
        if(!ch[v][x]) ch[v][x] = ++tot;
        v = ch[v][x];sz[v]++;
    }
}

inline int query(int val){
    int v = rt,res = 0;
    ROF(i,MAXL,0){
        int kk = (bool)(k&(1<<i));
        int x = (bool)(kk^((bool)((1<<i)&val)));
        if(kk){
            res += sz[ch[v][!x]];
        }
        if(!ch[v][x]) break;
        v = ch[v][x];
    }
    return res;
}
#include <cassert>
int main(){
    scanf("%d%d",&n,&k);
    CLR(ch,0);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) sm[i] = sm[i-1]^a[i];
//    FOR(i,1,n) DEBUG(sm[i]);
    insert(0);LL ans = 0;
    FOR(i,1,n){
//        int t = query(sm[i]);
//        assert(t == i);
        ans += query(sm[i]);
        insert(sm[i]);
    }
    printf("%lld\n",1ll*n*(n+1)/2-ans);
    return 0;
}
