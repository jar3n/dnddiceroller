#include "character.h"

int Character::getStrength(){
    return base_stats[0];
}

int Character::getDexterity(){
    return base_stats[1];
}

int Character::getConstitution(){
    return base_stats[2];
}

int Character::getIntelligence(){
    return base_stats[3];
}

int Character::getWisdom(){
    return base_stats[4];
}

int Character::getCharisma(){
    return base_stats[5];
}

void Character::setStrength(int strength){
    base_stats[0] = strength;
}

void Character::setDexterity(int dexterity){
    base_stats[1] = dexterity;
}

void Character::setConstitution(int constitution){
    base_stats[2] = constitution;
}

void Character::setIntelligence(int intelligence){
    base_stats[3] = intelligence;
}

void Character::setWisdom(int wisdom){
    base_stats[4] = wisdom;
}

void Character::setCharisma(int charisma){
    base_stats[5] = charisma;
}

int Character::getModifier(int base_stat){
    // maps the base stat to the appropiate base stat modifier
    return  -5 + ((10 + 5)/(30 - 1)) * (base_stat - 1);
}