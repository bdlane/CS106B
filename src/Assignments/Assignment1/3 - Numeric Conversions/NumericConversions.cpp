/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);

void test(int n, string expectation);
string intToStringImpl(int n);
string digitToString(int n);

int stringToInt(string str);

void test(string str, int expectation);
int stringToIntImpl(string str, int unit);
int digitToInt(char digit);

/* Main program */

int main() {
    cout << "***intToString***" << endl;
    test(0, "0");
    test(1, "1");
    test(12, "12");
    test(4358, "4358");
    test(-1, "-1");
    test(-40, "-40");

    cout << "***stringToInt***" << endl;
    test("0", 0);
    test("1", 1);
    test("12", 12);
    test("4358", 4358);
    test("-1", -1);
    test("-40", -40);
    
    return 0;
}

void test(int n, string expectation) {
    string result = intToString(n);
    cout << "intToString(" << n << ") == " << expectation << ": " << result << " " << (result == expectation ? "PASS" : "FAIL") << endl;
}

string intToString(int n) {
    int a = abs(n);
    
    string result = intToStringImpl(a);
    
    if (n < 0) {
        result = "-" + result;
    }
    
    return result;
}

string intToStringImpl(int n) {
    if (n < 10) {
        return digitToString(n);
    }
    
    int remaining = n / 10;
    int digit = n % 10;
    
    return intToString(remaining) + intToStringImpl(digit);
}

string digitToString(int n){
    return string() + char(n + '0');
}

void test(string str, int expectation) {
    int result = stringToInt(str);
    cout << "stringToInt(" << str << ") == " << expectation << ": " << result << " " << (result == expectation ? "PASS" : "FAIL") << endl;
}

int stringToInt(string str) {
    string abs = str[0] == '-' ? str.substr(1) : str;
    int sign = str[0] == '-' ? -1 : 1;
    
    return stringToIntImpl(abs, 1) * sign;
}

int stringToIntImpl(string str, int unit) {
    if (str == "") {
        return 0;
    }
    
    char digit = str.back();
    string remaining = str.substr(0, str.length() -1);
    
    return stringToIntImpl(remaining, unit * 10) + digitToInt(digit) * unit;
}

int digitToInt(char digit) {
    return digit - '0';
}
