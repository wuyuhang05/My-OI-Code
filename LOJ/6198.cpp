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

const int MAXN = 2e5 + 5;
const int MAXM = 17;
int ch[MAXN*(MAXM+1)][2],tot;
int bin[MAXN*(MAXM+1)],tp;

inline int New(){
    if(tp){
        ch[bin[tp]][0] = ch[bin[tp]][1] = 0;
        return bin[tp--];
    }
    else return ++tot;
}
char str[MAXN];int n;
struct Node{
    std::vector<int> G;
    int rt;

    inline void insert(int x){
        if(!rt) rt = New();
        G.pb(x);int v = rt;
        ROF(i,MAXM,0){
            int t = (x>>i)&1;
            if(!ch[v][t]) ch[v][t] = New();
            v = ch[v][t];
        }
    }

    inline void del(int &v){
        if(!v) return;
        del(ch[v][0]);del(ch[v][1]);
        bin[++tp] = v;v = 0;
    }

    inline int query(int x){
        int res = 0,v = rt;
//        assert(v != 0);
        if(!G.size()) return -1e9;
        ROF(i,MAXM,0){
            int t = (x>>i)&1;
            if(ch[v][t^1]) v = ch[v][t^1],res |= (1<<i);
            else v = ch[v][t];
        }
        return res;
    }
}T[MAXN];

struct SA{
    int sa[MAXN],tp[MAXN],tax[MAXN],rk[MAXN];
    int M;
    int H[MAXN];

    inline void sort(){
        FOR(i,0,M) tax[i] = 0;
        FOR(i,1,n) tax[rk[i]]++;
        FOR(i,1,M) tax[i] += tax[i-1];
        ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
    }

    inline void build(){
        M = 26;
        FOR(i,1,n) rk[i] = str[i]-'a'+1,tp[i] = i;
        sort();
        for(int w=1,p=0;p<n;M=p,w<<=1){
            p = 0;
            FOR(i,1,w) tp[++p] = n-w+i;
            FOR(i,1,n) if(sa[i] > w) tp[++p] = sa[i]-w;
            sort();std::swap(rk,tp);
            rk[sa[p = 1]] = 1;
            FOR(i,2,n) rk[sa[i]] = tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+w]==tp[sa[i-1]+w]?p:++p;
        }
        int j = 0;
        FOR(i,1,n){
            if(j) --j;
            while(str[i+j] == str[sa[rk[i]-1]+j]) ++j;
            H[rk[i]] = j;
        }
    }
}sa;
int a[MAXN];
int f[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}
std::vector<int> G[MAXN];
int nows,ans = 0;

inline void merge(int x,int y){
    x = find(x);y = find(y);
    if(x == y) return;
    if(T[x].G.size() < T[y].G.size()) std::swap(x,y);
    T[y].del(T[y].rt);
    for(auto val:T[y].G){
        ans = std::max(ans,nows+T[x].query(val));
        T[x].insert(val);
    }
    T[y].G.clear();
    f[y] = x;
}

int main(){
    scanf("%d",&n);scanf("%s",str+1);
    FOR(i,1,n) scanf("%d",a+i),T[i].insert(a[i]);std::iota(f+1,f+n+1,1);
    sa.build();
    FOR(i,1,n) G[sa.H[i]].pb(i);
    ROF(i,n-1,0){
        nows = i;
        for(auto x:G[i]){
            if(sa.sa[x-1]&&sa.sa[x]) merge(sa.sa[x-1],sa.sa[x]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
