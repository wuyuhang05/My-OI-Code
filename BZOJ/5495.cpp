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

const int MAXN = 10000000+5;

LL a[MAXN],sum[MAXN];
int n,k;
int ch[MAXN][2],size[MAXN],cnt;

inline void insert(LL x){
    int v = 0;
    ROF(i,31,0){
        int s = (x>>i)&1;size[v]++;
        if(!ch[v][s]) ch[v][s] = ++cnt;
        v = ch[v][s];
    }
    size[v]++;
}

LL query(LL x,int rk){
    int v = 0;LL ans = 0ll;
    ROF(i,31,0){
        int s = (x>>i)&1;
        if(!ch[v][s^1]) v = ch[v][s];
        else if(rk <= size[ch[v][s^1]]) v = ch[v][s^1],ans |= (1ll<<i);
        else rk -= size[ch[v][s^1]],v = ch[v][s];
    }
    return ans;
}

struct Node{
    int id,rk;LL w;
    Node(){}
    Node(int id,int rk) : id(id), rk(rk), w(query(sum[id],rk)){}

    friend bool operator < (const Node &a,const Node &b){
        return a.w < b.w;
    }
};

std::priority_queue<Node> q;
LL ans;

int main(){
    scanf("%d%d",&n,&k);k <<= 1;
    FOR(i,1,n) scanf("%lld",a+i),sum[i] = sum[i-1]^a[i];
    FOR(i,0,n) insert(sum[i]);
    FOR(i,0,n) q.push(Node(i,1));
    FOR(i,1,k){
        Node t = q.top();q.pop();
        ans += t.w;
        if(t.rk < n)
            q.push(Node(t.id,t.rk+1));
    }
    printf("%lld\n",ans>>1);
    return 0;
}
