/*
 * Author: RainAir
 * Time: 2019-07-21 09:40:39
 */
#include <unordered_map>
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

int a,b,k;
LL ans = 0ll;

inline int calc(int x,int y){
    return a*b-a*x-b*y;
}

struct Node{
    int x,y,f;
    Node(){}
    Node(int x,int y) : x(x),y(y) {
        f = calc(x,y);
    }
    
    inline bool operator < (const Node &t) const {
        return f < t.f;
    }
};
std::priority_queue<Node> q;
//std::unordered_map<int,int> S;
signed main(){
    scanf("%lld%lld%lld",&a,&b,&k);
    q.push(Node(1,1));//DEBUG(a*b);
    //S[calc(1,1)] = true;
    FOR(i,1,k){
        //if(q.empty()) break;
        Node v = q.top();q.pop();
        if(v.f < 0) break;
        while(!q.empty() && v.f == q.top().f) q.pop();
        ans ^= v.f;
      //  if(!S[calc(v.x,v.y+1)]) 
            q.push(Node(v.x,v.y+1));//,S[calc(v.x,v.y+1)] = true;
        //if(!S[calc(v.x+1,v.y)]) 
        q.push(Node(v.x+1,v.y));//,S[calc(v.x+1,v.y)] = true;
    }
    printf("%lld\n",ans);
    return 0;
}
