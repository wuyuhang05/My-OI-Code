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

const int MAXN = 1000+5;
bool vis[MAXN];
int n,k,a[MAXN];
std::bitset<2005> b[2];

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,k){
        int x;scanf("%d",&x);
        vis[x] = true;
    }
    k = 0;FOR(i,0,1000) if(vis[i]) a[++k] = i-n;
    int t = 0;b[t^1].set(1000);
    FOR(i,1,1000){
        FOR(j,1,k){
            if(a[j] < 0)
                b[t] |= b[t^1] << (-a[j]);
            else 
                b[t] |= b[t^1] >> a[j];
        }
        if(b[t][1000]) return 0*printf("%d\n",i);
        t ^= 1;b[t].reset();
    }
    puts("-1");
    return 0;
}

