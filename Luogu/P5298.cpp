#include<bits/stdc++.h>

#define fi first
#define se second
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

const int MAXN = 3e5 + 5;
const int ha = 998244353;
const int inv = 796898467;

int root[MAXN];

int sm[MAXN<<5],tag[MAXN<<5],ch[MAXN<<5][2];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    sm[x] = (sm[lc]+sm[rc])%ha;
}

inline void cover(int x,int d){
    sm[x] = 1ll*sm[x]*d%ha;tag[x] = 1ll*tag[x]*d%ha;
}

inline void pushdown(int x){
    if(tag[x] != 1){
        if(lc) cover(lc,tag[x]);
        if(rc) cover(rc,tag[x]);
        tag[x] = 1;
    }
}
int tot;
inline void update(int &x,int l,int r,int p,int d){
    if(!x) x = ++tot,tag[x] = 1;
    if(l == r){
        sm[x] = d;return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p,d);
    else update(rc,mid+1,r,p,d);
    pushup(x);
}

inline int merge(int x,int y,int mulx,int muly,int prob){
    if(!x && !y) return 0;
    if(!x || !y){
        cover(x+y,x?mulx:muly);
        return x+y;
    }
    pushdown(x);pushdown(y);
    int lsx = sm[lc],rsx = sm[rc],lsy = sm[ch[y][0]],rsy = sm[ch[y][1]];
    lc = merge(lc,ch[y][0],(mulx+1ll*rsy*(1+ha-prob)%ha)%ha,(muly+1ll*rsx*(1+ha-prob)%ha)%ha,prob);
    rc = merge(rc,ch[y][1],(mulx+1ll*prob*lsy%ha)%ha,(muly+1ll*lsx*prob%ha)%ha,prob);
    pushup(x);
    return x;
}

std::vector<int> G[MAXN];
int a[MAXN];
int m;

inline void dfs(int v){
    if(G[v].empty()){
        update(root[v],1,m,a[v],1);
        return;
    }
    if(G[v].size() == 1){
        dfs(G[v][0]);
        root[v] = root[G[v][0]];
        return;
    }
    dfs(G[v][0]);dfs(G[v][1]);
    root[v] = merge(root[G[v][0]],root[G[v][1]],0,0,a[v]);
}

int n;
int ans[MAXN];
inline void Dfs(int x,int l,int r){
    if(!x) return;
    if(l == r){
        ans[l] = sm[x];
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(x);
    Dfs(lc,l,mid);Dfs(rc,mid+1,r);
}
std::vector<int> S;
int main(){
    assert(1ll*inv*10000%ha==1);
    scanf("%d%*d",&n);
    FOR(i,2,n){
        int f;scanf("%d",&f);G[f].pb(i);
    }
    FOR(i,1,n){
        scanf("%d",a+i);
        if(!G[i].empty()) a[i] = 1ll*a[i]*inv%ha;
        else S.pb(a[i]);
    }
    std::sort(all(S));m = (int)S.size();
    FOR(i,1,n) if(G[i].empty()) a[i] = std::lower_bound(all(S),a[i])-S.begin()+1;
    dfs(1);Dfs(root[1],1,m);
    int res = 0;
    FOR(i,1,m) (res += 1ll*i*S[i-1]%ha*ans[i]%ha*ans[i]%ha) %= ha;
    printf("%d\n",res);
    return 0;
}
/*
 * f[i][j]: i 点的权值是 j 的概率
 * f[i][j] = f[x][j]*(p[i]*(\sum_{k < j} f[y][k])+(1-p[i])*(\sum_{k > j} f[y][k])) + f[y][j]*(p[i]*(\sum_{k < j}f[x][k])+(1-p[i])*(\sum_{k > j} f[x][k]))
 * 线段树合并完成这个的过程比较有意思：递归的时候记录一下两棵树目前分别要整体乘多少 左子树合并的时候把右子树的贡献乘上 右边同理
 */
