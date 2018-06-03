/*
ID: rain_ai1
PROG: crypt1
LANG: C++
*/
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int n,w[1000],ans=0,_pow(int);;
bool check1(int,int),check2(int,int);
int main() {
    freopen("crypt1.in","r",stdin);
    freopen("crypt1.out","w",stdout);
    scanf("%d",&n);
    for(int i=0; i<n; i++) scanf("%d",&w[i]);
    for(int i=100; i<=999; i++) {
        if(check2(i,3)) continue;
        //cout<<i<<" ";
        for(int j=10; j<=99; j++) {
            if(check2(j,2)) continue;
            if(check1(i,j)) ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
bool check1(int a,int b) {
    int m=b%10,n=b/10%10;
    int x=m*a,y=n*a;
    int z=x+y*10;
    if(x/1000!=0||y/1000!=0||z/10000!=0) return false;
    if(check2(x,3)||check2(y,3)||check2(z,4)) return false;
    return true;
}
bool check2(int a,int b){
    int s=0;
    for(int i=0;i<b;i++){
        for(int j=0;j<n;j++){
            if(a/_pow(i)%10==w[j]){
                s++;
                break;
            }
        }
    }
    if(s<b) return true;
    return false;
}
int _pow(int i){
    int s=1;
    for(int j=0;j<i;j++) s*=10;
    return s;
}
