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

const int ha = 1e9 + 7;
int n,l;
int ans = 0;
struct Node{
    int t,x,y;
    Node(int t=0,int x=0,int y=0) : t(t),x(x),y(y) {}

    bool operator < (const Node &_) const {
        return t < _.t;
    }
}a[MAXN];

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

inline void work(int x,int y){

}

int main(){
    scanf("%d%d",&n,&l);
    FOR(i,1,n) scanf("%d%d%d",&a[i].t,&a[i].x,&a[i].y);
    std::sort(a+1,a+n+1);
    FOR(i,-l,l){
        FOR(j,0,l){
            if(std::abs(i)+j > l) break;
            work(i,j);
        }
        ROF(j,-1,-l){
            if(std::abs(i)-j > l) break;
            work(i,j);
        }
    }
    printf("%d\n",ans);
    return 0;
}
