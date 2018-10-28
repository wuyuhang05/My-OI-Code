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

int L;
char xl[20],str[100];
char a[100],b[100],c[100];
std::map<char,int> mp;
std::stack<std::pair<char,int> > S;

inline int getnum(char str[],int pos=1){
    int len = strlen(str+1),ret=0;
    if(str[1] == 'n') return INT_MAX;
    FOR(i,pos,len){
        if(str[i] < '0' || str[i] > '9') return ret;
        ret = ret * 10 + str[i] - '0';
    }
    return ret;
}

#define MP std::make_pair

inline void Solve(){
    scanf("%d%s",&L,xl+1);
    int cnt=0,f=0;mp.clear();
    while(!S.empty()) S.pop();
    bool err=false;
    int depth=0;
    FOR(i,1,L){
        scanf("%s",str +1);
        if(str[1]== 'F'){
            scanf("%s%s%s",a+1,b+1,c+1);
            if(mp[a[1]]){
                err=true;
            }
            int x = getnum(b),y = getnum(c);//DEBUG(x);DEBUG(y);
            int js = (x > y) ? 0 : ((x != INT_MAX && y == INT_MAX) ? 1 : 2); // 0:no 2:chang shu 1: n
            if(!S.empty()) js = S.top().second == 0 ? 0 : js;
            mp[a[1]]++;S.push(MP(a[1],js));
            if(js == 1) f++;
            if(S.top().second) cnt = std::max(cnt,f);
        }
        if(str[1] == 'E'){
            if(S.empty()){
                err=1;
                continue;
            }
            mp[S.top().first]--;
            if(S.top().second == 1) f--;
            if(S.top().second) cnt = std::max(cnt,f);
            S.pop();
        }
        // if(!S.empty()) DEBUG(S.top().second);
    }
    if(!S.empty()) err = true;
    int cur;
    if(xl[3] == '1') cur=0;
    cur = getnum(xl,5);
    if(err){
        puts("ERR");
        return;
    }
    if(cur == cnt) puts("Yes");
    else puts("No");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
