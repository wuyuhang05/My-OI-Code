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

const int MAXN = 1000000+5;
const int dx[4] = {0,0,1,-1};
const int dy[4] = (1,-1,0,0);
int fac[10];

inline int code(int s[]){
    int res = 0;
    FOR(i,0,8){
        int num = 0;
        FOR(j,i+1,8) if(s[j] < s[i]) num++;
        sum += (num*fac[9-i-1]);
    }
}

struct Node{
    int f,loc;
    int s[9];

    inline void cal(){
        f = code(s);
        FOR(i,0,8) if(!s[i]) {loc = i;break;}
    }
}S,T;

bool vis[MAXN];

inline void bfs(){
    S.s = {1,2,3,4,5,6,7,8,0};
    std::queue<Node> q;q.push(S);
    while(!q.empty()){
        Node v = q.front();q.pop();
        int x = v.loc/3,y = v.loc%3;
        FOR(i,0,3){
            int xx = x + dx[i],yy = y + dy[i];
            if(xx >= 1 && xx <= 3 && yy >= 1 && yy <= 3){
                
            }
        }
    }
}

char ch[11];

int main(){
    fac[0] = 0;
    FOR(i,1,9) fac[i] = fac[i-1]*i;
    while(std::cin >> ch){
        FOR(i,0,8) T.s[i] = ch[i]-'0';T.cal();
    }
    return 0;
}
