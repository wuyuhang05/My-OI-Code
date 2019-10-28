/*
 * Author: RainAir
 * Time: 2019-10-25 16:22:45
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e3 + 5;
const int MAXM = 2e3 + 5;

char str[MAXN];
int a[MAXN][MAXN],b[MAXN][MAXN];
int u[MAXN][MAXN],d[MAXN][MAXN],l[MAXN][MAXN],r[MAXN][MAXN];
int n;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXM];

    inline void clear(){
        CLR(tree,0);
    }

    inline void add(int pos,int x){
        while(pos < MAXM){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline int calc(int pos){
        int res = 0;
        if(!pos) return 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }

    inline int query(int l,int r){
        if(l > r) return 0;
        return calc(r)-calc(l-1);
    }
}bit;

int ans;
std::vector<int> del[MAXN]; //  i 矩形在什么时候对答案无贡献
bool aa[MAXN][MAXN],bb[MAXN][MAXN];

inline void calc1(int x,int y){ // 左下
    bit.clear();
    FOR(i,0,MAXN-1) del[i].clear();
    while(x <= n+1 && y >= 1){
        for(auto xx:del[x]) bit.add(xx,-1);
        int len;
        if(u[x][y] < r[x][y]){
            len = u[x][y];
            int t = std::min(r[x][y],u[x-len-1][y]+len+1);
            if(bit.query(x-t,x-len-1) > 0){
                if(!bb[x-len-1][y]) ans++,bb[x-len-1][y] = 1;
            }
        }
        else{
            len = r[x][y];
            int t = std::min(u[x][y],r[x][y+len+1]+len+1);
            if(bit.query(x-t,x-len-1) > 0){
                if(!aa[x][y+len]) ans++,aa[x][y+len] = 1;
            }
        }
        bit.add(x,1);
        len = std::min(d[x][y],l[x][y])+1;
        del[x+len].pb(x);
        x++;y--;
    }
}

inline void calc2(int x,int y){// 右上
    bit.clear();
    FOR(i,0,MAXN-1) del[i].clear();
    int len;
    while(x >= 1 && y <= n+1){
        for(auto xx:del[x]) bit.add(xx,-1);
        if(l[x][y] < d[x][y]){
            len = l[x][y];
            int t = std::min(d[x][y],l[x][y-len-1]+len+1);
            if(bit.query(x+len+1,x+t) > 0){
                if(!aa[x][y-len-1]) ans++,aa[x][y-len-1] = 1;
            }
        }
        else{
            len = d[x][y];
            int t = std::min(l[x][y],d[x+len+1][y]+len+1);
            if(bit.query(x+len+1,x+t) > 0){
                if(!bb[x+len][y]) ans++,bb[x+len][y] = 1;
            }
        }
        bit.add(x,1);
        len = std::min(u[x][y],r[x][y])+1;
        del[x-len].pb(x);
        x--;y++;
    }
}

int main(){
    scanf("%d",&n);scanf("%*c");
    FOR(i,1,n+1){
        scanf("%[^\n]",str+1);scanf("%*c");
        FOR(j,1,2*n+1){
            a[i][j/2+1] = str[j] == '|'; // 是否可以上
            b[i][j/2+1] = str[j] == '_'; // 是否可以左
        }
    }
    FOR(i,1,n+1){
        FOR(j,1,n+1){
            if(a[i][j]) u[i][j] = u[i-1][j]+1;
            if(b[i][j]) l[i][j] = l[i][j-1]+1;
        }
    }
    ROF(i,n+1,1){
        ROF(j,n+1,1){
            if(a[i+1][j]) d[i][j] = d[i+1][j]+1,DEBUG(d[i][j]);
            if(b[i][j+1]) r[i][j] = r[i][j+1]+1;
        }
    }
    FOR(i,1,n+1) calc1(1,i),calc2(i,1),calc2(n+1,i),calc1(i,n+1);
    printf("%d\n",ans);
    return 0;
}
