/*
 * Author: RainAir
 * Time: 2019-08-11 18:50:04
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

const int MAXN = 100+5;

std::vector<int> v[MAXN],ans;
int g[5] = {0,1,3,8,20};
int a[MAXN],b[MAXN];
int n,A,T;

inline void cal(int d){
    ans.pb(d);
    FOR(i,0,n-1) b[i] = a[v[d][i]];
    FOR(i,0,n-1) a[i] = b[i];
}

inline void rotate(int d){
    ROF(i,4,1){
        while(d >= g[i]) cal(i),d -= g[i];
    }
}

int main(){
    scanf("%d%d%*d%*d%d",&n,&A,&T);
    FOR(i,1,4){
        v[i].pb(0);
        FOR(j,0,n-2) v[i].pb((j+g[i])%(n-1) + 1);
    }
    v[5].pb(1);v[5].pb(0);FOR(i,2,n-1) v[5].pb(i);
    FOR(i,6,A) FOR(j,0,n-1) v[i].pb(j);
    FOR(i,1,A){
        for(auto x:v[i]) printf("%d ",x+1);
        puts("");
    }
    while(T--){
        FOR(i,0,n-1) scanf("%d",a+i),--a[i];
        ans.clear();
        if(a[0] == 0) cal(5);
        while(true){
            int p = -1;
            FOR(i,0,n-1) if(!a[i]) p = i;// 2 0 1
            if(a[0] != 1){
                rotate(((p-1)+(a[0]-1))%(n-1));
                cal(5);
            }
            else{
                bool ok = true;
                FOR(i,0,n-3){
                    if(a[(i+p)%(n-1)+1] != i+2){
                        ok = false;
                        rotate((i+p)%(n-1));
                        cal(5);break;
                    }
                }
                if(ok){
                    rotate(p-1);
                    cal(5);
                    break;
                }
            }
        }
        printf("%d ",(int)ans.size());
        for(auto x:ans) printf("%d ",x);puts("");
    }
    return 0;
}
