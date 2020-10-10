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

Vector<string> getLadder(string startWord, string destinationWord);
Vector<string> getNextWords(string word);
string ladderToString(Vector<string> ladder);

int main() {
    while (true) {
        cout << "Enter start word (RETURN to quit): ";
        string startWord = getLine();
        
        if (startWord.length() == 0) {
            break;
        }
        
        cout << "Enter destination word: ";
        string destinationWord = getLine();
        
        Vector<string> ladder = getLadder(startWord, destinationWord);
        
        if (ladder.isEmpty()) {
            cout << "No ladder found" << endl;
        } else {
            cout << "Found ladder: " << ladderToString(ladder) << endl;
        }
    }
    
    return 0;
}

Vector<string> getLadder(string startWord, string destinationWord) {
    // Prime the queue
    Queue<Vector<string>> ladders;
    Vector<string> ladder;
    ladder.add(startWord);
    
    ladders.enqueue(ladder);
    
    // Begin the search
    while (!ladders.isEmpty()) {
        Vector<string> ladder = ladders.dequeue();
        string endWord = ladder[ladder.size()- 1];
        if (endWord == destinationWord) {
            return ladder;
        }
                    
        foreach(string word in getNextWords(endWord)) {
            Vector<string> l = ladder;
            l.add(word);
            ladders.enqueue(l);
        }
    }
    
    return Vector<string>();
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
            newWord.replace(i, 1, string(1, c));
            if (lexicon.contains(newWord) && !usedWords.contains(newWord)){
                words.add(newWord);
                usedWords.add(newWord);
            }
        }
    }
    
    return words;
}

string ladderToString(Vector<string> ladder) {
    string result;
    foreach(string word in ladder) {
        result += word += " ";
    }
    return result;
}
