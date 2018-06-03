/*
PROG: palsquare
ID: wuyuhan5
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>

inline void pc(int x){
    //return (x >= 0 && x <= 9) ? x + '0' : x - 10 + 'A';
    if(x >= 0 && x <= 9) putchar(x + '0');
    else putchar(x - 10 + 'A');
}

int b;

struct Num{
    int a[25];
    int l;
    Num(int x){
        for(l = 0;x;l++){
            a[l] = x % b;
            x /= b;
        }
    }
    bool check(){
        for(int i = 0;i < l;i++)
            if(a[i] != a[l-i-1]) return false;
        return true;
    }
    void print(){
        for(int i = l-1;i >= 0;i--)
            pc(a[i]);
    }
};

int main(){
    freopen("palsquare.in","r",stdin);
    freopen("palsquare.out","w",stdout);
    scanf("%d",&b);
    for(int i = 1;i <= 300;i++){
        Num a(i * i);
        if(a.check()){
            Num b(i);
            b.print();putchar(' ');
            a.print();putchar('\n');
        }
    }
    getchar();getchar();
    return 0;
}
