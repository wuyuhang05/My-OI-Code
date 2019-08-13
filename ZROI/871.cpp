/*
 * Author: RainAir
 * Time: 2019-08-04 17:37:12
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

const int MAXN = 1e5 + 5;

int n,k,a[MAXN];
int cnt[MAXN];
std::vector<int> ans[MAXN];
std::stack<int> G[MAXN];

inline void Solve(){
    scanf("%d%d",&n,&k);
    FOR(i,0,n) cnt[i] = 0;
    FOR(i,0,MAXN-1) while(!G[i].empty()) G[i].pop();
    FOR(i,1,n) scanf("%d",a+i),cnt[a[i]]++,G[a[i]].push(i);
    ROF(i,n,2) cnt[i-1] += cnt[i]/k;
    if(cnt[1] >= k){
        FOR(i,1,k) ans[i].clear();
        int now = 1,res = 1,base = 1;
        FOR(i,1,n){
            while(!G[i].empty()){
                ans[now].pb(G[i].top());G[i].pop();
                if(!--res && now < k){
                    ++now;res = base;
                }
            }
            base *= k;res *= k;
        }
        puts("1");
        FOR(i,1,now){
            printf("%d ",(int)ans[i].size());
            for(auto x:ans[i]) printf("%d ",x);
            puts("");
        }
    }
    else{
        puts("0");return;
    }
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
