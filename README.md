# Cypherock Submission

## Shamir's Secret Sharing Protocol [Galois Field: 256]

### Modules:
#### source
-   sss_distribution: key sharing module
-   sss_combine: find the original secret using shared keys
-   util: utility functions for Galois Field    

#### test_cases
- input(i).txt: "i"th test case input file
- intermediate_input(X).txt: "X"th (random number X) intermediate input file (for combining the shared keys, to retrieve the original secret)

#### outputs
- secrets(X).txt: contains shared secrets

### How to Run:
Make sure you have g++ installed.

```bash
g++ main.cpp
./a.out < test_cases/input1.txt
./a.out < test_cases/intermediate_input(X).txt
```















Note: We have used modular arithmetic instead of using ilog/log Tables which could be used to find modular inverse.

Author: Gajanan Gitte
