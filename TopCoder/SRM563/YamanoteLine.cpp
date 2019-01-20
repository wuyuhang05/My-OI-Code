#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50+10;
LL f[MAXN][MAXN][205];
int max;

class YamanoteLine{
    public:
    inline void add(int u,int v,int k,int w){
        f[u][v][k+max] = std::min(f[u][v][k+max],1ll*w);
    }
    public:
    LL howMany(int N,std::vector<int> S1,std::vector<int> T1,std::vector<int> L1,std::vector<int> S2,std::vector<int> T2,std::vector<int> L2){
        FOR(i,1,N) FOR(j,1,N) FOR(k,0,204) f[i][j][k] = LLONG_MAX;
        max = N;
        FOR(i,0,N) f[i][i][max] = 0;
        FOR(i,0,N-1) add(i+1,i,0,-1);
        add(N,0,-1,0);add(0,N,1,0);
        int k = (int)S1.size()-1;
        FOR(i,0,k){
            int s = S1[i],t = T1[i],l = L1[i];
            if(s < t) add(t,s,0,-l);
            else add(t,s,1,-l);
        }
        k = S2.size()-1;
        FOR(i,0,k){
            int s = S1[i],t = T1[i],l = L1[i];
            if(s < t) add(s,t,0,l);
            else add(s,t,-1,l);
        }
        FOR(k,0,N){
            FOR(i,0,N){
                FOR(x,-max,max){
                    if(f[i][k][x+max] < LLONG_MAX){
                        FOR(j,0,N){
                            FOR(y,std::max(-max,-max-x),std::min(max,max-x)){
                                if(f[k][j][y+max] < LLONG_MAX){
                                    f[i][j][x+y+max] = std::min(f[i][j][x+y+max],f[i][k][x+max]+f[k][j][y+max]);
                                }
                            }
                        }
                    }
                }
            }
        }
        FOR(i,0,N) if(f[i][i][max] < 0) return 0ll;
        LL L = N,R = LLONG_MAX;
        FOR(s,1,max){
            FOR(i,0,N){
                if(f[i][i][s+max]<LLONG_MAX) L = std::max(L,(LL)((-f[i][i][s+max]-1)/s+1));
            }
        }
        FOR(s,-max,-1){
            FOR(i,0,N){
                if(f[i][i][s+max]<LLONG_MAX) R = std::min(R,(LL)f[i][i][s+max]/(-s));
            }
        }
        return L > R ? 0 : ((R == LLONG_MAX) ? -1 : R-L+1);
    }
};
/*
int main(){
    std::vector<int> a,b,c,d,e,f;
    int n;scanf("%d",&n);
    int l1;scanf("%d",&l1);
    FOR(i,1,l1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        a.push_back(u);b.push_back(v);c.push_back(w);
    }
    scanf("%d",&l1);
    FOR(i,1,l1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        d.push_back(u);e.push_back(v);f.push_back(w);
    }
    printf("%lld\n",YamanoteLine.howMany(n,a,b,c,d,e,f));
    return 0;
}*/