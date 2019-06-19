#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

inline void read(int &x){
    x = 0;char ch = getchar();int flag = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;ch = getchar();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = getchar();
    }
    if(flag) x = -x;
}

const int MAXN = 200000+5;

char str[MAXN],op[22],d[22];
int ch[MAXN][2],f[MAXN],size[MAXN],v[MAXN],id[MAXN],root,cnt;
U LL h[MAXN],p[MAXN];
int n;
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    size[x] = size[lc]+size[rc]+1;
    h[x] = h[lc]+v[x]*p[size[lc]]+p[size[lc]+1]*h[rc];
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1] == x,w = ch[x][!k];
    ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;f[w] = y;
    pushup(y);pushup(x);
}

void splay(int x,int v){
    int y,z;
    while((y = f[x]) != v){
        if((z = f[y]) != v) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
        rotate(x);
    }
    if(!v) root = x;
}

inline int find(int rk){
    int x = root;
    while(233){
        if(rk <= size[lc]) x = lc;
        else if(rk == size[lc] + 1) return x;
        else rk -= size[lc]+1,x = rc;
    }
}

inline void insert(int rk,int val){
    int x = find(rk+1),y = find(rk+2);
    splay(x,0);splay(y,x);
    int z = ++cnt;ch[y][0] = z;f[z] = y;v[z] = val;
    pushup(z);pushup(y);pushup(x);splay(z,0);
}

inline int calc(int k,int val){
    int x = find(k),y = find(k+val+1);
    splay(x,0);splay(y,x);
    return h[ch[y][0]];
}

inline int solve(int x,int y){
    int l = 1,r = std::min(cnt-x,cnt-y)-1,ans=0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(calc(x,mid) == calc(y,mid)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    return ans;
}

inline void build(int l,int r,int fa){
    if(l > r) return;
    int x = id[l],lst = id[fa];
    if(l == r){
        v[x] = h[x] = str[l]-'a'+1;
        f[x] = lst;size[x] = 1;
        if(l < fa) ch[lst][0] = x;
        else ch[lst][1] = x;
        return;
    }
    int mid = (l + r) >> 1;x = id[mid];
    build(l,mid-1,mid);build(mid+1,r,mid);
    v[x] = str[mid]-'a'+1;f[x] = lst;pushup(x);
    if(mid < fa) ch[lst][0] = x;
    else ch[lst][1] = x;
}

int main(){
    scanf("%s",str+2);
    n = strlen(str+2);
    p[0] = 1;FOR(i,1,MAXN-1) p[i] = 1ll*p[i-1]*27;
    FOR(i,1,n+2) id[i] = i;
    build(1,n+2,0);cnt = n+2;root=(n+3)>>1;
    int q;read(q);
    while(q--){
        scanf("%s",op+1);
        int x,y;read(x);
        if(op[1] == 'Q'){
            read(y);
            printf("%d\n",solve(x,y));
        }
        if(op[1] == 'R'){
            scanf("%s",d+1);
            x = find(x+1);splay(x,0);
            v[root] = d[1]-'a'+1;pushup(root);
        }
        if(op[1] == 'I'){
            scanf("%s",d+1);
            insert(x,d[1]-'a'+1);
        }
    }
    return 0;
}
