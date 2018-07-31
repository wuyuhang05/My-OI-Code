#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

const int MAXN = 1000000 + 5;

int next[MAXN];
char s1[MAXN],s2[MAXN];
std::vector<int> ans;

inline void init(char *str){
    int len,t;
    len = strlen(str);
    next[0] = -1;
    for(int i = 1;i < len;i++){
        t = next[i-1];
        while(str[t + 1] != str[i] && t >= 0)
            t = next[t];
        if(str[t + 1] == str[i])
            next[i] = t + 1;
        else next[i] = -1;
    }
}

void kmp(char *str1,char *str2){
    init(str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int i = 0,j = 0;
    while(i < len1){
        if(str1[i] == str2[j]){
            i++;j++;
            if(j == len2){
                ans.push_back(i - len2 + 1);
                j = next[j-1] + 1;
            }
        }
        else{
            if(!j) i++;
            else j = next[j-1] + 1;
        }

    }
}

int main(){
    scanf("%s%s",s1,s2);
    int len = strlen(s2);
    kmp(s1,s2);
    for(int i = 0;i < ans.size();i++){
        printf("%d\n",ans[i]);
    }
    for(int i = 0;i < len;i++)
        printf("%d%c",next[i] + 1,(i == len-1) ? '\n' : ' ');
    getchar();getchar();
    return 0;
}