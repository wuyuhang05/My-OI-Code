//#include <tr1/unordered_map>
//#include <unordered_map>
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

const int MAXN = 15+1;
const int BASE = 31;
int a[MAXN],b[MAXN],n;
std::map<U LL,int> S;
//std::unordered_map<U LL,int> S;

inline U LL calc(int a[]){
    U LL res = 0;
    //FOR(i,1,n) printf("%d ",a[i]);puts("");
    FOR(i,1,n) res = res*BASE+a[i];
    return res;
}

/*
inline void get(int l,int r,int k){
    std::vector<int> tt;
    FOR(i,k,k+(r-l)){
        if(res[i]){
            res[i] = 0;tt.pb(res[i]);
        }
    }
    FOR(i,l,r) res[i] = ins[i-1];

}*/
bool flag = false;

inline void dfs1(int step,int c[]){
    if(step == 3){
        return;
    }
    int t[MAXN];FOR(i,1,n) t[i] = c[i];
    FOR(l,1,n){
        FOR(r,l,n){
            FOR(k,1,l-1){
                FOR(i,1,n) c[i] = t[i];
                int len = l-k;
                FOR(i,l,r){
                    int j = i;
                    FOR(k,1,len) std::swap(c[j],c[j-1]),j--;
                }
                U LL tt = calc(c);
                if(!S[tt]) S[tt] = step;
                dfs1(step+1,c);
            }
        }
    }
}
int ans = INT_MAX;
inline void dfs2(int step,int c[]){
    if(flag || step == 3){
        return;
    }
    int t[MAXN];FOR(i,1,n) t[i] = c[i];
    FOR(l,1,n){
        FOR(r,l,n){
            FOR(k,1,l-1){
                FOR(i,1,n) c[i] = t[i];
                int len = l-k;
                FOR(i,l,r){
                    int j = i;
                    FOR(k,1,len) std::swap(c[j],c[j-1]),j--;
                }
                int tt = S[calc(c)];
                if(tt){
                    ans = step+tt;
                    flag = true;return;
                }
                dfs2(step+1,c);
            }
        }
    }
}


inline void Solve(){
    flag = true;S.clear();ans = INT_MAX;
    scanf("%d",&n);FOR(i,1,n) b[i] = i,scanf("%d",a+i);
    FOR(i,1,n){
        if(a[i] != b[i]){
            flag = false;break;
        }
    }
    if(flag){
        puts("0");return;
    }
    dfs1(1,b);//return;
    int t = S[calc(a)];
    if(t) printf("%d\n",t);
    else{
        dfs2(1,a);
        if(ans == INT_MAX) puts("5 or more");
        else printf("%d\n",ans);
    }
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}


