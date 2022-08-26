/*
*   Added here are the used learning resources:
*   
*   https://www.cs.purdue.edu/homes/hmaji/teaching/Fall%202020/lectures/08.pdf
*   
*
*   The finite field with pn elements is denoted 
*   GF(pn) and is also called the Galois 
*   field of order pn, in honor of the founder 
*   of finite field theory, Évariste Galois. GF(p), 
*   where p is a prime number, is simply the ring of
*   integers modulo p.
*
*
*   https://www.youtube.com/watch?v=FUdEpUoA4mc
*/
#include "./source/sss_distribution.cpp"
#include "./source/sss_combine.cpp"

#include<iostream>
#include <assert.h>
#include<string.h>

using namespace std;

// GF(2^8) => 256bits 1 byte, we can use char 

int main(int argc, char **argv) {

    int _secret_len;
    int _total_shares;
    int _threshold_shares;
    string op;

    
    if(argc != 4 && argc != 1) {
        cout<<"\n[ERROR] Invalid number of arguments !!!\n"<<endl;
        exit(1);
    } 
    else if(argc == 4) {
        op = argv[1];
        _secret_len = atoi(argv[2]);
        _total_shares = atoi(argv[3]);
        _threshold_shares = atoi(argv[4]);
    }
    else {
        cout<<"[INPUT] Enter the operation to be performed (e for encode, d for decode): ";
        cin>>op;
        cout<<"\n[INPUT] Enter the length of the secret key (Press Enter after every input): ";
        cin>>_secret_len;
        cout<<"\n[INPUT] Enter total number of shares for your secret: ";
        cin>>_total_shares;
        cout<<"\n[INPUT] Enter the number of threshold shares for your secret: ";
        cin>>_threshold_shares;

        assert(_total_shares >= _threshold_shares);
        assert(_threshold_shares > 1);
    }


    if(op == "e") {
        int _secret[_secret_len];
        cout<<"\n[INPUT] Enter the secret key: (Sequence of integers with value between 0 to 255) :";
        for(int i = 0; i < _secret_len; i++) {
            cin>>_secret[i];
        }

        use_sss(_secret_len, _total_shares, _threshold_shares, _secret);
    }
    else if(op == "d") {
        int num_shares;
        
        cout<<"\n[INPUT] Enter the number of shares you possess: ";
        cin>>num_shares;

        int _shares[num_shares][_secret_len+1];
        cout<<"\n[INPUT] Enter the secret keys: (Sequence of integers with value between 0 to 255) :";
        
        for(int i=0; i<num_shares; i++) {
            cout<<"\nKey "<<i<<" :";
            for(int j=0; j<_secret_len+1; j++)
                cin>>_shares[i][j];
        }
        cout<<"\n";
        assert(num_shares >= _threshold_shares);

        decode_sss(_secret_len, _threshold_shares, num_shares, (int*)_shares );
    }
    else {
    cout<<"\n[ERROR] Invalid operation. Select 'd' or 'e' !!!\n"<<endl;
    }

    return 0;
}