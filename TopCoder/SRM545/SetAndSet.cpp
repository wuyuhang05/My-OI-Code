/*
 * Author: RainAir
 * Time: 2019-07-30 18:49:04
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

const int MAXN = 50+5;

class SetAndSet{
public:
    int n;LL ans;
    int f[MAXN];
    std::vector<int> bit[MAXN];

    inline int find(int x){
        return x == f[x] ? x : f[x] = find(f[x]);
    }

    inline void dfs(int x,int y){ // x位，有 y 位不对
        if(x >= 20){
            int cnt = 0;
            FOR(i,1,n) if(i == find(i)) cnt++;
            ans += (y&1) ? -(1ll<<cnt) : (1ll<<cnt);
            return;
        }
        dfs(x+1,y);
        if(bit[x].empty()) return;
        int tmp[MAXN];FOR(i,1,n) tmp[i] = f[i];
        int t = find(bit[x][0]);
        FOR(i,1,(int)bit[x].size()-1){
            int fa = find(bit[x][i]);
            if(fa != t) f[fa] = t;
        }
        dfs(x+1,y+1);
        FOR(i,1,n) f[i] = tmp[i];
    }

    LL countandset(std::vector<int> a){
        n = a.size();ans = 0;
        FOR(i,1,n) f[i] = i;
        FOR(i,0,20){
            FOR(j,1,n) if((~a[j-1]) & (1<<i)) bit[i].pb(j);
            //for(auto x:bit[i]) DEBUG(x);puts("------");
        }
        dfs(0,0);
        return ans;
    }
};

int main(){
    SetAndSet aaa;
    int n;scanf("%d",&n);std::vector<int> dw;
    FOR(i,1,n) {int x;scanf("%d",&x);dw.pb(x);}
    printf("%lld\n",aaa.countandset(dw));
    return 0;
}

