/*
 * Author: RainAir
 * Time: 2019-07-24 16:19:08
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

const int MAXN = 2500+5;
P seg[MAXN],p[MAXN];
int n,m;
std::priority_queue<int,std::vector<int>,std::greater<int> > S;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d%d",&seg[i].fi,&seg[i].se);
    FOR(i,1,m) scanf("%d%d",&p[i].fi,&p[i].se);
    std::sort(p+1,p+m+1);std::sort(seg+1,seg+n+1);
    int pos = 0,ans = 0;
    FOR(i,1,m){
        while(pos < n && seg[pos+1].fi <= p[i].fi) S.push(seg[++pos].se);
        while(!S.empty() && S.top() < p[i].fi) S.pop();
        if(S.empty()) continue;
        //S.pop();ans++;
        while(!S.empty() && p[i].se){
            p[i].se--;ans++;S.pop();
        }
    }
    printf("%d\n",ans);
    return 0;
}
