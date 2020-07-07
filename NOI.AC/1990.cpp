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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;

int n;
int f[MAXN],x[MAXN],y[MAXN],p[MAXN];

struct Node{
    int x,y,i;
    Node(int x=0,int y=0,int i=0) : x(x),y(y),i(i) {}

    bool operator < (const Node &t) const {
        if((x > y) != (t.x > t.y)) return (x > y) < (t.x > t.y);
        if(x > y) return y > t.y;
        else return x < t.x;
    }
};
std::priority_queue<Node> q;

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

bool vis[MAXN];

int main(){
    scanf("%d",&n);FOR(i,1,n) f[i] = i;
    FOR(i,2,n){
        scanf("%d%d%d",p+i,x+i,y+i);++p[i];
        if(x[i] == -1) x[i] = 1e9;
        q.push(Node(x[i],y[i],i));
    }
    while(!q.empty()){
        Node v = q.top();q.pop();
        if(vis[v.i] || v.x != x[v.i] || v.y != y[v.i]) continue;
        vis[v.i] = 1;
        int p = find(::p[v.i]);
        if(x[p] < y[v.i]) y[p] += y[v.i]-x[p],x[p] = x[v.i];
        else x[p] += x[v.i]-y[v.i];
        if(p != 1) q.push(Node(x[p],y[p],p));
        f[v.i] = p;
    }
    printf("%d\n",y[1]);
    return 0;
}
