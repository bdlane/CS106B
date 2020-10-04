/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

enum Face {
    Heads,
    Tails
};

Face flipCoin();

const int maxHeads = 3;
int headsSoFar = 0;
int flipsSoFar = 0;

int main() {
    cout << "Flipping coin..." << endl;
        
    while (headsSoFar < maxHeads) {
        Face toss = flipCoin();
        flipsSoFar++;
        cout << ((toss == Heads) ? "heads" : "tails") << endl;
        headsSoFar += toss == Heads ? 1 : -headsSoFar;
    }
    
    cout << "It took " << flipsSoFar << " flips to get " << maxHeads << " consecutive heads" << endl;
    
    return 0;
}

Face flipCoin() {
    return randomChance(0.5) ? Heads : Tails;
}
