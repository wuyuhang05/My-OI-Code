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

#define read(x) std::cin >> x;

const int MAXN = 200 + 5;
std::string str;
int N;
int num[26+5],nw[26+5];
bool f[MAXN][MAXN];
std::set<std::string> S;

inline bool check(int len,std::string s){
    memset(f,0,sizeof(f));
    FOR(i,1,N) f[i][i-1] = 1;
    FOR(l,1,N){
        for(R int i = 1;i+l-1 <= N;i++){
            int j = i+l-1;
            if(f[i][j-1] && s[(l-1)%len] == str[j])
                f[i][j] = 1;
            else
                for(R int k = 1;k*len <= l;k++)
                    if(f[i][j-k*len] && f[j-k*len+1][j])
                        f[i][j] = 1;
        }
    }
    return f[1][N];
}

inline void solve(){
    read(str);
    N = str.length();
    str = " " + str;
    CLR(num,0);
    FOR(i,1,N) num[str[i]-'a']++;
    FOR(l,1,N){
        if(N%l) continue;
        S.clear();
        for(R int i = 1;i + l - 1 <= N;i++){
            int j = i + l - 1;
            bool flag = 1;
            CLR(nw,0);
            FOR(k,i,j)
                nw[str[k]-'a']++;
            FOR(k,0,25)
                if(N/l*nw[k] != num[k]){
                    flag = 0;
                    break;
                }
            if(flag)
                S.insert(str.substr(i,l));
        }
        for(std::set<std::string>::iterator it = S.begin();it != S.end();it++){
            std::string t = *it;
            if(check(l,t)){
                std::cout << t << std::endl;
                return;
            }
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--)
        solve();
    return 0;
}
