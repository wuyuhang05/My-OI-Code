#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 800+5;
const int ha = 1e9 + 7;
const int MAXM = 2e5 + 5;

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

int L[MAXN][MAXN],U[MAXN][MAXN]; // (i,j) 左边的边
int n,m;

struct Node{
    int f,g; // f-> min  g->sum
    Node(int f=1e9,int g=0) : f(f),g(g) {}

    inline Node operator + (const Node &t) const {
        if(f < t.f) return (*this);
        if(f > t.f) return t;
        return Node(f,(g+t.g)%ha);
    }

    inline Node operator + (const int &x) const {
        return Node(f+x,g);
    }

    inline Node operator * (const int &x) const {
        return Node(f,1ll*g*x%ha);
    }
}F[2][MAXN];
int now;
std::map<int,int> id;
int tot;
std::vector<int> rID[MAXM];

inline int encode(std::vector<int> a){
    int res = 0;
    FOR(i,0,m-1) res = (res<<3)|a[i];
    return res;
}

inline int ID(std::vector<int> a){
    int t = encode(a);
    if(!id.count(t)) id[t] = ++tot,rID[tot] = a;
    return id[t];
}
int tmp[10];
inline std::vector<int> trans(std::vector<int> a){
    CLR(tmp,0);int tot = 0;
    FOR(i,0,m-1){
        if(!a[i]) continue;
        if(!tmp[a[i]]) tmp[a[i]] = ++tot;
        a[i] = tmp[a[i]];
    }
    return a;
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,0,n-1) FOR(j,1,m-1) scanf("%d",&L[i][j]);
    FOR(i,1,n-1) FOR(j,0,m-1) scanf("%d",&U[i][j]);
    tot = 0;id.clear();
    F[now = 0][ID(std::vector<int>(m,0))] = Node(0,1);
    FOR(i,0,n-1){
        FOR(j,0,m-1){
            int up = tot;
            FOR(k,1,up){
                if(F[now][k].f == 1e9) continue;
                std::vector<int> S = rID[k];
                std::vector<int> nxt = S;
                int l = !j ? 0 : S[j-1],u = S[j];
                int cnt = 0;
                for(auto x:S) if(x == u) cnt++;
                if(!i) ++cnt;
                if(cnt >= 2){ //都不连
                    nxt[j] = 9;
                    int t = ID(trans(nxt));
                    F[now^1][t] = F[now^1][t]+F[now][k];
                    nxt = S;
                }
                // 连左边
                if(j && cnt >= 2){
                    nxt[j] = l;
                    int t = ID(trans(nxt));
                    F[now^1][t] = F[now^1][t]+((F[now][k]+L[i][j])*2);
                    nxt = S;
                }
                // 连上边
                if(i){
                    F[now^1][k] = F[now^1][k]+((F[now][k]+U[i][j])*2);
                }
                // 都连
                if(i && j && l != u){
                    for(auto &x:nxt) if(x == u) x = l;
                    int t = ID(trans(nxt));
                    F[now^1][t] = F[now^1][t]+((F[now][k]+U[i][j]+L[i][j])*3);
                }
            }
            FOR(i,1,tot) F[now][i] = Node(1e9,0);
            now ^= 1;
        }
    }
    Node ans = F[now][ID(std::vector<int>(m,1))];
    printf("%d %d\n",ans.f,ans.g);
}

int main(){
    int T;scanf("%d",&T);
    FOR(i,1,T) printf("Case #%d: ",i),Solve();
    return 0;
}