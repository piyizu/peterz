#include <iostream>

//实现 1~1e18的三个数 a,b,p计算a*b%p 
// Created on 8th July, 2021

int main() {
    unsigned long long a, b, p, res = 0;
    std::cout << "Please input a, b and p:";
    std::cin >> a >> b >> p;
    //b = b(n) * 2^n + b(n-1) * 2^(n-1) + ... + b(1) * 2 + b(0)
    //其中，系数b(k)均只能取0或1 
    //故 a * b =  b(n) * 2^n * a + b(n-1) * 2^(n-1) * a + ... + b(1) * 2 * a + b(0) * a
    //所以 a * b % p = b(n) * 2^n * a % p + b(n-1) * 2^(n-1) * a % p + ... + b(1) * 2 * a % p + b(0) * a % p
    //即res中要么有 2^k * a % p这项，要么没有
    //快速幂思想即可运用进来 
    while(b) {
        if(b & 1)
            res = ( res + a ) % p; 
        a = a * 2 % p; //这个每次循环，无论有没有改变res，都要做 
        b >>= 1;
    }
    
    std::cout << res;
    return 0;
} 
