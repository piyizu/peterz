#include <iostream>
#include <algorithm>

int num[10];

inline bool pass(int x){
    for(; x > 0; x /= 10)
        if(num[x % 10] - 1)
            return false;
    return true;
}

inline int len_of_num(int x){
    int cnt = 0;
    if(x)
        for(; x > 0; ++cnt, x /= 10);
    else
        cnt = 1;
    return cnt;
}

inline void print(int num, char ch){
    for(; num >= 1; putchar(ch), --num);
}

int main(){
    std::ios::sync_with_stdio(false);

    std::string s;
    std::cin >> s;
    int cnt = 0;
    for(auto &a : s)
        if(a - '0' >= 0 && a - '0' <= 9) num[a - '0'] = 1;
    for(int x = 100; x <= 999; ++x){
        if(!pass(x)) continue;
        for(int y = 10; y <= 99; ++y){
            if(!pass(y)) continue;
            if(!pass(x * (y % 10) )) continue;
            if(!pass(x * (y / 10) )) continue;
            if(!pass(x * y) ) continue;

            int len = std::max(len_of_num(x * (y / 10)) + 1, len_of_num(x * y));
            print(8, '*'); putchar('\n');
            print(len - 3, ' '); printf("%d\n", x);
            print(1, 'X'); print(len - 3, ' '); printf("%d\n", y);
            print(len, '-'); printf("\n");
            print(len - len_of_num(x * (y % 10)), ' '); printf("%d\n", x * (y % 10));
            print(len - len_of_num(x * (y / 10)) - 1, ' '); printf("%d\n", x * (y / 10));
            print(len, '-'); printf("\n");
            print(len - len_of_num(x * y), ' '); printf("%d\n********\n", x * y);

            ++cnt;
        }
    }
    printf("The number of solutions:%d\n", cnt);
    return 0;
}