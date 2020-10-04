/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "tokenscanner.h"

using namespace std;

void testSyllableCount(string word, int expectation);
void processDocument();
string getFilename();
bool isWord(string token);
bool isSentenceMarker(string token);
int countSyllables(string token);
int countSyllablesImpl(string word, string currentVowelBlock);
bool isVowel(char c);

char head(string str);
string tail(string str);

double calculateGrade(int words, int syllables, int sentences);

// Grade calculation constants
const double c0 = -15.59;
const double c1 = 0.39;
const double c2 = 11.8;

int main() {
    testSyllableCount("me", 1);
    testSyllableCount("same", 1);
    testSyllableCount("through", 1);
    testSyllableCount("similar", 3);
    testSyllableCount("squeegee", 2);
    processDocument();
    return 0;
}

void processDocument() {
    string filename = getFilename();
    
    ifstream file(filename);
    
    TokenScanner scanner(file);
    
    scanner.ignoreWhitespace();
    scanner.addWordCharacters("'");
    
    int words = 0;
    int sentences = 0;
    int syllables = 0;
    
    while (scanner.hasMoreTokens()){
        string token = scanner.nextToken();
        
        if (isWord(token)) {
            words++;
            syllables += countSyllables(token);
//            cout << token << "(word, " << countVowels(token) << " vowels)" << endl;
        } else if (isSentenceMarker(token)){
//            cout << token << "(sentence)" << endl;
            sentences++;
        }
    }
    
    file.close();
    
    cout << "Words: " << words << endl;
    cout << "Sentences: " << sentences << endl;
    cout << "Syllable: " << syllables << endl;
    
    cout << calculateGrade(words, syllables, sentences) << endl;
    
    cout << "Done" << endl;
}

string getFilename() {
    string filename;
    
    while (true) {
        cout << "Enter filename: ";
        filename = getLine();
        if (fileExists(filename)) {
            break;
        }
        cout << "File does not exist";
    }
    
    return filename;
}

bool isWord(string token) {
    return isalpha(head(token));
}

bool isSentenceMarker(string token) {
    char first = head(token);
    return first == '.' || first == '!' || first == '?';
}

void testSyllableCount(string word, int expectation) {
    int result = countSyllables(word);
    
    cout << "'" << word << "'" << " has " << result << " syllables, expected " << expectation << ": " << (result == expectation ? "PASS" : "FAIL") << endl;
}

int countSyllables(string word) {
    int result = countSyllablesImpl(word, "");
    return result > 0 ? result : 1;
}

int countSyllablesImpl(string word, string currentVowelBlock) {
    if (word.empty()) {
        return toUpperCase(currentVowelBlock) == "E" ? -1 : 0;
    }
    
    char current = head(word);
    bool currentIsVowel = isVowel(current);
    bool newVowelBlock = currentIsVowel && currentVowelBlock.empty();
    
    if (currentIsVowel) {
        currentVowelBlock += current;
    } else {
        currentVowelBlock = "";
    }
    
    return (newVowelBlock ? 1 : 0) + countSyllablesImpl(tail(word), currentVowelBlock);
}

bool isVowel(char c) {
    c = toupper(c);
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

char head(string str) {
    return str[0];
}

string tail(string str){
    return str.substr(1);
}

double calculateGrade(int words, int syllables, int sentences) {
    return c0 + (c1 * (words / sentences)) + (c2 * (syllables / words));
}
