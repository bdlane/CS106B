/*
 * File: RandomShuffle.cpp
 * ----------------
 * This program shuffles a string.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"

using namespace std;

string randomShuffle(string input);
char removeAndReturnRandomChar(string &input);

int main() {
    
    while (true) {
        cout << "Enter string to shuffle: ";
        string input = getLine();
        cout << randomShuffle(input) << endl;
    }
    return 0;
}

string randomShuffle(string input) {
    if (input.empty()) {
        return "";
    }
    char c = removeAndReturnRandomChar(input);
    return c + randomShuffle(input);
}

char removeAndReturnRandomChar(string &input) {
    int i = randomInteger(0, input.length() - 1);
    char selected = input[i];
    input.erase(i, 1);
    return selected;
}
