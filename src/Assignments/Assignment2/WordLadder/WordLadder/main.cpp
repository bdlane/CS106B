//
//  main.cpp
//  WordLadder
//
//

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "lexicon.h"
#include "queue.h"
#include "set.h"

using namespace std;

Lexicon lexicon("EnglishWords.txt");
Set<string> usedWords;

typedef Vector<string> Ladder;

Ladder getLadder(string startWord, string destinationWord);
Vector<string> getNextWords(string word);
string ladderToString(Ladder ladder);

int main() {
    while (true) {
        cout << "Enter start word (RETURN to quit): ";
        string startWord = getLine();
        
        if (startWord.length() == 0) {
            break;
        }
        
        cout << "Enter destination word: ";
        string destinationWord = getLine();
        
        Ladder result = getLadder(startWord, destinationWord);
        
        if (result.isEmpty()) {
            cout << "No ladder found" << endl;
        } else {
            cout << "Found ladder: " << ladderToString(result) << endl;
        }
        
        usedWords.clear();
    }
    
    return 0;
}

Vector<string> getLadder(string startWord, string destinationWord) {
    // Prime the queue
    Queue<Ladder> ladders;
    Ladder initial;
    initial.add(startWord);
    ladders.enqueue(initial);
    
    // Begin the search
    while (!ladders.isEmpty()) {
        Ladder current = ladders.dequeue();
        string endWord = current[current.size()- 1];
        if (endWord == destinationWord) {
            return current;
        }
                    
        foreach(string word in getNextWords(endWord)) {
            Ladder next = current;
            next.add(word);
            ladders.enqueue(next);
        }
    }
    
    return Ladder();
}

Vector<string> getNextWords(string word) {
    Vector<string> words;
    word = toLowerCase(word);
    
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j < 26; j++) {
            string newWord = word;
            char c = 97 + j;
            if (c == newWord[i]) {
                continue;
            }
            newWord[i] = c;
            if (lexicon.contains(newWord) && !usedWords.contains(newWord)){
                words.add(newWord);
                usedWords.add(newWord);
            }
        }
    }
    
    return words;
}

string ladderToString(Ladder ladder) {
    string result;
    foreach(string word in ladder) {
        result += word += " ";
    }
    return result;
}
