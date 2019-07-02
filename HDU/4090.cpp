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

int n,m,k;

struct Node{
    int a[9][9];
    Node(){
        CLR(a,0);
    }
};

int ans;
const int dx[8] = {0,0,1,-1,1,-1,1,-1};
const int dy[8] = {1,-1,0,0,1,-1,-1,1};

inline int calc(const Node &s){
    int r[10] = {0};
    FOR(i,1,k) r[i] = 0;
    FOR(i,1,n) FOR(j,1,m) r[s.a[i][j]]++;
    int res = 0;
    FOR(i,1,k) res += r[i]*r[i];
    return res;
}

inline int dfs(Node &t,int x,int y,int d,Node &p){
    int cnt = 1;t.a[x][y] = p.a[x][y] = 0;
    FOR(i,0,7){
        int xx = x + dx[i],yy = y + dy[i];
        if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && t.a[xx][yy] == d)
            cnt += dfs(t,xx,yy,d,p);
    }
    return cnt;
}


inline void change1(Node &t){
    FOR(i,1,m){
        int pos = n;
        ROF(j,n,1){
            if(!t.a[j][i]) continue;
            t.a[pos][i] = t.a[j][i];
            if(pos != j) t.a[j][i] = 0;
            --pos;
        }
    }
}

inline void change2(Node &t){
    int pos = 1;
    FOR(i,1,m){
        bool flag = false;
        FOR(j,1,n) if(t.a[j][i]) {flag = true;break;}
        if(flag){
            FOR(j,1,n){
                t.a[j][pos] = t.a[j][i];
                if(pos != i) t.a[j][i] = 0;
            }
            ++pos;
        }
    }
}

inline void Solve(Node &s,int sum){
    if(sum + calc(s) <= ans) return;
    Node t = s,p = s;
    FOR(i,1,n){
        FOR(j,1,m){
            if(!t.a[i][j] || !p.a[i][j]) continue;
            int res = dfs(t,i,j,t.a[i][j],p);
            if(res >= 3){
                change1(t);change2(t);
                ans = std::max(ans,sum+res*res);
                Solve(t,sum+res*res);
            }
            t = s;
        }
    }
}

int main(){
    while(~scanf("%d%d%d",&n,&m,&k)){
        Node s;
        FOR(i,1,n) FOR(j,1,m) scanf("%d",&s.a[i][j]);
        Node t = s;
        ans = 0;Solve(s,0);
        printf("%d\n",ans);
    }
    return 0;
}
