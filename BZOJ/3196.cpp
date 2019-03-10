#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 4000000+5;

int n,m,tot,maxval,ans;
int a[MAXN],size[MAXN],cnt[MAXN],ch[MAXN][2],f[MAXN],val[MAXN],root[MAXN];

inline char nc(){
    static char buf[MAXN],*p1=buf+MAXN,*p2=buf+MAXN;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,MAXN,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;char ch = nc();bool flag = false;
    while(!isdigit(ch)){
        if(ch == '-') flag = true;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

#define lc ch[x][0]
#define rc ch[x][1]

inline void clear(int x){
    size[x] = cnt[x] = lc = rc = f[x] = val[x] = 0;
}

inline void pushup(int x){
    size[x] = size[lc] + size[rc] + cnt[x];
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    f[x] = z;if(z) ch[z][ch[z][1] == y] = x;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}

inline void splay(int pos,int x,int v){
    int y,z;
    while((y = f[x]) != v){
        if((z = f[y]) != v) rotate((ch[z][1] == y) ^ (ch[y][1] == x) ? x : y);
        rotate(x);
    }
    if(!v) root[pos] = x;
}

inline void insert(int pos,int v){
    int x = root[pos];
    if(!x){
        root[pos] = x = ++tot;val[x] = v;size[x] = cnt[x] = 1;
        f[x] = lc = rc = 0;
        return;
    }
    int pre = 0;
    while("SDOI2019"){
        if(val[x] == v){
            cnt[x]++;pushup(pre);break;
        }
        pre = x;x = ch[x][v > val[x]];
        if(!x){
            x = ++tot;val[x] = v;size[x] = cnt[x] = 1;
            ch[pre][v > val[pre]] = x;
            f[x] = pre;lc = rc = 0;
            pushup(pre);break;
        }
    }
    splay(pos,x,0);
}

inline int getrank(int pos,int v){
    int x = root[pos],res = 0;
    while(x){
        if(val[x] == v) return res + size[lc];
        if(val[x] < v){
            res += size[lc] + cnt[x];
            x = rc;
        }
        else x = lc;
    }
    return res;
}

inline int find(int pos,int v){
    int x = root[pos];
    while(x){
        if(val[x] == v){
            splay(pos,x,0);
            return x;
        }
        x = ch[x][v > val[x]];
    }
    return 0;// none
}

inline int pre(int pos){
    int x = ch[root[pos]][0];
    while(rc) x = rc;return x;
}

inline void del(int pos,int v){
    int x = find(pos,v);
    if(cnt[x] > 1){
        cnt[x]--;pushup(x);return;
    }
    if(!lc && !rc){
        clear(root[pos]);root[pos] = 0;return;
        // clear(x);
    }
    if(!lc){
        int y = ch[x][1];root[pos] = y;f[y] = 0;
        return;
    }
    if(!rc){
        int y = ch[x][0];root[pos] = y;f[y] = 0;
        return;
    }
    int p = pre(pos);int old = root[pos];
    splay(pos,p,0);ch[root[pos]][1] = ch[old][1];f[ch[old][1]] = root[pos];
    clear(old);pushup(root[pos]);
}

inline int getpre(int pos,int v){
    int x = root[pos];
    while(x){
        if(val[x] < v){
            if(ans < val[x]) ans = val[x];
            x = rc;
        }
        else x = lc;
    }
    return ans;
}

inline int getsuc(int pos,int v){
    int x = root[pos];
    while(x){
        if(val[x] > v){
            if(ans > val[x]) ans = val[x];
            x = lc;
        }
        else x = rc;
    }
    return ans;
}

#undef lc
#undef rc
#define lc (x<<1)
#define rc (x<<1|1)

inline void insert(int x,int l,int r,int pos,int v){
    insert(x,v);
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) insert(lc,l,mid,pos,v);
    else insert(rc,mid+1,r,pos,v);
}

inline void getrank(int x,int l,int r,int L,int R,int v){
    if(l == L && r == R){
        ans += getrank(x,v);return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) getrank(lc,l,mid,L,R,v);
    else if(L > mid) getrank(rc,mid+1,r,L,R,v);
    else getrank(lc,l,mid,L,mid,v),getrank(rc,mid+1,r,mid+1,R,v);
}

inline void change(int x,int l,int r,int pos,int v){
    del(x,a[pos]);insert(x,v);
    if(l == r){
        a[pos] = v;return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) change(lc,l,mid,pos,v);
    else change(rc,mid+1,r,pos,v);
}

inline void getpre(int x,int l,int r,int L,int R,int v){
    if(l == L && r == R){
        ans = std::max(ans,getpre(x,v));return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) getpre(lc,l,mid,L,R,v);
    else if(L > mid) getpre(rc,mid+1,r,L,R,v);
    else getpre(lc,l,mid,L,mid,v),getpre(rc,mid+1,r,mid+1,R,v);
}

inline void getsuc(int x,int l,int r,int L,int R,int v){
    if(l == L && r == R){
        ans = std::min(ans,getsuc(x,v));return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) getsuc(lc,l,mid,L,R,v);
    else if(L > mid) getsuc(rc,mid+1,r,L,R,v);
    else getsuc(lc,l,mid,L,mid,v),getsuc(rc,mid+1,r,mid+1,R,v);
}

inline int getkth(int l,int r,int rak){
    int L = 0,R = maxval + 1;
    while(L < R){
        int mid = (L + R) >> 1;
        ans = 0;getrank(1,1,n,l,r,mid);
        if(ans < rak) L = mid+1;
        else R = mid;
    }
    return L-1;
}

int main(){
    read(n);read(m);
    FOR(i,1,n){
        read(a[i]);
        insert(1,1,n,i,a[i]);
        maxval = std::max(maxval,a[i]);
    }
    while(m--){
        int opt,x,y,z;read(opt);read(x);read(y);
        if(opt != 3) read(z);
        if(opt == 1) ans = 0,getrank(1,1,n,x,y,z),printf("%d\n",ans+1);
        if(opt == 2) printf("%d\n",getkth(x,y,z));
        if(opt == 3) change(1,1,n,x,y);
        if(opt == 4) ans = INT_MIN+1,getpre(1,1,n,x,y,z),printf("%d\n",ans);
        if(opt == 5) ans = INT_MAX,getsuc(1,1,n,x,y,z),printf("%d\n",ans);
    }
    return 0;
}