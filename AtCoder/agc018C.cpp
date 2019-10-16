#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define ROF(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int long long
const int MAXN = 100000 + 5;

struct Node{
    int a,b,c;

    bool operator < (const Node &other) const {
        return a-b < other.a-other.b;
    }
}p[MAXN];

int N,x,y,z;
int sum=0,tot;
int l[MAXN];
std::priority_queue<int,std::vector<int>,std::greater<int> > q;

signed main(){
    scanf("%lld%lld%lld",&x,&y,&z);
    N = x+y+z;
    FOR(i,1,N) scanf("%lld%lld%lld",&p[i].a,&p[i].b,&p[i].c),tot += p[i].c;
    std::sort(p+1,p+N+1);
    LL ans = 0,sum = 0;
    FOR(i,1,y){
        sum += p[i].b-p[i].c;
        q.push(p[i].b-p[i].c);
    }
    FOR(i,y+1,N-x+1){
        l[i] = sum;
        sum += p[i].b-p[i].c;
        q.push(p[i].b-p[i].c);
        sum -= q.top();q.pop();
    }
    while(!q.empty()) q.pop();
    sum = 0;
    ROF(i,N,N-x+1){
        sum += p[i].a-p[i].c;
        q.push(p[i].a-p[i].c);
    }
    ROF(i,N-x,y){
        ans = std::max(ans,tot+l[i+1]+sum);
        sum += p[i].a-p[i].c;
        q.push(p[i].a-p[i].c);
        sum -= q.top();
        q.pop();
    }
    printf("%lld\n",ans);
    return 0;
}
