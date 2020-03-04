/*
考虑给每个位置赋上一个权值：第一次出现 0 否则是和上一个出现该数的差
我们重新定义===运算表示同构，那么我们对于每个 $i$ 要么这个距离相等 要么都是第一次出现才可以。
显然这个东西是有传递性的
我们考虑如何在 AC 自动机上快速判断这两种情况：第一种情况直接判断就可以，第二种需要比较当前串长和距离的关系
我们枚举输入的 S 的每个后缀 在AC 自动机上找有没有对应的字符串可以。第二种情况实际上是比较 AC 自动机上的点所代表的串的长度（深度）和当前 S 的 d。
*/
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;
std::map<int,int> ch[MAXN];
int fail[MAXN],dep[MAXN],rt=1,tot=1;
bool ok[MAXN];
int len;

inline void insert(int str[]){
    int v = rt;
    FOR(i,1,len){
        int x = str[i];
        if(!ch[v].count(x)) ch[v][x] = ++tot;
        v = ch[v][x];
    }ok[v] = 1;
}

inline void build(){
    std::queue<int> q;
    for(auto x:ch[rt]){
        q.push(x.se);dep[x.se] = 1;fail[x.se] = rt;
    }
    while(!q.empty()){
        int v = q.front();q.pop();
        for(auto x:ch[v]){
            q.push(x.se);dep[x.se] = dep[v] + 1;fail[x.se] = rt;
            int p = fail[v];
            while(p){
                if(ch[p].count(x.fi)){
                    fail[x.se] = ch[p][x.fi];
                    break;
                }
                else if(ch[p].count(0) && x.fi >= dep[p]+1){
                    fail[x.se] = ch[p][0];
                    break;
                }
                p = fail[p];
            }
        }
    }
}

int n;
char str[MAXN];
int d[MAXN];
int sm[2333];

int main(){
    // DEBUG(1);
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%s",str+1);len = strlen(str+1);CLR(sm,-1);
        FOR(i,1,len){
            if(sm[str[i]] == -1) d[i] = 0;
            else d[i] = i-sm[str[i]];
            sm[str[i]] = i;
        }
        insert(d);
    }
    build();
    int q;scanf("%d",&q);
    while(q--){
        scanf("%s",str+1);len = strlen(str+1);CLR(sm,-1);
        int v = rt;bool ans = false;
        FOR(i,1,len){
            if(sm[str[i]] == -1) d[i] = 0;
            else d[i] = i-sm[str[i]];
            sm[str[i]] = i;
            bool flag = false;
            while(v){
                if(ch[v].count(d[i])){
                    v = ch[v][d[i]];flag = true;
                    break;
                }
                else if(ch[v].count(0) && d[i] >= dep[v]+1){
                    v = ch[v][0];flag = true;
                    break;
                }
                v = fail[v];
            }
            if(!flag) v = rt;
            if(ok[v]){
                ans = true;break;
            }
        }
        puts(ans ? "Yes" : "No");
    }
    return 0;
}