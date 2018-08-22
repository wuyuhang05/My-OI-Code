#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

const double fb = 0.6180339887498949;
const int MAXN = 30000 + 5;

double ans = 9999999999999.9;

int N,x,y;
double a[MAXN];

inline int Search(double k,int i){
    int L = i + 1,R = N;
    while(L <= R){
        int mid = (L + R) >> 1;
        if(a[mid] <= k) L = mid + 1;
        else R = mid - 1;
    }
    double d = fabs(a[L] - k);
    double b = fabs(a[L - 1] - k);
    double c = fabs(a[L + 1] - k);
    if(d < b && d < c)
        return L;
    if(b < d && b < c) return L - 1;
    return L + 1;
}

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)
        scanf("%lf",&a[i]);
    std::sort(a + 1,a + N + 1);
    for(int i = 1;i <= N;i++){
        double b = (a[i] / (fb));
        int k = Search(b,i);
        double t = fabs((a[i]/a[k]) - fb);
        if(t < ans){
            ans = t;
            x = a[i];
            y = a[k];
        }
    }
    printf("%d\n%d\n",x,y);
    return 0;
}
