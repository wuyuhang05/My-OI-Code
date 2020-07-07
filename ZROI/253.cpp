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

const int MAXN = 1e6 + 5;
const int ha = 1e9 + 9;
const int BASE = 31;
int pw[MAXN];
char str[MAXN];
int n;
std::vector<char> G[MAXN];
int tp;
int cs;
#include<cassert>
namespace Subtask1{
//public:
    int sm[MAXN];
    int pd[MAXN],ans[MAXN];

    inline int calc(int l,int r){
        return (sm[r]+ha-1ll*pw[r-l+1]*sm[l-1]%ha)%ha;
    }

    inline void Solve(){
        sm[0] = 0;FOR(i,1,n) sm[i] = (1ll*sm[i-1]*BASE%ha+str[i]-'a'+1)%ha,ans[i] = 1;
        pd[n] = 1;int d = n;ans[n] = str[1]!=str[n];
        FOR(i,1,n-1){
            if(n%i) {pd[i] = 0;continue;}
            int t = calc(1,i);bool flag = true;
            for(int j = i+1;j <= n;j += i){
                if(t != calc(j,j+i-1)){
                    flag = false;break;
                }
            }
            if(flag){
                d = i;break;
            }
        }ans[1] = 1;
        printf("Case %d:",cs);
        FOR(i,2,n){
            if((i-1)%d == 0) ans[i] = 0;
        }
        std::reverse(ans+1,ans+n+1);
        FOR(i,1,n) putchar('0'+ans[i]);
        puts("");
    }
}

namespace Subtask2{
//public:
    int ans[MAXN];
    int sm[MAXN];

    inline int calc(int l,int r){
        return (sm[r]+ha-1ll*sm[l-1]*pw[r-l+1]%ha);
    }

    inline void Solve(){
        FOR(i,1,n) ans[i] = 0;
        FOR(i,1,tp){
            sm[0] = 0;int len = G[i].size();
            FOR(j,1,len){
                sm[j] = (1ll*sm[j-1]*BASE%ha+G[i][j-1]-'a'+1)%ha;
            }
            FOR(j,2,len){
                if(calc(1,len-j+1) != calc(j,len)) ans[j] = 1;
            }
        }
        printf("Case %d:",cs);ans[1] = 1;
        std::reverse(ans+1,ans+n+1);
        FOR(i,1,n) putchar('0'+ans[i]);puts("");
    }
}

inline void Solve(){cs++;
    n = strlen(str+1);tp = 1;
    FOR(i,1,n){
        if(str[i] == str[i-1]){
            tp++;
        }
        G[tp].pb(str[i]);
    }
    if(tp == 1) Subtask1::Solve();
    else{
        if(str[1] != str[n]){
            std::vector<char> tmp;
            for(auto x:G[tp]) tmp.pb(x);G[tp].clear();tp--;
            for(auto x:G[1]) tmp.pb(x);G[1] = tmp;
        }
        Subtask2::Solve();
    }
    FOR(i,1,tp) G[i].clear();tp = 1;
}

int main(){
//    freopen("1.in","r",stdin);
//    freopen("1.out","w",stdout);
    pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 1ll*pw[i-1]*BASE%ha;
    while(~scanf("%s",str+1)) Solve();
    return 0;
}
