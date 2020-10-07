//
//  main.cpp
//  HaikuDetection
//
//  Created by Brendan Lane on 06/10/2020.
//

#include <iostream>
#include "console.h"
#include "strlib.h"
#include "simpio.h"
#include "vector.h"
#include "tokenscanner.h"

using namespace std;

const int lineCount = 3;
//typedef Vector<string> HaikuLine;
//typedef Vector<Vector<string>> Haiku;

Vector<Vector<string>> getVerse();
bool isHaiku(Vector<Vector<string>> lines);
Vector<string> tokenizeLine(string line);
int lineSyllableCount(Vector<string> line);

int syllablesIn(string word);

int countSyllablesImpl(string word, string currentVowelBlock);
bool isVowel(char c);

char head(string str);
string tail(string str);

int main() {
    Vector<Vector<string>> verse = getVerse();
    
    bool result = isHaiku(verse);
    
    cout << "This is " << (result ? "" : "not ") << "a haiku" << endl;
    
    return 0;
}

Vector<Vector<string>> getVerse() {
    Vector<Vector<string>> result;
    
    for (int i = 0; i < lineCount; i++) {
        cout << "Enter line " << i + 1 << ": ";
        result.add(tokenizeLine(getLine()));
    }
    
    return result;
}

Vector<string> tokenizeLine(string line) {
    Vector<string> tokens;
    TokenScanner scanner(line);
    
    scanner.ignoreWhitespace();
    scanner.addWordCharacters("'");
    
    while (scanner.hasMoreTokens()) {
        tokens.add(scanner.nextToken());
    }
    
    return tokens;
}

bool isHaiku(Vector<Vector<string>> verse) {
    // Assume we only have 3 lines
    
    Vector<int> expectedSyllables;
    
    expectedSyllables.add(5);
    expectedSyllables.add(7);
    expectedSyllables.add(5);
    
    for (int i = 0; i < expectedSyllables.size(); i++) {
        int actual = lineSyllableCount(verse[i]);
        int expected = expectedSyllables[i];
        if (actual != expected) {
            return false;
        }
    }
    
    return true;
}

int lineSyllableCount(Vector<string> line) {
    int result = 0;
    for(int i = 0; i < line.size(); i++) {
        result += syllablesIn(line[i]);
    }
    return result;
}

int syllablesIn(string word) {
    TokenScanner scanner;
    if (scanner.getTokenType(word) != WORD) {
        return 0;
    }
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
