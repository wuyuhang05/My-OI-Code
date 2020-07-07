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
#define double long double
#define int LL
const int MAXN = 1e5 + 5;
int n,q;

struct Node{
    int x,y;
    Node(int x=0,int y=0) : x(x),y(y) {}
    inline double deg(){
        return atan2(y,x);
    }

    Node operator - (const Node &t) const {
        return Node(x-t.x,y-t.y);
    }

    inline int operator * (const Node &t) const {
        return x*t.y-y*t.x;
    }
}a[MAXN];

inline bool cmp(Node x,Node y){
    return x*y > 0;
}

signed main(){
    int N;
    scanf("%lld%lld",&N,&q);
    bool gx = 1;
    FOR(i,1,N){
        int x,y;scanf("%lld%lld",&x,&y);
        if(x == 0 && y == 0) continue;
        a[++n] = Node(x,y);
    }
    FOR(i,2,n){
        gx &= (a[i].y*a[i-1].x == a[i].x*a[i-1].y);
    }
    std::sort(a+1,a+n+1,cmp);
    int cnt = 1;
    FOR(i,2,n){
        if(a[i]*a[i-1] != 0) cnt++;
    }
    FOR(i,1,q){
        Node p;scanf("%lld%lld",&p.x,&p.y);
        if(p.x == 0 && p.y == 0){
            puts("0");continue;
        }
        int ps = std::lower_bound(a+1,a+n+1,p,cmp)-a;
        bool flag = 0;
        FOR(j,std::max(1ll,ps-5),std::min(n,ps+5)){
            if(p.y*a[j].x == p.x*a[j].y){
                flag = 1;break;
            }
        }
        if(flag){
            puts("1");continue;
        }
        if(gx){
            puts("-1");continue;
        }
        if(cnt >= 3){
            puts("2");continue;
        }
        flag = true;
        FOR(i,1,std::min(5ll,n)){
            ROF(j,n,std::max(n-5,1ll)){
                if(i == j) continue;
                flag &= (a[i]*(p-a[j])==0 && a[j]*(p-a[i])==0);
            }
        }
        if(flag){
            puts("3");continue;
        }
        puts("2");
    }
    return 0;
}
