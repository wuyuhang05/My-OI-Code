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
#define LD long double
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 6;
const int MAXC = 100+5;
int n,len,alphabet;
bool vis[MAXN];

struct Matrix{
    LD a[MAXC][MAXC];
    Matrix operator * (const Matrix &t) const {
        Matrix ans;
        FOR(i,0,MAXC-1){
            FOR(j,0,MAXC-1){
                ans.a[i][j] = 0.0;
                FOR(k,0,MAXC-1){
                    ans.a[i][j] += a[i][k]*t.a[k][j];
                }
            }
        }
        return ans;
    }

    Matrix operator ^ (int n) const {
        Matrix res,a = *this;
        FOR(i,0,MAXC-1) FOR(j,0,MAXC-1) res.a[i][j] = (i == j);
        while(n){
            if(n & 1) res = res*a;
            a = a*a;
            n >>= 1;
        }
        return res;
    }
}a,b;

const int MAXL = MAXN*16000;

namespace AC{
    int tag[MAXL],ch[MAXL][26],cnt = 1,fail[MAXL];

    inline void insert(char str[]){
        int len = strlen(str+1),v = 1;
        FOR(i,1,len){
            int x = str[i]-'a';
            if(!ch[v][x]) ch[v][x] = ++cnt;
            v = ch[v][x];
        }
        tag[v] = 1;
    }

    inline void build(){
        std::queue<int> q;
        q.push(1);
        while(!q.empty()){
            int v = q.front();q.pop();
            tag[v] |= tag[fail[v]];
            int pos;
            FOR(i,0,alphabet-1){
                pos = fail[v];
                while(pos && !ch[pos][i]) pos = fail[pos];
                if(ch[v][i]){
                    fail[ch[v][i]] = pos ? ch[pos][i] : 1;
                    q.push(ch[v][i]);
                }
                else ch[v][i] = pos ? ch[pos][i] : 1;
            }
        }
    }

    inline void calc(){
        std::queue<int> q;
        q.push(1);vis[1] = true;
        while(!q.empty()){
            int v = q.front();q.pop();
            FOR(i,0,alphabet-1){
                if(!vis[ch[v][i]]) vis[ch[v][i]] = 1,q.push(ch[v][i]);
                if(tag[ch[v][i]]){
                    a.a[v][cnt+1] += (LD)1.0/alphabet;
                    a.a[v][1] += (LD)1.0/alphabet;
                }
                else a.a[v][ch[v][i]] += (LD)1.0/alphabet;
            }
        }
        a.a[cnt+1][cnt+1] = 1;
    }
}

char str[MAXN][20];

int main(){
    scanf("%d%d%d",&n,&len,&alphabet);
    FOR(i,1,n) scanf("%s",str[i]+1),AC::insert(str[i]);
    AC::build();AC::calc();
    b = a^len;
    printf("%.6Lf\n",b.a[1][AC::cnt+1]);
    return 0;
}
