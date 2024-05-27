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

int Character::strength(){
    return base_stats[0];
}

int Character::dexterity(){
    return base_stats[1];
}

int Character::constitution(){
    return base_stats[2];
}

int Character::intelligence(){
    return base_stats[3];
}

int Character::wisdom(){
    return base_stats[4];
}

int Character::charisma(){
    return base_stats[5];
}

string Character::getAbilityScoresAndModifiers()
{
    string abilityandmodsmsg = name + " has the following ability scores and modifiers:\n";
    abilityandmodsmsg += "\tStrength " + to_string(strength()) + " => Mod: " + to_string(getModifier(strength())) + "\n"; 
    abilityandmodsmsg += "\tDexterity " + to_string(dexterity()) + " => Mod: " + to_string(getModifier(dexterity())) + "\n";
    abilityandmodsmsg += "\tConstitution " + to_string(constitution()) + " => Mod: " + to_string(getModifier(constitution())) + "\n";
    abilityandmodsmsg += "\tIntelligence " + to_string(intelligence()) + " => Mod: " + to_string(getModifier(intelligence())) + "\n";
    abilityandmodsmsg += "\tWisdom " + to_string(wisdom()) + " => Mod: " + to_string(getModifier(wisdom())) + "\n";
    abilityandmodsmsg += "\tCharisma " + to_string(charisma()) + " => Mod: " + to_string(getModifier(charisma())) + "\n";
    return string();
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

string Character::getMoney()
{
    string moneyStatus = name + " has the following amounts of coin:\n";
    moneyStatus += "Copper Pieces: " + to_string(money[0]) + "\n";
    moneyStatus += "Silver Pieces: " + to_string(money[1]) + "\n";
    moneyStatus += "Electrum Pieces: " + to_string(money[2]) + "\n";
    moneyStatus += "Gold Pieces: " + to_string(money[3]) + "\n";
    moneyStatus += "Platinum Pieces: " + to_string(money[4]) + "\n";
    
    return moneyStatus;
}

int Character::getModifier(int base_stat){
    // maps the base stat to the appropiate base stat modifier
    return  -5 + ((10 + 5)/(30 - 1)) * (base_stat - 1);
}



