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

const int MAXN = 330 + 5;

int n,a[MAXN][MAXN],len[MAXN];
std::string plan[MAXN];
int ans[MAXN];

struct Trie{
    const int root = 1;
    int ch[MAXN*MAXN][26],dep[MAXN*MAXN],tot = 1;

    int insert(int x,int c){
        if(!ch[x][c]) dep[ch[x][c] = ++tot] = dep[x] + 1;
        return ch[x][c];
    }

    std::vector<int> v[MAXN*MAXN];
    std::string s;

    void dfs(int x){
        for(auto i:v[x]) plan[i] = s;
        FOR(i,0,25){
            if(ch[x][i]){
                s.pb(i+'a');
                dfs(ch[x][i]);
                s.pop_back();
            }
        }
    }

    void read(){
        FOR(i,1,n) v[ans[i]].pb(i);
        dfs(root);
    }
}trie;

std::vector<int> mat[MAXN];

namespace Step1{
    int nxt[MAXN][MAXN][26];
    void bfs(int x){
        std::queue<std::pair<int,int> > q;
        q.push(MP(1,0));
        int tot = 0;
        while(!q.empty() && tot <= n){
            std::pair<int,int> v = q.front();q.pop();
            if(v.fi != 1) mat[x].pb(v.fi);
            FOR(i,0,25){
                if(nxt[x][v.se+1][i] <= len[x]){
                    q.push(MP(trie.insert(v.fi,i),nxt[x][v.se+1][i]));
                    tot++;
                }
            }
        }
        while(!q.empty()){
            mat[x].pb(q.front().fi);q.pop();
        }
    }

    void Solve(){
        FOR(i,1,n){
            FOR(j,0,25) nxt[i][len[i]+1][j] = len[i]+1;
            ROF(j,len[i],1){
                memcpy(nxt[i][j],nxt[i][j+1],sizeof(nxt[i][j]));
                nxt[i][j][a[i][j]] = j;
            }
        }
        FOR(i,1,n) bfs(i);
    }
};

namespace Step2{
    const int MAXN = 1000000+5;
    int head[MAXN],cnt=1;
    struct Edge{
        int to,c,next;
    }e[MAXN<<2];

    inline void add(int u,int v,int c){
      //  printf("%d %d %d\n",u,v,c);
        e[++cnt] = (Edge){v,c,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
    }

    int level[MAXN],S,T;

    inline bool bfs(){
        std::queue<int> q;q.push(S);
        CLR(level,0);level[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            for(int i = head[v];i;i = e[i].next){
                int to = e[i].to;
                if(!level[to] && e[i].c > 0){
                    level[to] = level[v] + 1;
                    if(to == T) return true;
                    q.push(to);
                }
            }
        }
        return false;
    }

    inline int dfs(int v,int limit=INT_MAX){
        if(v == T) return limit;int flow;
        for(int i = head[v];i;i = e[i].next){
            int to = e[i].to;
            if(level[to] == level[v] + 1 && e[i].c > 0){
                if((flow = dfs(to,std::min(limit,e[i].c)))){
                    e[i].c -= flow;e[i^1].c += flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    inline int Dinic(){
        int ans = 0,flow;
        while(bfs()){
            while((flow = dfs(S))) ans += flow;
        }
    //    DEBUG(ans);
        return ans;
    }
    int tot = 0;
    inline int Solve(int k){
        ++tot;S = 0;T = 1;cnt = 1;CLR(head,0);
        FOR(i,1,n) add(S,i+1,1);
        FOR(i,2,trie.tot){
            if(trie.dep[i] <= k) add(i+n,T,1);
        }
        FOR(i,1,n){
            for(auto x:mat[i]){
                if(trie.dep[x] <= k){
                    add(i+1,x+n,1);
                }
            }
        }
        return Dinic();
    }

    void getans(){
        FOR(i,1,n){
            for(int j = head[i+1];j;j = e[j].next){
                if(!e[j].c && e[j].to > n){
                    ans[i] = e[j].to - n;
                    break;
                }
            }
        }
    }
};

int main(){
    scanf("%d",&n);std::string s;
    FOR(i,1,n){
        std::cin >> s;len[i] = s.length();
        FOR(j,0,len[i]-1){
            a[i][j+1] = s[j]-'a';
        }
    }
    Step1::Solve();
  //  DEBUG(Step2::Solve(1));DEBUG(Step2::Solve(1));return 0;
    if(Step2::Solve(300) != n){
        puts("-1");
        return 0;
    }
    int l = 1,r = 301;
    while(l < r){
        int mid = (l + r) >> 1;
        if(Step2::Solve(mid) < n) l = mid+1;
        else{
            Step2::getans();
            r = mid;
        }
    }
    printf("%d\n",l);
    trie.read();
    FOR(i,1,n) std::cout << plan[i] << std::endl;
    return 0;
}
