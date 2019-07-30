/*
 * Author: RainAir
 * Time: 2019-07-24 19:05:32
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

const int MAXN = 5e5 + 5;
int n,k,p;
int s[MAXN],a[MAXN],suf[MAXN];
bool vis[MAXN];
struct Node;
std::priority_queue<Node> q;

struct Node{
    int x;
    Node(){}
    Node(int x) : x(x) {}

    inline bool operator < (const Node &t) const {
        return suf[x] < suf[t.x];
    }
};

int main(){
    scanf("%d%d%d",&n,&k,&p);
    FOR(i,1,p) scanf("%d",a+i);
    ROF(i,p,1) suf[i] = s[a[i]],s[a[i]] = i;
    FOR(i,1,p) if(!suf[i]) suf[i] = INT_MAX;
    int pos = 0;
    int ans = 0,sz = 0;
    FOR(i,1,p){
        if(vis[a[i]]){
            q.push(Node(i));
            continue;
        }
        ans++;sz++;
        if(sz > k){
            int t = q.top().x;q.pop();sz--;
            vis[a[t]] = false;
        }
        vis[a[i]] = true;q.push(Node(i));
    }
    printf("%d\n",ans);
    return 0;
}
