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

const int MAXN = 2e5 + 5;
int f[MAXN];LL v[MAXN];
int n,m;

inline int find(int x){
    if(f[x] == -1) return x;
    int t = find(f[x]);
    v[x] += v[f[x]];f[x] = t;
    return t;
}

inline void Union(int i,int j,int s){
    int fa = find(i),fb = find(j);
    if(fa != fb){
        if(fa < fb) std::swap(fa,fb);
        f[fa] = fb;v[fa] = std::abs(v[i]-v[j]+s);
    }
}

int ans = 0;

inline void Solve(){
    ans = 0;CLR(f,-1);CLR(v,0);
    FOR(i,1,m){
        int l,r,s;scanf("%d%d%d",&l,&r,&s);
        l--;int fa = find(l),fb = find(r);
        if(fa == fb){
            if(std::abs(v[l]-v[r]) != s){
                ans++;
            }
        }
        else Union(l,r,s);
    }
    printf("%d\n",ans);
}

int main(){
    while(~scanf("%d%d",&n,&m)) Solve();
    return 0;
}
