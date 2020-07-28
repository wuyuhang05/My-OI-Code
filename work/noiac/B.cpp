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
const int MAXN = 1e5 + 5;
int n,m,s;
int A[1000000+5];
const int ha = 998244353;
int a[MAXN];

inline void gen(){
    A[0] = s;
    FOR(i,1,1000000) A[i] = (1ll*A[i-1]*100000005%ha+20150609)%ha;
    FOR(i,1,n) a[i] = A[i]%2;
}

int len,l,r;

inline bool cmp(int x,int y){
//    DEBUG(1);
    FOR(i,1,len){
        if(a[x] < a[y]) return 1;
        if(a[x] > a[y]) return 0;
        x++;y++;
        if(x == r+1) x = l;
        if(y == r+1) y = l;
    }
    return 1;
}

int main(){
    scanf("%d%d%d",&n,&m,&s);
    gen();
    FOR(i,1,m){
        int a = 1+A[n+4*(i-1)+1]%n,b = 1+A[n+4*(i-1)+2]%n,c=1+A[n+4*(i-1)+3]%n,d=1+A[n+4*(i-1)+4]%n;
        int l1 = std::min(a,b),r1 = std::max(a,b),l2 = std::min(c,d),r2 = std::max(c,d);
        std::vector<int> S1,S2;
        FOR(i,l1,r1) S1.pb(i);
        FOR(i,l2,r2) S2.pb(i);
        len = S1.size();l = l1;r = r1;std::sort(all(S1),cmp);
        len = S2.size();l = l2;r = r2;std::sort(all(S2),cmp);
        int ans = 0,lim = std::min(S1.size(),S2.size());
        FOR(i,0,lim-1){
            int p1 = S1[i]+(int)S1.size()-1,p2 = S2[i]+(int)S2.size()-1;
            if(p1 > r1) p1 -= (int)S1.size();
            if(p2 > r2) p2 -= (int)S2.size();
            if(::a[p1] > ::a[p2]){
                ans = 1;break;
            }
            if(::a[p1] < ::a[p2]){
                ans = -1;break;
            }
        }
        if(!ans){
            if(S1.size() < S2.size()) ans = -1;
            if(S1.size() > S2.size()) ans = 1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
