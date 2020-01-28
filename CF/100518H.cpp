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

const int MAXN = 10000+5;

struct Node{
    int u,v,id;

    bool operator < (const Node &t) const {
        return u+v < t.u+t.v;
    }
};

inline bool cmp(const Node &a,const Node &b){
    return a.u == b.u ? a.v < b.v : a.u < b.u;
}

std::priority_queue<Node> q;
std::vector<Node> v;
int n,l[MAXN],f[MAXN],tot;
char ans[MAXN][MAXN],ch[MAXN];
bool vis[MAXN];

inline bool Solve(){
    tot = n;
    while(!q.empty()){
        v.clear();v.push_back(q.top());q.pop();
        int len = v[0].u + v[0].v;
        if(q.empty()) return len == 0;
        while(!q.empty()){
            Node t = q.top();
            if(t.u + t.v == len) v.push_back(t),q.pop();
            else break;
        }
        int sz = v.size();
        if(sz & 1) return 0;
        std::sort(v.begin(),v.end(),cmp);
        int j = 1;
        FOR(i,0,sz-1) vis[i] = false;
        FOR(i,0,sz-1){
            if(vis[i]) continue;
            j = std::max(j,i+1);
            while(j < sz && v[j].u <= v[i].u) ++j;
            if(j == sz) return 0;
            if(v[j].u != v[i].u+1 || v[j].v != v[i].v-1) return 0;
            f[v[i].id] = ++tot;ch[v[i].id] = '1';
            f[v[j].id] = tot;ch[v[j].id] = '0';
            vis[i] = vis[j] = true;
            q.push((Node){v[i].u,v[j].v,tot});
            j++;
        }
    }
    return true;
}

int main(){
    freopen("huffman.in","r",stdin);
    freopen("huffman.out","w",stdout);
    while(~scanf("%d",&n) && n){
        while(!q.empty()) q.pop();
        if(n == 1){
            int u,v;scanf("%d%d",&u,&v);
            puts(u+v == 1 ? (u ? "0" : "1") : ("No"));
            continue;
        }
        FOR(i,1,n){
            int u,v;scanf("%d%d",&u,&v);
            l[i] = u+v;
            q.push((Node){u,v,i});
        }
        bool flag = Solve();
        if(!flag){puts("No");continue;}
        else{
            puts("Yes");
            FOR(i,1,n){
                int u = i;
                ans[i][l[i]] = '\0';
                while(u != tot){
                    //DEBUG(ch[u]);
                    ans[i][--l[i]] = ch[u];
                    u = f[u];
                }
                printf("%s\n",ans[i]);
            }
        }
    }
    return 0;
}
/*
3
1 0
0 2
1 1
7
1 1
2 1
3 0
1 1
1 2
1 3
0 4
2
1 1
1 1
0
*/