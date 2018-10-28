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

const int MAXN = 1000+1;

struct BigInt{
#define MAXL 1000+5
    int num[MAXL],len;

    BigInt(){
        len=0;
        CLR(num,0);
    }

    BigInt(int a){
        len=1;
        num[1] = a;
    }

    void read(){
        char str[MAXL];
        scanf("%s",str+1);
        this->len = strlen(str+1);
        FOR(i,1,this->len){
            this->num[i] = str[len-i+1]-'0';
        }
    }

    inline void clear(){
        this->len = 0;
    }

    inline void print(){
        if(!this->len) puts("0");
        ROF(i,this->len,1) putchar(this->num[i] + '0');
        puts("");
    }

    BigInt operator + (const BigInt &other) const {
        BigInt ret;ret.clear();
        ret.len = std::max(this->len,other.len);
        FOR(i,1,ret.len){
            ret.num[i] += this->num[i] + other.num[i];
            ret.num[i+1] = ret.num[i]/10;
            ret.num[i]%=10;
        }
        //DEBUG(ret.num[ret.len+1]);
        if(ret.num[ret.len+1]) ret.len++;
        return ret;
    }

    BigInt operator - (const BigInt &other) const {
        BigInt ret = *this;
        FOR(i,1,ret.len){
            ret.num[i] -= other.num[i];
            if(ret.num[i] < 0){
                ret.num[i]+=10;
                ret.num[i+1]--;
            }
        }
        while(ret.len && !ret.num[ret.len]) ret.len--;
        return ret;
    }

    int operator % (int ha) const {
        int ret = 0;
        ROF(i,this->len,1) ret = (10ll * ret + this->num[i])%ha;
        return ret;
    }

    bool operator > (const BigInt &other) const {
        if(this->len != other.len) return this->len > other.len;
        ROF(i,this->len,1)
            if(this->num[i] != other.num[i]) return this->num[i] > other.num[i];
        return false; // =
    }
#undef MAXL
}f[MAXN+5];

const int ha = 258280327;

int main(){
    f[1] = f[2] = BigInt(1);
    FOR(i,3,MAXN) f[i] = f[i-1]+f[i-2];
    //FOR(i,1,MAXN) f[i].print();
    int T;scanf("%d",&T);
    while(T--){
        int notuse;
        scanf("%d",&notuse);
        BigInt n;n.read();
        BigInt n1;n1 = n + BigInt(1);
        FOR(i,1,MAXN+1){
            //f[i].print();
            if(f[i] > n1){
                n = n-f[i-2];
                printf("%d\n",n%ha);
                break;
            }
        }
    }
    return 0;
}