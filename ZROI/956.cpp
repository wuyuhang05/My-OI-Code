/*
 * Author: RainAir
 * Time: 2019-09-02 19:15:33
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = (6e5*31)+3;
const int BASE = 29;

int tag[MAXN],ch[MAXN][2],tot=1,xors,rt = 1;

inline void update(int val,int d){
    int v = rt;
    FOR(i,0,BASE){
        int x = (1<<i)&val;
        x = x ? 1 : 0;
        if(!ch[v][x]) ch[v][x] = ++tot;
        v = ch[v][x];
    }
    tag[v] += d;
}

inline void add1(int step,int v,int val){
    if(!v) return;
    int x = (1<<step)&val;
    x = x ? 1 : 0;
    add1(step+1,ch[v][x],val);
    std::swap(ch[v][0],ch[v][1]);
}

std::vector<int> ans;

inline void dfs(int step,int v,int val){
    if(!v) return;
    dfs(step+1,ch[v][0],val);
    dfs(step+1,ch[v][1],val|(1<<step));
    while(tag[v]--) ans.pb(val^xors);
}

int n,q;

int main(){
    scanf("%d%d",&n,&q);
    FOR(i,1,n){
        int x;scanf("%d",&x);
        update(x,1);
    }
    FOR(i,1,q){
        int opt;scanf("%d",&opt);
        int x;if(opt != 3) scanf("%d",&x);
        if(opt == 1){
            update(x^xors,1);
        }
        if(opt == 2){
            update(x^xors,-1);
        }
        if(opt == 3){
            add1(0,rt,((1<<30)-1)^xors);
        }
        if(opt == 4){
            xors ^= x;
        }
    }
    dfs(0,rt,0);
    std::sort(all(ans));
    for(auto x:ans) printf("%d ",x);
    return 0;
}
