#include <string>
#include <vector>

using namespace std;

class Word {
   
    private:
    int sum;
    
    private:
    int count;
    
    public:
    Word(int score) {
        this->sum = score;
        this->count = 1;
    }
    
    void addScore(int score) {
        this->sum += score;
    }
    
    void tally() {
        this->count++;
    }
    
    int getSum() {
        return this->sum;
    }
    
    int getCount() {
        return this->count;
    }
    
    double getAvgScore() {
        return (double) sum / (double) count;
    }

};