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

const int MAXN = 2e5 + 5;
std::bitset<4096> S[MAXN];
int n,k,q;
int a[13][MAXN];
std::vector<P> G[MAXN];

int main(){
    scanf("%d%d%d",&n,&k,&q);
    FOR(i,1,k) FOR(j,1,n) scanf("%d",&a[i][j]),G[j].pb(MP(a[i][j],i));
    FOR(i,1,n) std::sort(all(G[i]));//,std::reverse(all(G[i]));
    FOR(i,1,k){
        FOR(S,0,(1<<k)-1){
            if((S>>(i-1))&1) ::S[i][S] = 1;
        }
    }
    int now = k;
    FOR(i,1,q){
        int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
        if(opt == 1){
            S[++now] = S[x]|S[y];
        }
        if(opt == 2){
            S[++now] = S[x]&S[y];
        }
        if(opt == 3){
            int state = (1<<k)-1;
            FOR(i,0,k-1){
                state ^= (1<<(G[y][i].se-1));
                if(!S[x][state]){
                    printf("%d\n",G[y][i].fi);
                    break;
                }
            }
        }
    }
    return 0;
}
