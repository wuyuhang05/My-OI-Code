#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;

const int MAXN = 100 + 5;
char ch[MAXN];
int f[MAXN][MAXN];

int main(){
    scanf("%s",ch);
    int n = strlen(ch);
    for(int i = 1;i <= n;i++) f[i][i] = 1;
    for(int p = 1;p < n;p++){
        for(int i = 1;i <= n - p;i++){
            int j = i + p;
            //if(j > n) break;
            f[i][j] = INT_MAX;
            if((ch[i-1] == '(' && ch[j-1] == ')') || (ch[i-1] == '[' && ch[j-1] == ']'))
                f[i][j] = f[i+1][j-1];
            if(ch[i-1] == '(' || ch[i-1] == '[')
                f[i][j] = min(f[i][j],f[i][j-1] + 1);
            if(ch[j-1] == ')' || ch[j-1] == ']')
                f[i][j] = min(f[i][j],f[i+1][j] + 1);
            for(int k = i;k < j;k++){
                f[i][j] = min(f[i][k] + f[k+1][j],f[i][j]);
            }
        }
    }
    printf("%d",f[1][n]);
    getchar();getchar();
    return 0;
}
