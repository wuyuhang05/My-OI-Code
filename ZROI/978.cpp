/*
 * Author: RainAir
 * Time: 2019-11-09 19:35:45
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
const int MAXN = 1e5 + 5;
const int MAXM = 50;
std::vector<int> A[MAXN+2],B[MAXN+2],lst,tmp;
int n,k;

inline bool chk(int mid){
    FOR(i,0,MAXM) B[i] = A[i];lst.clear();
    int ans = 0;
    FOR(i,0,MAXM){
        int p1 = 0,p2 = 0;tmp.clear();
        while(p1 < B[i].size() && p2 < lst.size()){
            if(B[i][p1] < lst[p2]) tmp.pb(B[i][p1++]);
            else tmp.pb(lst[p2++]);
        }
        FOR(j,p1,(int)B[i].size()-1) tmp.pb(B[i][j]);
        FOR(j,p2,(int)lst.size()-1) tmp.pb(lst[j]);
        lst.clear();
        B[i] = tmp;
//        DEBUG(i);
//        for(auto x:B[i]) printf("%d ",x);
//        puts("");
        if(!B[i].empty()){
     //       if(i == 2) DEBUG(B[i][(int)B[i].size()-1]);
            if(mid & 1) ans += B[i][(int)B[i].size()-1],B[i].pop_back();
            int j;
            for(j = (int)B[i].size()-1;j > 0;j -= 2){
                lst.pb(B[i][j]+B[i][j-1]);
            }
            if(j == 0) lst.pb(B[i][0]);
            std::reverse(all(lst));
        }
        mid >>= 1;
    }
//    DEBUG(ans);
    return ans >= k;
}

signed main(){
    scanf("%lld%lld",&n,&k);
    int l = 0,r = 0;
    FOR(i,1,n){
        int a,b;scanf("%lld%lld",&a,&b);
        r += (1ll<<a);
        A[a].pb(b);
    }
    FOR(i,0,MAXM) std::sort(all(A[i]));
    int ans = r;
//    DEBUG(chk(20));
//    exit(0);
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,r = mid-1;
        else l = mid+1;
    }
    printf("%lld\n",ans);
    return 0;
}
