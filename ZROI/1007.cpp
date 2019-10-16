/*
 * Author: RainAir
 * Time: 2019-09-28 21:08:13
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 17+2;

int n,m;
int mp[MAXN];
bool can[(1<<MAXN)+3];
int f[(1<<MAXN)+3];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        u--;v--;
        mp[u] |= (1<<v);mp[v] |= (1<<u);
    }
    FOR(S,0,(1<<n)-1){
        bool flag = true;
        FOR(i,0,n-1){
            if(S&(1<<i)){
                if(mp[i]&S) flag = false;
            }
            if(!flag) break;
        }
        can[S] = flag;
    }
    CLR(f,0x3f);int U = (1<<n)-1;
    FOR(S,0,U) if(can[S]) f[S] = 0;
    FOR(S,0,(1<<n)-1){
        int C = U^S;
        for(int T = C;T;T = (T-1)&C){
            if(can[T]) f[S|T] = std::min(f[S|T],f[S]+1);
        }
    }
    printf("%d\n",f[U]);
    return 0;
}
