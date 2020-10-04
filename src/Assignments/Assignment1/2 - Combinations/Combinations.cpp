/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int c(int n, int k);
void test(int n, int k, int expectation);

int main() {
    
    test (0, 0, 1);
    test (1, 1, 1);
    test (2, 1, 2);
    test (4, 2, 6);
    test (6, 2, 15);
    test (4, 4, 1);

    return 0;
}

void test(int n, int k, int expectation) {
    int result = c(n, k);
    cout << "c(" << n << ", " << k << ") == " << expectation << ": " << result << " " << (result == expectation ? "PASS" : "FAIL") << endl;
}

int c(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    
    return c(n - 1, k - 1) + c(n - 1, k);
}
