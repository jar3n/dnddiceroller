#include "dice.h"

Dice::Dice() : 
    gen(rd()){}

Dice::~Dice(){}

int Dice::rolldX(int cap){
    uniform_int_distribution<> disX(1, cap);
    return disX(gen);
}

dice_res Dice::doubleRoll(int cap){
    dice_res res;
    res.roll_1 = rolldX(cap);
    res.roll_2 = rolldX(cap);
    res.max_roll = max(res.roll_1, res.roll_2);
    res.min_roll = min(res.roll_1, res.roll_2);
    return res;
}
