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
const int ha = 1e9 + 7;

char str[MAXN];

struct PAM{
    int ch[MAXN][26],fail[MAXN],sz[MAXN],len[MAXN];
    int las,tot,rt0,rt1;
    
    inline void init(){
        tot = 0;rt0 = ++tot;rt1 = ++tot;
        len[rt0] = 0;len[rt1] = -1;
        fail[rt0] = fail[rt1] = rt1;las = rt1;
    }

    inline void insert(int p){
        int v = las,c = str[p]-'a';
        while(str[p-len[v]-1] != str[p]) v = fail[v];
        if(!ch[v][c]){
            ++tot;len[tot] = len[v]+2;int t = fail[v];
            while(str[p-len[t]-1] != str[p]) t = fail[t];
            fail[tot] = ch[t][c];if(!fail[tot]) fail[tot] = rt0;
            ch[v][c] = tot;
        }
        las = ch[v][c];sz[las]++;
    }
    
    std::vector<int> G[MAXN];

    inline void dfs(int v){
        for(auto x:G[v]){
            dfs(x);sz[v] += sz[x];
        }
    }

    inline void build(){
        FOR(i,1,tot) if(fail[i] != i) G[fail[i]].pb(i);
        dfs(rt1);
    }
}T;

int n;

int main(){
    scanf("%s",str+1);n = strlen(str+1);
    T.init();
    FOR(i,1,n) T.insert(i);
    T.build();int ans = 0;
    FOR(i,3,T.tot) (ans += (1ll*T.sz[i]*(T.sz[i]-1)/2)%ha)%=ha;
    printf("%d\n",ans);
    return 0;
}
