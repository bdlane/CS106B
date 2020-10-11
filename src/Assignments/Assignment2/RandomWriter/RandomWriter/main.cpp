//
//  main.cpp
//  RandomWriter
//
//

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "vector.h"
#include "map.h"
#include "random.h"

using namespace std;

typedef Map<string, Vector<char>> MarkovModel;

MarkovModel generateModel(string filename, int order);
string getMostFrequent(MarkovModel model);
void write(MarkovModel model, int length);

int main() {
    MarkovModel model = generateModel("test.txt", 5);
    write(model, 2000);
    return 0;
}

MarkovModel generateModel(string filename, int order) {
    MarkovModel model;
    ifstream stream(filename);
    string current;
    char c;
    
    // Build the seed
    while (current.size() < order && stream.get(c)) {
        current += c;
    }
    
    // Process the rest of the document
    while (stream.get(c)) {
        model[current].add(c);
        current = current.substr(1) + c;
    }
    
    return model;
}

void write(MarkovModel model, int length) {
    string current = getMostFrequent(model);
    cout << current;
    length -= current.size();
    while (length > 0 && model.containsKey(current)) {
        char next = model[current].get(randomInteger(0, model[current].size() - 1));
        cout << next;
        current = current.substr(1) + next;
        length--;
    }
    cout << endl;
}

string getMostFrequent(MarkovModel model) {
    string soFar;
    int maxOccurences = 0;
    foreach(string key in model) {
        if (model[key].size() > maxOccurences) {
            soFar = key;
            maxOccurences = model[key].size();
        }
    }
    
    return soFar;
}
