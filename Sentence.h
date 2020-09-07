#include <string>
#include <vector>

using namespace std;

class Sentence {

    private:
    int score;
    
    private:
    string text;
    
    public:
    Sentence(int score, string text) {
        this->score = score;
        this->text = text;
    }
    
    int getScore() {
        return this->score;
    }
    
    string getText() {
        return this->text;
    }

};