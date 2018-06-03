#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXL = 1000000 + 5;

char str1[MAXL],str2[MAXL];
int next[MAXL],s[MAXL],cnt;

inline void init(char *s){
    next[0] = -1;
    int t,len = strlen(s);
    for(int i = 1;i < len;i++){
        t = next[i-1];
        while(s[t + 1] != s[i] && t >= 0)
            t = next[t];
        if(s[t + 1] == s[i])
            next[i] = t + 1;
        else
            next[i] = -1;
    }
}

inline void kmp(char str1[],char str2[]){
    init(str2);
    int i,j;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    i = j = 0;
    while(j < len1){
        if(str1[j] == str2[i]){
            i++,j++;
            if(i == len2){
                s[++cnt] = j-len2+1;
                i = next[i-1] + 1;
            }
        }
        else{
            if(i == 0) j++;
            else i = next[i-1]+1;
        }
    }
}

int main(){
    scanf("%s%s",str1,str2);
    int len = strlen(str2);
    kmp(str1,str2);
    for(int i = 1;i <= cnt;i++)
        printf("%d\n",s[i]);
    for(int i = 0;i < len;i++)
        printf("%d ",next[i] + 1);
    return 0;
}
