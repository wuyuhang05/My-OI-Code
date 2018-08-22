#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 300000 + 5;
const int logN = 24;

inline void Read(int &x){
    x = 0;
    int flag = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-') flag = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    x *= flag;
}

struct Edge{
    int to,w,next;
}e[MAXN * 2];

int Max = 0;

int head[MAXN],cnt;
int N,M;
int f[MAXN][30 + 5],deep[MAXN],dist[MAXN],topre[MAXN],p[MAXN];

inline void add(int u,int v,int w){
    e[cnt] = Edge{v,w,head[u]};
    head[u] = cnt++;
    e[cnt] = Edge{u,w,head[v]};
    head[v] = cnt++;
}

void dfs(int v,int fa){
    p[++cnt] = v;
    for(int i = 1;i < logN;i++){
        f[v][i] = f[f[v][i-1]][i-1];
        if(!f[v][i]) break;
    }
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to != fa){
            dist[e[i].to] = dist[v] + e[i].w;
            deep[e[i].to] = deep[v] + 1;
            f[e[i].to][0] = v;
            topre[e[i].to] = e[i].w;
            dfs(e[i].to,v);
        }
    }
}

int lca(int x,int y){
    if(deep[x] > deep[y])
        std::swap(x,y);
    for(int i = logN-1;i >= 0;i--)
        if(deep[x] <= deep[f[y][i]])
            y = f[y][i];
    for(int i = logN-1;i >= 0;i--){
        if(f[x][i] != f[y][i]){
            x = f[x][i];
            y = f[y][i];
        }
    }
    if(x != y) x = f[x][0];
    return x;
}
int a[MAXN],b[MAXN],l[MAXN],d[MAXN],cf[MAXN];
bool checker(int k){
    memset(cf,0,sizeof(cf));
    cnt = 0;
    for(int i = 1;i <= M;i++){
        if(d[i] > k){
            cf[a[i]]++;
            cf[b[i]]++;
            cf[l[i]]-=2;
            cnt++;
        }
    }
    for(int i = N;i >= 1;i--){
        cf[f[p[i]][0]] += cf[p[i]];
        if(topre[p[i]] >= Max - k && cf[p[i]] == cnt) return true;
    }
    return false;
}

int Binary_Search(int L,int R){
    int mid;

    while(L < R){
        mid = (L + R) >> 1;
        if(checker(mid))
            R = mid;
        else L = mid + 1;
    }
    return L;
}

int main(){
    Read(N);Read(M);
    int Max1 = 0;
    for(int u,v,w,i = 1;i < N;i++){
        Read(u);Read(v);Read(w);
        add(u,v,w);
        Max1 = std::max(w,Max1);
    }
    cnt = 0;
    deep[1] = 1;deep[0] = -1;
    dfs(1,0);
    for(int i = 1;i <= M;i++){
        Read(a[i]);Read(b[i]);
        l[i] = lca(a[i],b[i]);
        d[i] = dist[a[i]] + dist[b[i]] - (dist[l[i]] << 1);
        Max = std::max(Max,d[i]);
    }
    int ans = Binary_Search(Max - Max1, Max + 1);
    printf("%d\n",ans);
    return 0;
}
