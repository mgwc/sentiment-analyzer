#include "Sentence.h"
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <string.h>

using namespace std;

// Please do not change the signatures of these functions!
vector<Sentence*>* readFile(char*);
map<string, double>* wordScores(vector<Sentence*>&);
double calculateSentenceScore(map<string, double>&, string);

int main(int argc, char* argv[]) {
    
    char* filename = argv[1];
    vector<Sentence*>* sentences = readFile(filename);
    if (sentences == NULL) {
        cout << "sentences is null" << endl;
    }
    map<string, double>* wordMap = wordScores(*sentences);
    
    // Prompt user for sentence and return sentiment analysis score for sentence
    while(1) {
    cout << "Please enter a sentence for sentiment analysis." << endl;
    string line;
    getline(cin, line); // reads entire line from cin into line
    
    // Quit if the user entered "quit", but free memory first
    if (line.compare("quit") == 0) {
        
        vector<Sentence*>::iterator sentenceIt = (*sentences).begin();
        while (sentenceIt != (*sentences).end()) {
            delete (*sentenceIt);
            sentenceIt++;
        }
        delete sentences;
        delete wordMap;
        
        return 0;
    }
    
    double sentenceScore = calculateSentenceScore(*wordMap, line);
    cout << "Score: " << sentenceScore << endl;
    }
    
  return 0;
}
