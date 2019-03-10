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

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000+5;

struct Data{
    LL v;int pos;
    bool operator < (const Data &t) const{
        return v < t.v;
    }
};
std::priority_queue<Data> q1;
struct Node{
    LL v;int pos;
    bool operator < (const Node &t) const {
        return v > t.v;
    }
};
std::priority_queue<Node> q2;

int N,M,K;
LL a[MAXN],s[MAXN],x[MAXN],c[MAXN],ans[MAXN];
std::queue<int> bin;int p = 100000;LL tot;
std::vector<int> app[MAXN];
bool used[MAXN];LL sd[MAXN];

int main(){
    scanf("%d%d%d",&N,&M,&K);
    FOR(i,1,N) scanf("%d%d%d%d",a+i,s+i,c+i,x+i);
    FOR(i,1,N){
        if(!x[i]) app[p].push_back(i);
        else app[std::min(1ll*p,(c[i]+x[i]-1)/x[i])].push_back(i);
    }
    ROF(i,p,1){
        FOR(j,0,(int)app[i].size()-1) q1.push((Data){a[app[i][j]]+s[app[i][j]],app[i][j]});
        if(q1.empty()) continue;
        LL lim = M;
        while(lim && !q1.empty()){
            Data v = q1.top();q1.pop();
            if(!used[v.pos]){
                used[v.pos] = true;ans[p] += v.v;sd[v.pos]++;lim--;
                if(c[v.pos] != 1) q1.push((Data){a[v.pos],v.pos});
            }
            else{
                LL re = c[v.pos]-sd[v.pos]-(i-1)*x[v.pos];
                LL del = std::min(re,lim);ans[p] += del*v.v;sd[v.pos] += del;lim -= del;
                if(sd[v.pos] != c[v.pos]) bin.push(v.pos);
            }
        }
        for(;!bin.empty();bin.pop()) q1.push((Data){a[bin.front()],bin.front()});
    }
    FOR(i,1,N){
        if(sd[i] == 1) q2.push((Node){s[i]+a[i],i});
        else if(sd[i]) q2.push((Node){a[i],i});
        tot += sd[i];
    }
    ROF(i,p-1,1){
        ans[i] = ans[i+1];if(tot <= M*i) continue;
        int lim = tot-M*i;
        while(lim && !q2.empty()){
            Node v = q2.top();q2.pop();
            if(sd[v.pos] != 1){
                LL del = std::min(1ll*lim,sd[v.pos]-1);
                sd[v.pos] -= del;lim -= del;ans[i] -= del*v.v;
                if(sd[v.pos] == 1) q2.push((Node){s[v.pos]+a[v.pos],v.pos});
                else q2.push((Node){a[v.pos],v.pos});
            }
            else{
                lim--;sd[v.pos]--;ans[i] -= v.v;
            }
        }
        tot = M*i;
    }
    while(K--){
        int x;scanf("%d",&x);printf("%lld\n",ans[x]);
    }
    return 0;
}