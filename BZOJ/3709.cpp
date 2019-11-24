 
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
#define FOR(i,a,b) for(Re LL i = a;i <= b;++i)
#define ROF(i,a,b) for(Re LL i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 5e5 + 5;
  
inline int sgn(int x){
    return !x ? 0 : (x < 0 ? -1 : 1);
}
  
struct Node{
    int a,b,id;
      
    bool operator < (const Node &t) const {
        return sgn(b-a) > sgn(t.b-t.a);
    }
}a[MAXN];
int n,m;
 
inline bool cmp1(const Node &x,const Node &y){
    return x.a < y.a;
}
 
inline bool cmp2(const Node &x,const Node &y){
    return x.b > y.b;
}
std::vector<Node> p1,p2;
int p[MAXN];
inline void Solve(){
    scanf("%lld%lld",&n,&m);p1.clear();p2.clear();
    FOR(i,1,n){
        int a,b;scanf("%lld%lld",&a,&b);
        if(a <= b) p1.pb((Node){a,b,i});
        else p2.pb((Node){a,b,i});
    }
    std::sort(all(p1),cmp1);
    std::sort(all(p2),cmp2);
    int tp = 0;
    FOR(i,0,(int)p1.size()-1) a[++tp] = p1[i];
    FOR(i,0,(int)p2.size()-1) a[++tp] = p2[i];
    FOR(i,1,n){
        m -= a[i].a;
        if(m <= 0){
            puts("NIE");
            return;
        }
        m += a[i].b;
    }
    puts("TAK");
    FOR(i,1,n) printf("%d ",a[i].id);puts("");
}
  
signed main(){
    int T = 1;
    while(T--) Solve();
    return 0;
}
/*
1
3 5
3 1
4 8
8 3
*/
