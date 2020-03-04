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
namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

const int MAXN = 1000000+5;
char str1[MAXN],str2[MAXN];
int next[MAXN];
std::vector<int> ans;

inline void init(char *str){
    int len,j=0;
    len = strlen(str+1);
    FOR(i,2,len){
        while(j && str[i] != str[j+1]) j = next[j];
        if(str[i] == str[j+1]) j++;
        next[i] = j;
    }
}

inline void kmp(char *a,char *b){ //next->b;
    int len1 = strlen(a+1),len2 = strlen(b+1),j=0;
    FOR(i,1,len1){
        while(j && a[i] != b[j+1]) j = next[j];
        if(a[i] == b[j+1]) j++;
        if(j == len2){
            ans.push_back(i-len2+1);
            j = next[j];
        }
    }
}

int main(){
    scanf("%s%s",str1+1,str2+1);
    init(str2);
    kmp(str1,str2);
    int len = strlen(str2+1);
    FOR(i,0,(int)ans.size()-1) printf("%d\n",ans[i]);
    FOR(i,1,len) printf("%d%c",next[i],(i == len) ? '\n' : ' ');
    system("pause");
    return 0;
}