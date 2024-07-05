#include "dice.h"

Dice::Dice() : 
    gen(rd()), 
    dis4(1,4), 
    dis6(1,6),
    dis8(1,8),
    dis10(1,10),
    dis12(1,12),
    dis20(1,20),
    dis100(1,100){}

int Dice::rolldX(int cap){
    uniform_int_distribution<> disX(1, cap);
    return disX(gen);
}

dice_res Dice::doubleRoll(int cap)
{
    dice_res res;
    res.roll_1 = rolldX(cap);
    res.roll_2 = rolldX(cap);
    res.max_roll = max(res.roll_1, res.roll_2);
    res.min_roll = min(res.roll_1, res.roll_2);
    return res;
}

int Dice::rolld4(){
    return dis4(gen);
}

int Dice::rolld6(){
    return dis6(gen);
}

int Dice::rolld8(){
    return dis8(gen);
}

int Dice::rolld10(){
    return dis10(gen);
}

int Dice::rolld12(){
    return dis12(gen);
}

int Dice::rolld20(){
    return dis20(gen);
}

int Dice::rolld100(){
    return dis100(gen);
}

