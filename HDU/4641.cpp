/*
 * 垃圾 OJ 卡空间 未通过测试
 */
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

const int MAXN = 5e5 + 5;
inline int merge(int,int);
int root[MAXN];

struct SAM{
    int len[MAXN],fail[MAXN];
    std::map<int,int> ch[MAXN];
    int las,tot;
//    std::vector<int> G[MAXN];

    inline void clr(){
        FOR(i,0,tot) len[i] = fail[i] = 0;//,G[i].clear();
        FOR(i,0,tot) ch[i].clear();
        las = tot = 1;
    }

    inline int insert(int c){
        int p = las,np = las = ++tot;len[np] = len[p]+1;
        for(;p&&!ch[p].count(c);p=fail[p]) ch[p][c] = np;
        if(!p) fail[np] = 1;
        else{
            int q = ch[p][c];
            if(len[q] == len[p]+1) fail[np] = q;
            else{
                int nq = ++tot;ch[nq] = ch[q];fail[nq] = fail[q];len[nq] = len[p]+1;fail[q] = fail[np] = nq;
                for(;p&&ch[p].count(c) && ch[p][c] == q;p=fail[p]) ch[p][c] = nq;
            }
        }
        return np;
    }

/*    inline void dfs(int v){
        FOR(i,0,(int)G[v].size()-1){
            int x = G[v][i];dfs(x);
            root[v] = merge(root[v],root[x]);
        }
    }

    inline void build(){
        FOR(i,2,tot) G[fail[i]].pb(i);
        dfs(1);
    }*/
}sam;

struct Node{
    int sm;
    int lc,rc;
    Node(int sm=0,int lc=0,int rc=0) : sm(sm),lc(lc),rc(rc) {}
}t[MAXN<<4];
int tot;

inline void update(int &x,int l,int r,int p,int d=1){
    t[x=++tot].sm += d;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) update(t[x].lc,l,mid,p,d);
    else update(t[x].rc,mid+1,r,p,d);
}

inline int merge(int x,int y){
    if(!x || !y) return x+y;
    int v = ++tot;
    t[v].sm = t[x].sm+t[y].sm;
    t[v].lc = merge(t[x].lc,t[y].lc);
    t[v].rc = merge(t[x].rc,t[y].rc);
    return v;
}

inline int query(int x,int l,int r,int k){
    if(!x) return -1;
    if(l == r) return k==1?l:-1;
    int mid = (l + r) >> 1;
    int ls = t[t[x].lc].sm;
    if(ls >= k) return query(t[x].lc,l,mid,k);
    else return query(t[x].rc,mid+1,r,k-ls);
}

int n,m,k;

LL cf[MAXN];
int qqq[MAXN];
char str[MAXN];
int tax[MAXN],sa[MAXN];
inline void Solve(){
    scanf("%s",str+1);
    FOR(i,1,m) qqq[i] = -1;
    FOR(i,0,sam.tot) root[i] = 0;
    FOR(i,1,tot) t[i] = Node();tot = 0;
    FOR(i,1,m){
        int opt;scanf("%d",&opt);
        if(opt == 2)qqq[i] = n;
        else{
            char t[23];scanf("%s",t);
            str[++n] = t[0];
        }
    }
    sam.clr();
    FOR(i,1,n){
        int t = sam.insert(str[i]-'a');
        update(root[t],1,n,i);
    }
    FOR(i,0,n) tax[i] = 0;
    FOR(i,1,sam.tot) tax[sam.len[i]]++;
    FOR(i,1,n) tax[i] += tax[i-1];
    FOR(i,1,sam.tot) sa[tax[sam.len[i]]--] = i;
    ROF(i,sam.tot,1) root[sam.fail[sa[i]]] = merge(root[sam.fail[sa[i]]],root[sa[i]]);
//    sam.build();
    FOR(i,0,n+233) cf[i] = 0;
    FOR(i,1,sam.tot){
        int p = query(root[i],1,n,k);
        if(p != -1) cf[p] += sam.len[i]-sam.len[sam.fail[i]];
    }
    FOR(i,1,n) cf[i] += cf[i-1];
    FOR(i,1,m){
        if(qqq[i] != -1){
            printf("%lld\n",cf[qqq[i]]);
        }
    }
}

int main(){
//    freopen("a.in","r",stdin);
//    freopen("a.out","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&k)) Solve();
    return 0;
}
