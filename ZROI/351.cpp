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
const int MAXN = 100000 + 5;
std::string a,b,c;
int ans[MAXN];

int main(){
    std::cin >> a >> b >> c;
    while(a.length() < b.length()){
        a = '0' + a;
    }
    while(b.length() < a.length()){
        b = '0' + b;
    }
    int t = a.length();
    if(c == "or"){
        FOR(i,0,t-1){
            int x = a[i]-'0',y = b[i]-'0';
            ans[i] = (x|y);
        }
    }
    else if(c == "and"){
        FOR(i,0,t-1){
            int x = a[i]-'0',y = b[i]-'0';
            ans[i] = (x&y);
        }
    }
    else{
        FOR(i,0,t-1){
            int x = a[i]-'0',y = b[i]-'0';
            ans[i] = (x^y);
        }
    }
    bool flag = true;
    FOR(i,0,t-1){
        if(ans[i]) flag = false;
        if(flag) continue;
        printf("%d",ans[i]);
    }
    return 0;
}