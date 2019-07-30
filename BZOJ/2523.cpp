/*
 * Author: RainAir
 * Time: 2019-07-22 14:57:21
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

inline bool chk(int x,int y,int t,int n){
    while(n > 0){
        if(x == y) break;
        int tx = x,ty = y;
        if(x < y){
            x = ty-tx;y = tx;
            t = (t+2)%3;n--;
        }
        else{// x > y
            x = ty;y = tx-ty;
            t = (t+1)%3;n -= 2;
        }
    }
    return x == y && t == n;
}

int n,m;

struct Node{
    int s[3];
    
    bool operator < (const Node &t) const {
        return s[0] == t.s[0] ? s[1] < t.s[1] : s[0] < t.s[0];
    }

    inline void print(){
        FOR(i,0,2) printf("%d ",s[i]);puts("");
    }
};

std::vector<Node> ans;

int main(){
    while(~scanf("%d%d",&n,&m) && (n+m) > 0){
        n--;ans.clear();
        int a = n%3,b = (n+1)%3,c = (n+2)%3;
        FOR(i,1,m-1){
            if(chk(i,m-i,a,n)){
                Node v;CLR(v.s,0);
                v.s[a] = m;v.s[b] = i;v.s[c] = m-i;
                ans.pb(v);
            }
        }
        printf("%d\n",(int)ans.size());
        std::sort(all(ans));
        FOR(i,0,(int)ans.size()-1) ans[i].print();
    }
    return 0;
}
