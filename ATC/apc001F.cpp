/*
 * Author: RainAir
 * Time: 2019-10-08 16:33:35
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

const int MAXN = 1e5 + 5;
const int MAXM = 15 + 1;
int a[MAXN];
int n,ans;
int cnt[16];
int f[(1<<MAXM)+3];

inline int dfs(int S){
    int &ans = f[S];
    if(!S) return ans = 0;
    if(ans != -1) return ans;
    ans = 1e9;
    FOR(i,1,15){
        if(!(S&(1<<(i-1)))) continue;
        FOR(j,1,15){
            if(i == j) continue;
            if(!(S&(1<<(j-1)))) continue;
            int x = i^j,nS = S;
            if(S&(1<<(x-1))){
                nS ^= (1<<(i-1));
                nS ^= (1<<(j-1));
                nS ^= (1<<(x-1));
                ans = std::min(ans,2+dfs(nS));
            }
            else{
                nS |= (1<<(x-1));
                nS ^= (1<<(i-1));
                nS ^= (1<<(j-1));
                ans = std::min(ans,1+dfs(nS));
            }
        }
    }
    return ans;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        ++u;++v;
        a[u] ^= w;a[v] ^= w;
    }
    FOR(i,1,n) cnt[a[i]]++;
    FOR(i,1,15) ans += cnt[i]/2,cnt[i] %= 2;
    int S = 0;
    FOR(i,1,15) if(cnt[i]) S |= (1<<(i-1));
    CLR(f,-1);
    ans += dfs(S);
    printf("%d\n",ans);
    return 0;
}
