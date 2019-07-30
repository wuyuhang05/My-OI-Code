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

const int MAXN = 1e5 + 5;
int t[MAXN],a[MAXN],b[MAXN],n;
bool vis[MAXN];

inline void Solve(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",t+i),vis[i] = false;
    FOR(i,1,n) scanf("%d",b+i);
    FOR(i,1,n) a[b[i]] = t[i];
    int ans = 0;
    FOR(i,1,n){
        if(vis[i]) continue;
        int p = i,cnt = 0;
        /*while(!vis[p]){
            vis[p] = true;
            p = a[p];cnt++;
        }//DEBUG(cnt);*/
        do{
            p = a[p];cnt++;
            vis[p] = true;
        }while(p != i);
        ans += std::max(1,cnt-1);
    }
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--)  Solve();
    return 0;
}
