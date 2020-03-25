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

struct PAM{
    int ch[MAXN][26],fail[MAXN];
    int las,tot,rt0,rt1;
    int len[MAXN],sz[MAXN];
    char str[MAXN];

    inline void init(){
        FOR(i,1,tot) {fail[i] = 0;FOR(j,0,25) ch[i][j] = 0;}
        tot = 0;
        rt0 = ++tot;rt1 = ++tot;
        len[rt0] = 0;len[rt1] = -1;
        fail[rt0] = fail[rt1] = rt1;las = rt1;
    }
    PAM(){tot = 0;init();}

    inline void insert(int p){
//        DEBUG(p);
        int v = las,c = str[p]-'a';
        while(str[p-len[v]-1] != str[p]) v = fail[v];
        if(!ch[v][c]){
            ++tot;len[tot] = len[v]+2;int t = fail[v];
            while(str[p-len[t]-1] != str[p]) t = fail[t];
            fail[tot] = ch[t][c];if(!fail[tot]) fail[tot] = rt0;
            ch[v][c] = tot;sz[tot] = sz[fail[tot]]+1;
        }
        las = ch[v][c];
    }
}pam;

int main(){
    scanf("%s",pam.str+1);int n = strlen(pam.str+1);
    FOR(i,1,n){
        pam.insert(i);int t=-1;
        printf("%d ",t = pam.sz[pam.las]);
        pam.str[i+1] = (pam.str[i+1]-97+t)%26+97;
    }
    return 0;
}
