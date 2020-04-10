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
const int MAXM = 100+5;

namespace MCMF{
    struct Edge{
        int fr,to,w,c,nxt;
    }e[MAXN<<1];
    int head[MAXN],cnt=1;

    inline void add(int u,int v,int w,int c){
        e[++cnt] = (Edge){u,v,w,c,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){v,u,0,-c,head[v]};head[v] = cnt;
    }

    int dis[MAXN],pre[MAXN];
    bool inq[MAXN];
    int N,S,T;

    inline bool spfa(){
        std::queue<int> q;
        FOR(i,0,N) dis[i] = 1e9,pre[i] = -1;
        dis[S] = 0;pre[S] = 0;q.push(S);inq[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            inq[v] = 0;
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].w > 0 && dis[e[i].to] > dis[v]+e[i].c){
//                    DEBUG(e[i].to);DEBUG(e[i].c);
                    dis[e[i].to] = dis[v]+e[i].c;pre[e[i].to] = i;
                    if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = 1;
                }
            }
        }
        return pre[T]!=-1;
    }

    int maxFlow,minCost;

    inline void work(){
        while(spfa()){
            int flow = 1e9;
            for(int v = T;v != S;v = e[pre[v]].fr){
                flow = std::min(flow,e[pre[v]].w);
            }
            maxFlow += flow;
            for(int v = T;v != S;v = e[pre[v]].fr){
                minCost += flow*e[pre[v]].c;
                e[pre[v]].w -= flow;
                e[pre[v]^1].w += flow;
            }
        }
    }
}
using namespace MCMF;

int n,m;

inline int calc(int i,int j,int k){
    return k*n*m+(i-1)*m+j;
}
int d[MAXN];
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
class CurvyonRails{
public:
    int getmin(std::vector<std::string> a){
        n = a.size();m = a[0].length();
        N = calc(n,m,2);int s = ++N,t = ++N;S = ++N;T = ++N;
        FOR(i,1,n){
            FOR(j,1,m){
                if(a[i-1][j-1] == 'w') continue;
                if((i+j)&1) d[s] += 2,d[calc(i,j,0)] -= 2;
                else d[calc(i,j,0)] += 2,d[t] -= 2;
                int w = (a[i-1][j-1] == 'C');
                if((i+j)&1){
                    add(calc(i,j,0),calc(i,j,1),1,0);add(calc(i,j,0),calc(i,j,1),1,w);
                    add(calc(i,j,0),calc(i,j,2),1,0);add(calc(i,j,0),calc(i,j,2),1,w);
                    if(i-1 > 0 && a[i-2][j-1] != 'w') add(calc(i,j,1),calc(i-1,j,1),1,0);
                    if(i+1 <= n && a[i][j-1] != 'w') add(calc(i,j,1),calc(i+1,j,1),1,0);
                    if(j-1 > 0 && a[i-1][j-2] != 'w') add(calc(i,j,2),calc(i,j-1,2),1,0);
                    if(j+1 <= m && a[i-1][j] != 'w') add(calc(i,j,2),calc(i,j+1,2),1,0);
                }
                else{
                    add(calc(i,j,1),calc(i,j,0),1,0);add(calc(i,j,1),calc(i,j,0),1,w);
                    add(calc(i,j,2),calc(i,j,0),1,0);add(calc(i,j,2),calc(i,j,0),1,w);
                }
            }
        }
        int sm = 0;
        FOR(i,1,N-2){
            if(d[i] > 0) add(i,T,d[i],0);
            if(d[i] < 0) add(S,i,-d[i],0),sm -= d[i];
        }
        add(t,s,1e9,0);
        work();
//        DEBUG(sm);DEBUG(maxFlow);
        if(sm != maxFlow) return -1;
        return minCost;
    }
};
/*
 * 想到拆点 然后连(1,0) 和(1,1) 来控制两个边走在一起答案+1
 * 所以每个点拆成三个点 在拆后的点之间连关系
 */
#ifdef RainAir
int main(){
    CurvyonRails test;
    printf("%d\n",test.getmin({"CC..CCCw.CwC..CC.w.C", "C.CCCwCCC.w.w..C.w..", "wwww...CC.wC.Cw.CC..", "CC..CC.w..w.C..CCCC.", "CC.CCC..CwwCCC.wCC..", "w.C..wwCC.CC.wwwCC..", ".CC.CC..CCC..CC.CC.C", "Cw....C.C.CCC...CC..", "CC.C..Cww.C.CwwwC..w", "wCCww..C...CCCCCCC.w", "C.CCw.CC.ww...C.CCww", "C.C.C.CCwCC..wCCw.Cw", "CCC.C...w..C.wC.wCCw", "CC.C..C..CCC.CC.C...", "C.ww...CCC..CC...CCC", "...CCC.CwwwC..www.C.", "wwCCCCC.w.C.C...wCwC", "CCwC.CwCCC.C.w.Cw...", "C.w.wC.CC.CCC.C.w.Cw", "CCw.CCC..C..CC.CwCCw", "C.wwwww.CwwCCwwwwwww"}));
    return 0;
}
#endif
