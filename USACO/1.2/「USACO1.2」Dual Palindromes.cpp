/*
ID: wuyuhan5
PROG: dualpal
LANG: C++
*/
#include <iostream>
#include <cstring>
#include <cstdio>

int N,S;

int pd[100 + 5];

bool check(int x,int n){
    int len;
    for(len = 0;x != 0;len++){
        pd[len] = x % n;
        x /= n;
    }
    for(int i = 0;i < len;i++)
        if(pd[i] != pd[len - i - 1])
            return false;
    return true;
}

int main(){
    freopen("dualpal.in","r",stdin);
    freopen("dualpal.out","w",stdout);
    scanf("%d%d",&N,&S);
    for(int i = S + 1;N;i++){
        int cnt = 0;
        for(int j = 2;j <= 10;j++)
            if(check(i,j)) cnt++;
        if(cnt >= 2){
            printf("%d\n",i);
            N--;
        }
    }
    getchar();getchar();
    return 0;
}
