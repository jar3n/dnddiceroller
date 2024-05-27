#include "character.h"
#include "dice.h"

using namespace dnd;


Character::Character(int level, int base_stats[6]) :
    death_saves_fails(0),
    death_saves_success(0),
    level(level)
{
    for (int i = 0; i < 6; i++){
        this->base_stats[i] = base_stats[i];
    }

    // TEMP based on class
    // also based on game rules
    // could either be random dice rolls or taking max value 

    
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

int Character::getDexterityMod(){
    return getModifier(base_stats[1]);
}

int Character::getConstitutionMod(){
    return getModifier(base_stats[2]);
}

int Character::getIntelligenceMod(){
    return getModifier(base_stats[3]);
}

int Character::getWisdomMod(){
    return getModifier(base_stats[4]);
}

int Character::getCharismaMod(){
    return getModifier(base_stats[5]);
}

string Character::getHitPoints()
{
    string health_status = "Current Health Status:\n";
    health_status += "\tHit Points: " + to_string(hit_points) + "\n";
    health_status += "\tTemperary Hit Points: " + to_string(temp_hit_points) + "\n";
    
    return health_status;
}

string Character::takeDamage(int damage)
{
    if (temp_hit_points > 0){
        if(temp_hit_points > damage){
            temp_hit_points -= damage;
        } else {
            hit_points -= (damage - temp_hit_points);
            temp_hit_points = 0;
        }

    } else {
        if (hit_points > damage){
            hit_points -= damage;
        } else{
            hit_points = 0;
        }
    }
    return getHitPoints();
}

string Character::heal(int health){
    if ((hit_points + health) > max_hit_points){
        hit_points = max_hit_points;
    } else{
        hit_points += health;
    }
    return getHitPoints();
}

string Character::getDeathSaves()
{
    if (hit_points > 0){
        return name + " is not unconscious.";
    }

    string death_save_status = "Death Save Status: ";

    death_save_status += "Saves: " + to_string(death_saves_success) + "\n"; 
    death_save_status += "Fails: " + to_string(death_saves_fails) +  "\n";

    return death_save_status;
}

string Character::rollDeathSave()
{
    Dice * deathSaveDice = new Dice();

    int roll = deathSaveDice->rolld20();
    if(roll >= 10){
        death_saves_success++;
    } else {
        death_saves_fails++;
    }
    return getDeathSaves();
}

int Character::getModifier(int base_stat){
    // maps the base stat to the appropiate base stat modifier
    return  -5 + ((10 + 5)/(30 - 1)) * (base_stat - 1);
}



