/*
 * File: ComputingAverages.cpp
 * ----------------
 */

#include <iostream>
#include <fstream>
#include "simpio.h"
#include "vector.h"
#include "filelib.h"

using namespace std;

void averageValueInFile(string filename, double& result);
void test(string filename, double expected);
void printResult(string filename, double expected, double result);
double stringToDouble(string str);

int main() {
    test("input1.txt", 1);
    test("input2.txt", 15.75);
    return 0;
}

void test(string filename, double expected) {
    double result = 0;
    averageValueInFile(filename, result);
    printResult(filename, expected, result);
}

void printResult(string filename, double expected, double result) {
    cout << "File: " << filename << ", expected " << expected << ", got " << result << " [" << (expected == result ? "PASS" : "FAIL") << "]" << endl;
}

void averageValueInFile(string filename, double& result) {
    ifstream file(filename);
    Vector<string> lines;
    readEntireFile(file, lines);
    file.close();
    int total = 0;
    for(int i = 0; i < lines.size(); i++) {
        total += stringToDouble(lines[i]);
    }
    result = (double)total / lines.size();
}

double stringToDouble(string str) {
    istringstream stream(str);
    double value;
    stream >> value >> ws;
    return value;
}
