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
const int MAXM = 100+5;

LL f[2][MAXN];int now;
int n,k;
LL w[MAXM][MAXN];
int p[MAXN];

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXM];
    inline void add(int pos,int x){
        for(pos++;pos<MAXM;pos+=lowbit(pos)) tree[pos] += x;
    }

    inline int query(int pos){
        int res = 0;
        for(pos++;pos;pos-=lowbit(pos)) res += tree[pos];
        return res;
    }
}pre,suf;

LL ext = 0;
std::deque<int> q;
#define X(i) ((i))
#define Y(i) (-(f[now^1][i]))

inline double slope(int i,int j){
    return 1.0*(Y(i)-Y(j))/(X(i)-X(j));
}

inline bool pd(int i,int j,int k,int l){
    return 1ll*(Y(i)-Y(j))*(X(k)-X(l)) <= 1ll*(X(i)-X(j))*(Y(k)-Y(l));
//    return slope(i,j) >= slope(k,l);
}

int main(){
    scanf("%d%d",&n,&k);
//    n = 2e5;k = 100;
    int t = 0;
    FOR(i,1,n){
        scanf("%d",p+i);
        //p[i] = 0;
        if(p[i]){
            ext += t-suf.query(p[i]);
            t++;suf.add(p[i],1);
        }
    }
    int m = n-t;
    t = 0;
    FOR(i,1,n){
        if(p[i]){
            suf.add(p[i],-1);pre.add(p[i],1);t++;
        }
        else{
            FOR(j,1,k){
                w[j][i-t] = t-pre.query(j)+suf.query(j-1);
            }
        }
    }
    now = 0;
    f[now][0] = 0;
    FOR(i,1,m) f[now][i] = f[now][i-1]+w[k][i];
    ROF(i,k-1,1){
        now ^= 1;
        FOR(j,0,m) f[now][j] = f[now^1][j];
        // sth...
        FOR(j,1,m) w[i][j] += w[i][j-1];
        FOR(j,0,m) f[now^1][j] += -w[i][j]-1ll*j*j;
        f[now][0] = 0;q.clear();
        FOR(j,1,m){
            while(q.size() >= 2 && pd(j-1,q[q.size()-1],q[q.size()-1],q[q.size()-2])) q.pop_back();
            q.pb(j-1);
            //FOR(k,0,j-1){
            //    int gx = f[now^1][k]+j*k;
            //    mx = std::max(mx,gx);
            //}
            while(q.size() >= 2 && f[now^1][q[0]]+1ll*j*q[0] <= f[now^1][q[1]]+1ll*j*q[1]) q.pop_front();
            LL mx = f[now^1][q.front()]+1ll*j*q.front();
            f[now][j] = std::max(f[now][j],mx+w[i][j]);
        }
//        DEBUG(f[now][m]);
    }
    printf("%lld\n",f[now][m]+ext);
    return 0;
}
/*
f[i][j] = f[i+1][k]+(...) k < j
*/
