#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int dx[4] = {0,-1,0,1};
const int dy[4] = {-1,0,1,0};
const int MAXN = 50 + 5;
char dir[3] = {' ','N','K'};

int N,M;
int f[MAXN*MAXN];
int size[MAXN*MAXN];
#define lowbit(x) x&-x
int scc,max_siz=1,max_mer;

int find(int x){
    return (x == f[x]) ? x : f[x] = find(f[x]);
}

inline void init(){
    FOR(i,1,N*M){
        f[i] = i;
        size[i] = 1;
    }
}

inline int encode(int x,int y){
    return (x*M)+y;
}

inline void Union(int x,int y,int tx,int ty){
    int a = encode(x,y),b = encode(tx,ty);
    int fa = find(a),fb = find(b);
    if(fa != fb){
        --scc;
        f[fa] = fb;
        size[fb] += size[fa];
        max_siz = std::max(max_siz,size[fb]);
    }
}

bool map[MAXN][MAXN][4];

inline void Read(){
    scanf("%d%d",&M,&N);
    scc = M*N;
    init();
    FOR(i,1,N)
        FOR(j,1,M){
            int opt;scanf("%d",&opt);
            FOR(k,0,3)
                map[i][j][k] = (opt >> k & 1);
            FOR(k,0,3){
                if(!map[i][j][k]){
                    int tx = i + dx[k],ty = j + dy[k];
                    Union(i,j,tx,ty);
                }
            }
        }
}

int main(){
    Read();
    printf("%d\n%d\n",scc,max_siz);
    int ansi=0,ansj=0,ans2=0;
    FOR(j,1,M){
        RFOR(i,N,1){
            FOR(k,1,2){
                if(map[i][j][k]){
                    int xx = i + dx[k],yy = j + dy[k];
                    if(xx >= 1 && xx <= N && yy >= 1 && yy <= M){
                        int fx = find(encode(i,j)),fy = find(encode(xx,yy));
                        // DEBUG(fx);DEBUG(fy);DEBUG(size[fx]);DEBUG(size[fy]);
                        if(fx != fy && max_mer < size[fx] + size[fy]){
                            max_mer = size[fx] + size[fy];
                            ansi = i;ansj = j;ans2 = k;
                        }

                    }
                }
            }
        }
    }
    DEBUG(ansi);DEBUG(ansj);DEBUG(ans2);
    printf("%d\n%d %d %c\n",max_mer,ansi,ansj,dir[ans2]);
    return 0;
}
