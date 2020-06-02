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

struct SAM{
    int ch[MAXN][10],fail[MAXN],len[MAXN],rmin[MAXN];
    std::vector<int> G[MAXN];
    int tot=1,las=1,v,l;

    inline void copy(int x,int y){
        FOR(i,0,9) ch[x][i] = ch[y][i];fail[x] = fail[y];len[x] = len[y];
    }

    inline void insert(int c){
        int p = las,np = las = ++tot;len[np] = len[p]+1;
        for(;p&&!ch[p][c];p=fail[p]) ch[p][c] = np;
        if(!p) fail[np] = 1;
        else{
            int q = ch[p][c];
            if(len[q] == len[p]+1) fail[np] = q;
            else{
                int nq = ++tot;copy(nq,q);len[nq] = len[p]+1;fail[q] = fail[np] = nq;
                for(;p&&ch[p][c]==q;p=fail[p]) ch[p][c] = nq;
            }
        }
    }

    inline void dfs(int v){
        if(!rmin[v]) rmin[v] = 1e9;
        for(auto x:G[v]){
            dfs(x);
            rmin[v] = std::min(rmin[v],rmin[x]);
        }
    }

    inline void build(){
        FOR(i,1,tot) if(fail[i]) G[fail[i]].pb(i);
        dfs(1);
    }

    inline void add(int c){
        for(;v&&!ch[v][c];v=fail[v]) l = len[v];
        if(ch[v][c]){
            v = ch[v][c];l++;
        }
    }

    inline void del(){
        l--;
        if(l == len[fail[v]]) v = fail[v];
    }
}sam;

char str[MAXN];
int c[10],tc,tp;
int n;
int p[MAXN];
LL f[MAXN];
std::deque<int> q;

int main(){
    scanf("%s",str+1);FOR(i,0,9) scanf("%d",c+i);scanf("%d%d",&tc,&tp);n = strlen(str+1);
    FOR(i,1,n) sam.insert(str[i]-'0'),sam.rmin[sam.las] = i;
//    DEBUG(sam.tot);
    sam.build();sam.v = 1;
//    FOR(i,1,sam.tot) DEBUG(sam.rmin[i]);
    FOR(i,1,n){
        p[i] = p[i-1];sam.add(str[i]-'0');
        while(p[i] < i && sam.rmin[sam.v] > p[i]) sam.del(),p[i]++;
    }
    f[0] = 0;
    FOR(i,1,n){
        f[i] = f[i-1]+c[str[i]-'0'];
        while(!q.empty() && q.front() < p[i]) q.pop_front();
        if(!q.empty()) f[i] = std::min(f[i],f[q.front()]-1ll*tc*q.front()+tp+1ll*tc*i);
        while(!q.empty() && f[q.back()]-1ll*tc*q.back() >= f[i]-1ll*tc*i) q.pop_back();
        q.pb(i);
    }
    printf("%lld\n",f[n]);
    return 0;
}
