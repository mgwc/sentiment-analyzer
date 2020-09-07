#include "Sentence.h"
#include "Word.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>

#include <boost/algorithm/string.hpp>
using namespace boost;
using namespace std;

/*
 * This function should read the specified file and return a vector
 * containing pointers to a Sentence object for each well-formatted line.
 */
vector<Sentence*>* readFile(char* filename) {

    vector<Sentence*>* sentences = new vector<Sentence*>();
    
    if (filename == NULL) {
        cout << "No filename was specified; returning NULL sentences vector" << endl;
        return NULL;
    }
    
    // Attempt to open the file for reading
    ifstream file;
    file.open(filename);    
    if (!file.is_open()) {
        cout << "Could not open " << filename << " for reading; returning NULL sentences vector" << endl;
        return NULL;
    }
    
    // Read every line of input file
    string line;
    while (getline(file, line)) {
        
        // Check if line is well formatted
        string::iterator strIt = line.begin();
        string number;
        while (strIt != line.end() && *strIt != ' ') {
            number = number + *strIt;
            strIt++;
        }
        
        bool spaceAndChar = false;
        bool validNumber = true;
        if (*strIt == ' ' && (*(strIt + 1)) != '\0' && (*(strIt + 1)) != '\n') {
            spaceAndChar = true;
            string::iterator numIt = number.begin();
            if (*numIt == '-') {
                if (number.size() == 1) {
                    validNumber = false;
                    break;
                } else {
                    numIt++;
                }
            }
            for (numIt; numIt != number.end(); numIt++) {
                if (!isdigit(*numIt)) {
                    validNumber = false;
                    break;
                }
            }
        }
         
        // If line is well formatted, add the sentence to the vector
        if (spaceAndChar && validNumber) {
            // Create a Sentence object from line; score = int at beginning, text = string following the whitespace after the int
            int number_size = number.size();
            Sentence* s = new Sentence(stoi(number), line.substr(number_size + 1));
            
            // Add the sentence to the vector 
            sentences->push_back(s);
        }
    }
    
    file.close();
    return sentences;
}

/*
 * This function takes the vector of Sentence pointers and calculates the
 * average score for each word. The return value maps the word to its score.
 */
map<string, double>* wordScores(vector<Sentence*>& sentences) {

 // Create the output map
 map<string, double>* wordScores = new map<string, double>();
 // Create the intermediate map<Word>
 map<string, Word> wordObjMap;

 // For each sentence in sentences, break the Sentence up into its component words
 std::vector<Sentence*>::iterator sentenceIt = sentences.begin();
 while (sentenceIt != sentences.end()) {
     
     int currSentenceScore = (*sentenceIt)->getScore();
     string currSentenceText = (*sentenceIt)->getText();
     to_lower(currSentenceText);
     
     if (isalpha(currSentenceText[0])) {      // Check that the current sentence starts with a letter
     
         std::vector<std::string> words;
         split(words, currSentenceText, is_any_of(" \r\n.,\"\\;:{}[]+_-()*&^%$#@!~`/"), token_compress_on);

         // For each word, if the word isn't the empty string, 
         // create a Word object or update the existing Word object for that word
         vector<string>::iterator wordIt = words.begin();
         while (wordIt != words.end()) {
             string word = *wordIt;
             if (word.size() != 0) {
                 auto wordObjMapIt = wordObjMap.find(word);
                 if (wordObjMapIt == wordObjMap.end()) {
                     Word temp(currSentenceScore);
                     wordObjMap.insert(pair<string, Word>(word, temp));
                 } else {
                     wordObjMapIt->second.tally();
                     wordObjMapIt->second.addScore(currSentenceScore);
                 }
             }
             wordIt++;
         }
     }
    
     sentenceIt++;
 }
    
  // For each Word in the wordObjMap, get average score and add <word, score> to output map
 map<string, Word>::iterator wordObjMapIt = wordObjMap.begin();
 while (wordObjMapIt != wordObjMap.end()) {

     string word = wordObjMapIt->first;
     double score = wordObjMapIt->second.getAvgScore();
     wordScores->insert(pair<string, double>(word, score));
     
     wordObjMapIt++;
 }
    
  return wordScores;

}

/*
 * This function takes the map of words to scores and a string representing
 * a new sentence. The return value is the average of the scores of the
 * words in the sentence.
 */
double calculateSentenceScore(map<string, double>& scores, string sentence) {
  
  // Split sentence into lowercase words and store in a vector<string>
  string currSentenceText(sentence);
  to_lower(currSentenceText);
  std::vector<std::string> words;
  split(words, currSentenceText, is_any_of(" \r\n.,\"\\;:{}[]+_-()*&^%$#@!~`/"), token_compress_on);
  int numWords = words.size();
  
  double sum = 0.0;
  // For each word in vector<string>, find the word in scores, and add its value to sum (or add 0 if not present)
  vector<string>::iterator wordIt = words.begin();
  while (wordIt != words.end()) {
      if (!((*wordIt).size() == 0)) {
          if (scores.find(*wordIt) == scores.end()) {
              cout << "did not find " << *wordIt << "in scores" << endl;
          } else {
              sum += scores[*wordIt];
              cout << "found " << *wordIt << " in scores; added " << scores[*wordIt] << " to sum to get " << sum << endl;
          }
      } else {
          numWords--;
      }
      wordIt++;
  }
  
  cout << "sum = " << sum << ", numWords = " << numWords << endl;
  double sentenceScore = (sum / (double) numWords);  

  return sentenceScore;

}

