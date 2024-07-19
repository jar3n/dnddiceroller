#ifndef _DICE_H_
#define _DICE_H_

#include <random>

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
        int rolld4();
        int rolld6();
        int rolld8();
        int rolld10();
        int rolld12();
        int rolld20();
        int rolld100();
        int rolldX(int cap);
        dice_res doubleRoll(int cap);



    private:
        random_device rd;
        mt19937 gen;
        uniform_int_distribution<> dis4;
        uniform_int_distribution<> dis6;
        uniform_int_distribution<> dis8;
        uniform_int_distribution<> dis10;
        uniform_int_distribution<> dis12;
        uniform_int_distribution<> dis20;
        uniform_int_distribution<> dis100;

};




#endif