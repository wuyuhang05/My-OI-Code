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
std::vector<int> G[MAXN];
char str[MAXN];

struct PAM{
    int ch[MAXN][26],len[MAXN],fail[MAXN],tot,rt0,rt1,las;
    inline void init(){
        FOR(i,0,tot) CLR(ch[i],0),fail[i] = len[i] = 0;
        tot = 2;len[rt0 = 1] = 0;len[rt1 = 2] = -1;
        las = fail[rt0] = fail[rt1] = rt1;
    }
    PAM(){tot = 0;init();}

    inline void insert(int p){
        int v = las,c = str[p]-'a';
        while(str[p-len[v]-1] != str[p]) v = fail[v];
        if(!ch[v][c]){
            ++tot;len[tot] = len[v]+1;int t = v;
            while(str[p-len[t]-1] != str[p]) t = fail[t];
            fail[tot] = ch[t][c]?ch[t][c]:rt0;ch[v][c] = tot;
        }
        las = ch[v][c];
    }

    inline void build(){
        FOR(i,1,tot) G[fail[i]].pb(i);
    }
}pam;
std::map<int,int> S;
int ans = 0;
inline void dfs(int v){
    if((pam.len[v]&1) == 0 && S[pam.len[v]/2] != 0) ans = std::max(ans,pam.len[v]);
    S[pam.len[v]] = v;
    for(auto x:G[v]){
        dfs(x);
    }
    S.erase(pam.len[v]);
}

int main(){
    int n;scanf("%d%s",&n,str+1);
    FOR(i,1,n) pam.insert(i);pam.build();
    dfs(pam.rt1);printf("%d\n",ans);
    return 0;
}
