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

const int MAXN = 300000+5;

struct PAM{
    int rt0,rt1,len[MAXN],ch[MAXN][26],fail[MAXN],sz[MAXN],tot,las;
    char str[MAXN];

    inline void init(){
        FOR(i,0,tot) CLR(ch[i],0),fail[i] = sz[i] = len[i] = 0;
        tot = 2;rt0 = 1;rt1 = 2;len[rt0] = 0;len[rt1] = -1;
        fail[rt0] = fail[rt1] = rt1;las = rt1;
    }
    PAM(){tot = 0;init();}

    inline void insert(int p){
        int v = las,c = str[p]-'a';
        while(str[p-len[v]-1] != str[p]) v = fail[v];
        if(!ch[v][c]){
            ++tot;len[tot] = len[v]+2;int t = fail[v];
            while(str[p-len[t]-1] != str[p]) t = fail[t];
            fail[tot] = ch[t][c]?ch[t][c]:rt0;ch[v][c] = tot;
        }
        las = ch[v][c];++sz[las];
    }
}pam;

int main(){
    scanf("%s",pam.str+1);int n = strlen(pam.str+1);
    FOR(i,1,n) pam.insert(i);//pam.build();
    LL ans = 0;
    ROF(i,pam.tot,1) pam.sz[pam.fail[i]] += pam.sz[i];
    FOR(i,3,pam.tot) ans = std::max(ans,1ll*pam.len[i]*pam.sz[i]);//,DEBUG(pam.len[i]),DEBUG(pam.sz[i]);
    printf("%lld\n",ans);
    return 0;
}
