/*
 * Author: RainAir
 * Time: 2019-07-24 13:21:28
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
#define P std::pair<int,int>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100+5;
int n;
P a[MAXN];
std::priority_queue<int,std::vector<int>,std::greater<int> > q;

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i].fi);
    FOR(i,1,n) scanf("%d",&a[i].se);
    std::sort(a+1,a+n+1);int t = 0;
    FOR(i,1,n){
        t = std::max(t,a[i].fi);
        q.push(a[i].se);
        while(q.size() > t) q.pop();
    }
    int ans = 0;
    while(!q.empty()) ans += q.top(),q.pop();
    printf("%d\n",ans);
    return 0;
}
