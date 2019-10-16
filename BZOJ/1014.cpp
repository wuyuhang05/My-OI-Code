/*
 * Author: RainAir
 * Time: 2019-10-10 14:42:02
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

const int MAXN = 2e5 + 5;
const int ha = 1e9 + 9;
const int BASE = 31;

#define lc (ch[x][0])
#define rc (ch[x][1])
int ch[MAXN][2],f[MAXN],sz[MAXN],cnt;
U LL sm[MAXN],pw[MAXN],val[MAXN];int root;

inline void pushup(int x){
    sz[x] = sz[lc] + sz[rc] + 1;
    sm[x] = sm[lc] + val[x]*pw[sz[lc]] + sm[rc]*pw[sz[lc]+1];
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1] == x,w = ch[x][!k];
    ch[z][ch[z][1] == y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;f[w] = y;
    pushup(y);pushup(x);
}

inline void splay(int x,int v){
    int y,z;
    while((y = f[x]) != v){
        if((z = f[y]) != v)
            rotate((ch[z][1] == y)^(ch[y][1] == x) ? x : y);
        rotate(x);
    }
    if(!v) root = x;
}

inline int find(int rk){
    int x = root;
    while("Sqytxdy"){ // Sqy TXDY!!!
        int ls = sz[lc];
        if(rk <= ls) x = lc;
        else if(rk == ls+1) break;
        else rk -= ls+1,x = rc;
    }
    return x;
    //splay(x);
}

inline void debug(int x){
    if(lc) debug(lc);
    printf("%c",(char)(val[x]+'a'-1));
    if(rc) debug(rc);
}

inline U LL calc(int l,int r){
    int x = find(l),y = find(r+2);
    splay(x,0);splay(y,x);
  //  debug(ch[y][0]);puts("");
    return sm[ch[y][0]];
}

inline void insert(int ps,int d){
    int x = find(ps+1),y = find(ps+2);
    splay(x,0);splay(y,x);
    val[++cnt] = d;f[cnt] = y;ch[y][0] = cnt;sz[cnt] = 1;
    pushup(cnt);pushup(y);pushup(x);splay(cnt,0);
}

char str[MAXN];

inline void build(int l,int r,int pre){
    if(l > r) return;
    if(l == r){
        val[l] = sm[l] = str[l]-'a'+1;f[l] = pre;
        sz[l] = 1;
        ch[pre][l > pre] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(l,mid-1,mid);build(mid+1,r,mid);
    val[mid] = str[mid]-'a'+1;f[mid] = pre;
    ch[pre][mid > pre] = mid;
    pushup(mid);
}

int len = 0;

inline int query(int x,int y){
    int l = 1,r = std::min(cnt-x,cnt-y)-1,ans = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(calc(x,x+mid-1) == calc(y,y+mid-1)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    return ans;
}

int main(){
    scanf("%s",str+2);len = strlen(str+2);
    pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = pw[i-1]*BASE;
    build(1,len+2,0);root = (len+3) >> 1;
    cnt = len+2;
    int q;scanf("%d",&q);
    while(q--){
        char opt[sizeof("Orz")],s[sizeof("Orz")];int x;
        scanf("%s",opt+1);scanf("%d",&x);
        if(opt[1] == 'Q'){
            int y;scanf("%d",&y);
            printf("%d\n",query(x,y));
        }
        if(opt[1] == 'R'){
            scanf("%s",s);
            x = find(x+1);splay(x,0);
            val[root] = s[0]-'a'+1;pushup(root);
        }
        if(opt[1] == 'I'){
            scanf("%s",s);//++len;
            insert(x,(int)(s[0]-'a'+1));
        }
 //       DEBUG(calc(1,cnt));
    }
    return 0;
}
