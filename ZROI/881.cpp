/*
 * Author: RainAir
 * Time: 2019-08-06 18:56:28
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

const int MAXN = 2e5 + 5;
std::deque<int> q1,q2;
int h,w,n;
std::vector<int> G[MAXN];
int ans[MAXN],p[MAXN];

int main(){
    scanf("%d%d%d",&h,&w,&n);
    FOR(i,1,n){
        int x,y;scanf("%d%d",&x,&y);
        G[x].pb(y);
    }
    FOR(i,1,w) (i&1 ? q1:q2).pb(i);
    FOR(i,1,h){
        if(i&1) std::swap(q1,q2);
        else{
            int x = q1.front();q1.pop_front();
            int y = q2.back();q2.pop_back();
            std::swap(q1,q2);
            q1.push_front(x);q2.pb(y);
        }
        for(auto x:G[i]){
            int xx = x,yy = x+1;
            if(yy&1) std::swap(xx,yy);
            std::swap(q1[std::ceil(xx/2.0)-1],q2[std::ceil(yy/2.0)-1]);
            //std::swap(q1[(x+1)/2],q2[x/2]);
        }
    }
    for(int i = 1;i < w;i += 2) p[i] = q1.front(),q1.pop_front();
    for(int i = 2;i <= w;i += 2) p[i] = q2.front(),q2.pop_front();
    FOR(i,1,w) ans[p[i]] = i;
    FOR(i,1,w) printf("%d\n",ans[i]);
    return 0;
}
