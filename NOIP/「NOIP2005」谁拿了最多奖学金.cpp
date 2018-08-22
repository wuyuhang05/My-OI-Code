//
//  main.cpp
//  OI Code
//
//  Created by RainAir on 2018/6/1.
//  Copyright © 2018年 wyh. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl;

struct Student{
    std::string name;
    int money,num;

    bool operator < (const Student a) const {
        return (money == a.money) ? num < a.num : money > a.money;
    }
}s[105];

int main(int argc, const char * argv[]) {
    int N,a,b,c;
    long long sum = 0;
    char flag1,flag2;
    scanf("%d",&N);
    for(int i = 1;i <= N;i++){
        std::cin >> s[i].name >> a >> b >> flag1 >> flag2 >> c;
        //scanf("%d%d%c%c%d",&a,&b,&flag1,&flag2,&c);
        if(a > 80 && c >= 1)
            s[i].money += 8000;
        if(a > 85 && b > 80)
            s[i].money += 4000;
        if(a > 90)
            s[i].money += 2000;
        if(a > 85 && flag2 == 'Y')
            s[i].money += 1000;
        if(b > 80 && flag1 == 'Y')
            s[i].money += 850;
        s[i].num = i;
        sum += s[i].money;
        //DEBUG(s[i].money);
    }
    std::sort(s + 1,s + N + 1);
    std::cout << s[1].name << std::endl;
    printf("%d\n%lld\n",s[1].money,sum);
    return 0;
}
