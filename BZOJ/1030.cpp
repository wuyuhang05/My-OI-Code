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

const int MAXN = 100+5;
const int ha = 10007;

int ch[60*MAXN][27],fail[60*MAXN],f[105][60*MAXN],cnt=1;
bool tag[MAXN*60];
char str[MAXN*10];

inline void insert(char str[]){
    int v = 1,len = strlen(str+1);
    FOR(i,1,len){
        int x = str[i]-'A';
        if(!ch[v][x]) ch[v][x] = ++cnt;
        v = ch[v][x];
    }
    tag[v] = true;
}

inline void build(){
    std::queue<int> q;q.push(1);
    while(!q.empty()){
        int v = q.front();q.pop();
        FOR(i,0,25){
            if(ch[v][i]){
                int t = fail[v];
                while(!ch[t][i]) t = fail[t];
                fail[ch[v][i]] = ch[t][i];
                if(tag[ch[t][i]]) tag[ch[v][i]] = 1;
                q.push(ch[v][i]);
            }
        }
    }
}

inline void solve(int x){
    FOR(i,1,cnt){
        if(tag[i] || !f[x-1][i]) continue;
        FOR(j,0,25){
            int k = i;
            while(!ch[k][j]) k = fail[k];
            f[x][ch[k][j]] = (f[x][ch[k][j]]+f[x-1][i])%ha;
        }
    }
}

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,0,25) ch[0][i] = 1;
    FOR(i,1,n){
        scanf("%s",str+1);
        insert(str);
    }
    build();
    f[0][1] = 1;
    FOR(i,1,m) solve(i);
    int ans2 = 1,ans1 = 0;
    FOR(i,1,m) ans2 = 1ll*ans2*26%ha;
    FOR(i,1,cnt){
        if(!tag[i]) ans1 = (ans1 + f[m][i])%ha;
    }
    printf("%d\n",(ans2-ans1+ha)%ha);
    return 0;
}
