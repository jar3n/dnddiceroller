#ifndef _DICE_H_
#define _DICE_H_

#include <random>
#include <vector>

using namespace std;
struct dice_res {
    int roll_1;
    int roll_2;
    int max_roll;
    int min_roll;
};
typedef struct dice_res dice_res;

class Dice {
        
    public:
        Dice();
        ~Dice();
        int rolldX(int cap);
        dice_res doubleRoll(int cap);
        vector<int> multiRoll(int cap, uint32_t numRolls);

    private:
        random_device rd;
        mt19937 gen;
};




#endif
