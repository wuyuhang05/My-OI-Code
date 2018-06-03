#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

const int MAXN = 1000000 + 5;

char str1[MAXN],str2[MAXN];
int Next[MAXN];
std::vector <int> Ans;

inline void init(char *str){
    int len,t;
    len = strlen(str);
    Next[0] = -1;
    for(int i = 1;i < len;i++){
        t = Next[i-1];
        while(str[t + 1] != str[i] && t >= 0)
            t = Next[t];
        if(str[t + 1] == str[i])
            Next[i] = t + 1;
        else
            Next[i] = -1;
    }
}

void kmp(char *str1,char *str2){
    init(str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int i = 0,j = 0;
    while(j < len1){
        if(str2[i] == str1[j]){
            i++;j++;
            if(i == len2){
                Ans.push_back(j - len2 + 1);
                i = Next[i-1] + 1;
            }
        }
        else{
            if(!i) j++;
            else i = Next[i-1] + 1;
        }
    }
}

int main(){
    scanf("%s%s",str1,str2);
    int l = strlen(str2);
    kmp(str1,str2);
    for(int i = 0;i < Ans.size();i++)
        printf("%d%c",Ans[i],'\n');
    for(int i = 0;i < l;i++)
        printf("%d ",Next[i] + 1);
    //getchar();getchar();
    return 0;
}
