#include <iostream>
#include <cstdio>
#include <cstring>

#define LL long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 30 + 5;
const int MAXL = 26 + 5;

LL C[MAXN][MAXN];
std::string str;

int main(){
    for(int i = 0;i < MAXL;i++)
        for(int j = 0;j <= i;j++)
            if(!j || i == j)
                C[i][j] = 1;
            else
                C[i][j] = C[i-1][j] + C[i-1][j-1];
    while(std::cin >> str){
        int L = str.length();
        for(int i = 1;i < L;i++)
            if(str[i-1] >= str[i]){
                printf("0\n");
                return 0;
            }
        LL ans = 0;
        for(int i = 1;i < L;i++)
            ans += C[26][i];
        for(int i = 0;i < L;i++){
            char ch = (!i) ? 'a' : str[i-1] + 1;
            while(ch <= str[i] - 1){
                ans += C['z'-ch][L-i-1];
                ch++;
            }
        }
        printf("%lld\n",ans + 1);
    }
    return 0;
}
