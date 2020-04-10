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

namespace Flow{
    struct Edge{
        int to,w,nxt;
    }e[MAXN<<1];
    int head[MAXN],cur[MAXN],cnt=1;
    int dep[MAXN];
    int S,T,N;

    inline void add(int u,int v,int w){
        e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
    }

    inline bool bfs(){
        FOR(i,0,N) cur[i] = head[i],dep[i] = 0;
        std::queue<int> q;q.push(S);dep[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].w > 0 && !dep[e[i].to]){
                    dep[e[i].to] = dep[v] + 1;
                    if(e[i].to == T) return true;
                    q.push(e[i].to);
                }
            }
        }
        return dep[T];
    }

    inline int dfs(int v,int flow=1e9){
        if(v == T) return flow;
        if(!flow) return 0;
        int ans = 0;
        for(int &i = cur[v];i;i = e[i].nxt){
            if(e[i].w > 0 && dep[e[i].to] == dep[v] + 1){
                int t = dfs(e[i].to,std::min(flow,e[i].w));
                if(t>0){
                    ans += t;flow -= t;
                    e[i].w -= t;e[i^1].w += t;
                    if(!flow) break;
                }
            }
        }
        return ans;
    }

    inline int Dinic(){
        int ans = 0,t = 0;
        while(bfs()) while((t=dfs(S))) ans += t;
        return ans;
    }
};
using namespace Flow;

int n,m;

inline int calc(int i,int j,int k){
    return k*n*m+(i-1)*m+j;
}

inline int val(char s){
    if(!isdigit(s)) return 0;
    return s-'0';
}

class LaserTowersDiv1{
public:
    int countMaxEnemies(std::vector<std::string> a){
        n = a.size();m = a[0].length();N = calc(n,m,1);S = ++N;T = ++N;// 没有传递性 需要拆点
        FOR(i,1,n){
            FOR(j,1,m){
                char c = a[i-1][j-1];
                if(c == '.' || ('1' <= c && c <= '9')){
                    add(calc(i,j,0),calc(i,j,1),1e9);
                }
            }
        }
        int ans = 0;
        FOR(i,1,n){
            FOR(j,1,m){
                char c = a[i-1][j-1];
                int mx = 0;
                if(c == 'A'){
                    int las = calc(i,j,0);add(las,T,1e9);
                    ROF(k,i-1,1){
                        mx = std::max(mx,val(a[k-1][j-1]));
                    }
                    ROF(k,i-1,1){
                        add(calc(k,j,1),las,mx-val(a[k][j-1]));
                        las = calc(k,j,1);
                    }
                }
                if(c == 'V'){
                    int las = calc(i,j,0);add(las,T,1e9);
                    FOR(k,i+1,n){
                        mx = std::max(mx,val(a[k-1][j-1]));
                    }
                    FOR(k,i+1,n){
                        add(calc(k,j,1),las,mx-val(a[k-2][j-1]));
                        las = calc(k,j,1);
                    }
                }
                if(c == '<'){
                    int las = calc(i,j,0);add(S,las,1e9);
                    ROF(k,j-1,1){
                        mx = std::max(mx,val(a[i-1][k-1]));
                    }
                    ROF(k,j-1,1){
                        add(las,calc(i,k,0),mx-val(a[i-1][k]));
                        las = calc(i,k,0);
                    }
                }
                if(c == '>'){
                    int las = calc(i,j,0);add(S,las,1e9);
                    FOR(k,j+1,m){
                        mx = std::max(mx,val(a[i-1][k-1]));
                    }
                    FOR(k,j+1,m){
                        add(las,calc(i,k,0),mx-val(a[i-1][k-2]));
                        las = calc(i,k,0);
                    }
                }
                ans += mx;
            }
        }
//        DEBUG(ans);
        int t = Dinic();//DEBUG(t);
        return ans-t;
    }
};

#ifdef RainAir
int main(){
    LaserTowersDiv1 test;
    printf("%d\n",test.countMaxEnemies({ ".9V.", ">..7", ".A1." }));
    return 0;
}
#endif
