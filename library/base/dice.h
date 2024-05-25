#ifndef _DICE_H_
#define _DICE_H_

#include <random>

using namespace std;

namespace dnd {

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

}



#endif