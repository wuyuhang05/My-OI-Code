#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 500000+5;
const int LOG = 30+5;

LL a[MAXN],sum[MAXN],st[LOG][MAXN];
int n,k,l,r;

inline void init(){
    FOR(i,1,n) st[0][i] = i;
    FOR(i,1,25){
        for(int j = 1;j+(1<<i)-1 <= n;++j){
            int x = st[i-1][j],y = st[i-1][j+(1<<(i-1))];
            st[i][j] = sum[x] > sum[y] ? x : y;
        }
    }
}

inline int calc(int l,int r){
    int c = log2(r-l+1);
    int x = st[c][l],y = st[c][r-(1<<c)+1];
    return sum[x] > sum[y] ? x : y;
}

struct Node;
std::priority_queue<Node> q;

struct Node{
    int o,l,r,t;
    Node(){}
    Node(int o,int l,int r) : o(o), l(l), r(r), t(calc(l,r)) {}
    friend bool operator < (const Node &a,const Node &b){
        return sum[a.t] - sum[a.o - 1] < sum[b.t] - sum[b.o - 1];
    }
    inline void split(){
        if(l != t) q.push(Node(o,l,t-1));
        if(r != t) q.push(Node(o,t+1,r));
    }
};

int main(){
    scanf("%d%d%d%d",&n,&k,&l,&r);
    FOR(i,1,n) scanf("%lld",a+i),sum[i] = sum[i-1]+a[i];
    init();
    FOR(i,1,n) if(i+l-1 <= n) q.push(Node(i,i+l-1,std::min(i+r-1,n)));
    LL ans = 0;
    while(k--){
        Node x = q.top();q.pop();
        ans += sum[x.t] - sum[x.o-1];
        x.split();
    }
    printf("%lld\n",ans);
    return 0;
}
