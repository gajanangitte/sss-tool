#pragma once

#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <fstream>

using namespace std;

int solve_secret(int num_shares, int secret_len, int idx, pair<int,int>* modular_fractions, int* shares) {
    int res = 0;
    
    for(int i = 0; i < num_shares; i++) {
        res +=  mod_mul_frac( shares[i*(secret_len +1) + idx], modular_fractions[i]);
    }

    return gf_mod(res);
}

// https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing
// Using computationally efficient approach for Lagrange coeff calc
void fill_fractions(int num_shares, int* key_idx, pair<int,int>* modular_fractions) {

    // ----------------------------------------------------------------
    // TODO: Implement tables for calc' mod inv of even finite field values
    // will fail for larger multiplications !!!!!
    
    for(int i = 0; i < num_shares; i++) {
        int res_num = 1;
        int res_dem = 1;
        
        for(int j = 0; j < num_shares; j++) {
          if(i!=j) {  
                res_num *= key_idx[j];
                res_dem *= (key_idx[j]-key_idx[i]);
                int cmf = __gcd(res_num, res_dem);
                res_num /= cmf;
                res_dem /= cmf;
            }
        }

        modular_fractions[i].first = res_num;
        modular_fractions[i].second = res_dem;
        
    }
    
    // debug
    // for (int i = 0; i < num_shares; i++) {
    //     cout<<modular_fractions[i].first<<" "<<modular_fractions[i].second<<endl;
    // }
    
}

void decode_sss(int secret_len, int threshold_shares, int num_shares, int* shares) {
    
    int secret[secret_len];
    num_shares = threshold_shares;

    int key_idx[num_shares];
    for(int i = 0; i < num_shares; i++)
        key_idx[i] = shares[i*(secret_len + 1)+ 0];

    pair<int,int> modular_fractions[num_shares];
    fill_fractions(num_shares, key_idx, modular_fractions);

    for(int i=1; i < secret_len+1; i++) {
        secret[i-1] = solve_secret(num_shares, secret_len, i, modular_fractions, shares);
    }

    // --------------------------------
    // Output section

    cout<<"The secret key was: ";
    for(int i=0; i < secret_len;i++) {
        cout<<secret[i]<<" ";
    }
    cout<<endl;
}