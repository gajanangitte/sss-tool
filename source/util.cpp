#include<iostream>
#include<algorithm>
#include <utility>
#include<assert.h>

using namespace std;
#define GF 256

int gf_add(int a, int b) {
    return (a%GF + b%GF)%GF;
}


int gf_mul(int a, int b) {
    return (a%GF * b%GF)%GF;
}

// modular exponentiation
int gf_pow(int a, int b) {
    a = (a % GF);
    if(b == 0)
        return 1;
    int res = 1;

    while(b > 0) {
        if(b%2==1) {
            res = gf_mul(res, a);
            b--;
        }
        else {
            b/=2;
            a = gf_mul(a,a);
        }
    }
    return res;
}

int gf_mod(int a) {
    if(a < 0)
        while(a < 0) a+=GF;
    return a%GF;    
}

int mod_mul_frac(int a, pair<int, int> p) {
    int res = 1;
    res = a * p.first;
    int gcd = __gcd(res, p.second);
    res /= gcd;
    p.second /= gcd;

    // assert(res == (p.second*(res/p.second)));

    return (res/p.second)%GF;
}

// Tables to be used later
//int gf_inv()