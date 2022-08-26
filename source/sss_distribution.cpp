#pragma once
#include "util.cpp"

#include <iostream>
#include <cstdlib>
#include <fstream>

#define SEED 1
#define GF 256

using namespace std;


int calculate_polynomial_value(int x,  int y0, int* coefficients) {
    
    int y_val = y0%GF;
    int num = sizeof(coefficients)/sizeof(coefficients[0]);

    for(int i = 0; i < num; i++) {
        y_val = gf_add(y_val, gf_mul(coefficients[i], gf_pow(x, i+1)));

    }
    return y_val;
}

void fill_coefficients(int* coefficients) {
    int n = sizeof(coefficients)/sizeof(int);

    for(int i = 0; i < n; i++) {
        coefficients[i] = rand()%GF;
    }
}

void polynomify(int _index, int _secret_len, int _total_shares, int constant, int* coefficients, int* shares) {


    int sum = 0;
    int n = sizeof(coefficients)/sizeof(int);
    for(int i = 0; i < _total_shares; i++) {
       shares[i*_secret_len+_index] = calculate_polynomial_value( i+SEED, constant, coefficients  );
    }
}


void use_sss(int _secret_len, int _total_shares, int _threshold_shares, int _secret[]) {
    
    int shares[_total_shares][_secret_len];
    int coefficients [_threshold_shares-1];


    for(int i = 0; i < _secret_len; i++) {
        int constant = _secret[i];
        fill_coefficients(coefficients);
        polynomify(i, _secret_len, _total_shares, constant, coefficients, (int* )shares);
    }

    srand(unsigned (time(0)));
    char temp = rand()%26+98;
    string str = to_string(temp);
    ofstream output_f("outputs/secrets"+str+".txt"), input_f("test_cases/intermediate_input"+str+".txt");
    input_f<<"d\n"<<_secret_len<<"\n"<<_total_shares<<"\n"<<_threshold_shares<<"\n"<<_threshold_shares<<"\n";

    for(int i = 0; i < _total_shares; i++) {
        cout<<"\nKey "<<i+1<<": [ ";
        output_f <<i+1<<" ";
        input_f <<i+1<<" ";
        for(int j=0; j < _secret_len-1; j++) {
            cout<<shares[i][j]<<", ";
            output_f <<shares[i][j]<<" ";
            input_f <<shares[i][j]<<" ";
        }
        cout<<shares[i][_secret_len-1]<<"] ";
        output_f<<shares[i][_secret_len-1]<<endl;
        input_f<<shares[i][_secret_len-1]<<endl;
    }
    cout<<endl;
    output_f.close();
    input_f.close();
}