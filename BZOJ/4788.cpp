/*
 * Author: RainAir
 * Time: 2019-08-25 07:53:58
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
#define int LL
const int MAXN = (1<<20)+5;
int l[MAXN],r[MAXN],cnt[MAXN],lv[MAXN],rv[MAXN];
int mp[22][22],t;
bool ll[MAXN],rr[MAXN];
int n,m;
std::vector<int> q1,q2;

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n){
        FOR(j,1,m){
            scanf("%1lld",&mp[i][j]);
            if(mp[i][j]) l[1<<i-1] |= (1<<j-1),r[1<<j-1] |= (1<<i-1);
        }
    }
    FOR(i,1,n) scanf("%lld",lv+i);
    FOR(i,1,m) scanf("%lld",rv+i);scanf("%lld",&t);
    FOR(i,1,MAXN-1) cnt[i] = cnt[i>>1] + (i&1);
    ll[0] = rr[0] = 1;
    FOR(S,1,(1<<n)-1){
        ll[S] = 1;int sm = 0;
        FOR(i,0,n-1){
            if(S&(1<<i)){
                l[S] |= l[S^(1<<i)];
                ll[S] &= ll[S^(1<<i)];
                if(!ll[S]) break;
                sm += lv[i+1];
            }
        }
        if(!ll[S]) continue;
        if(cnt[S] > cnt[l[S]]) ll[S] = 0;
        else q1.pb(sm);
    }
    FOR(S,1,(1<<m)-1){
        rr[S] = 1;int sm = 0;
        FOR(i,0,m-1){
            if(S&(1<<i)){
                r[S] |= r[S^(1<<i)];
                rr[S] &= rr[S^(1<<i)];
                if(!rr[S]) break;
                sm += rv[i+1];
            }
        }
        if(!rr[S]) continue;
        if(cnt[S] > cnt[r[S]]) rr[S] = 0;
        else q2.pb(sm);
    }
    std::sort(all(q1));std::sort(all(q2));
    int sz1 = q1.size(),sz2 = q2.size();
    q1.insert(q1.begin(),0);
    q2.insert(q2.begin(),0);
    int p1 = 0,p2 = sz2,ans = 0;
    while(p1 <= sz1 && p2 >= 0){
        while(p1 <= sz1 && q1[p1]+q2[p2] < t) p1++;
        ans += (q1.size() - p1);
        p2--;
    }
    printf("%lld\n",ans);
    return 0;
}
