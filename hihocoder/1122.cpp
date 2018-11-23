#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 100000
    static char buf[SIZE],*p1=buf+SIZE,*pend=buf+SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,SIZE,stdin);
        if(p1 == pend) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;char ch = nc();
    int flag = 1;
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    x *= flag;
}

const int MAXN = 1000+5;
int N,M;
int f[MAXN][MAXN];
bool used[MAXN];int match[MAXN];

bool dfs(int v){
    FOR(i,1,N){
        if(!used[i] && f[v][i]){
            used[i] = true;
            if(!match[i] || dfs(match[i])){
                match[i] = v;
                return true;
            }
        }
    }
    return false;
}

int main(){
    read(N);read(M);
    FOR(i,1,M){
        int u,v;read(u);read(v);
        f[u][v] = true;
    }
    int ans = 0;
    FOR(i,1,N){
        CLR(used,false);
        if(dfs(i)) ans++;
    }
    printf("%d\n",ans);
    system("pause");
    return 0;
}