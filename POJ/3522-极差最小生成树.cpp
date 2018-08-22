#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

//const int MAXM = 10000 * 2
const int INF = 0x3f3f3f3f;
const int MAXN = 100 + 5;

struct Edge{
    int u,v,w;

    bool operator < (const Edge &b) const{
        return w < b.w;
    }

    Edge(int u=0,int v=0,int w=0) : u(u), v(v), w(w) {}
};

std::vector<Edge> e;

int f[MAXN];
int N,M;

int find(int x){
    if(x == f[x]) return x;
    return f[x] = find(f[x]);
}

void init(){
    for(int i = 1;i <= N;i++)
        f[i] = i;
}

int main(){
    //freopen("std.in","r",stdin);
    while(std::cin >> N >> M){
        if(N == 0 && M == 0) break;
        e.clear();
        for(int u,v,w,i = 0;i < M;i++){
            scanf("%d%d%d",&u,&v,&w);
            e.push_back(Edge(u,v,w));
        }
        std::sort(e.begin(),e.end());
        int ans = INF;
        for(int i = 0;i <= M - N + 1;i++){
            init();
            int count = 0;
            for(int j = i;j < M;j++){
                int f1 = find(e[j].u);
                int f2 = find(e[j].v);
                if(f1 != f2){
                    f[f1] = f2;
                    count++;
                }
                if(count == N - 1){
                    ans = std::min(ans,e[j].w-e[i].w);
                    break;
                }
            }
        }
        if(ans == INF) puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}
