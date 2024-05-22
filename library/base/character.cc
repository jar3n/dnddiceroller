#include "character.h"


Character::Character(int level, int base_stats[6]) :
    death_saves_fails {false, false, false},
    death_saves_success {false, false, false},
    level(level)
{
    for (int i = 0; i < 6; i++){
        this->base_stats[i] = base_stats[i];
    }

    
}

// getting base stats

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

// getting base stat modifiers

int Character::getStrengthMod(){
    return getModifier(base_stats[0]);
}

int Character::getDexterity(){
    return getModifier(base_stats[1]);
}

int Character::getConstitution(){
    return getModifier(base_stats[2]);
}

int Character::getIntelligence(){
    return getModifier(base_stats[3]);
}

int Character::getWisdom(){
    return getModifier(base_stats[4]);
}

int Character::getCharisma(){
    return getModifier(base_stats[5]);
}


int Character::getModifier(int base_stat){
    // maps the base stat to the appropiate base stat modifier
    return  -5 + ((10 + 5)/(30 - 1)) * (base_stat - 1);
}

