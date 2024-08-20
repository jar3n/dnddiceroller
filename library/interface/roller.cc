#include "roller.h"
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

Roller::Roller()
{
}

Roller::~Roller(){}

string Roller::rollCheck(int modifier, bool advantage, bool disadvantage){
    if(advantage && disadvantage){
        throw optionsException("You cannot have both advantage and disadvantage on a roll.");
    }

    Dice d;
    int maxBaseRoll = 20;
    int roll;
    dice_res doubleRoll;

    string advDisResStrMod = " ";
    string rollStr = "";
    if (advantage || disadvantage){
        if (advantage){
            advDisResStrMod = " with advantage";
            doubleRoll = d.doubleRoll(maxBaseRoll);
            roll = doubleRoll.max_roll;
            rollStr = " ( " + to_string(doubleRoll.min_roll) + " , " + to_string(doubleRoll.max_roll) + " ) => " + to_string(roll);
        } else {
            advDisResStrMod = " with disadvantage";
            doubleRoll = d.doubleRoll(maxBaseRoll);
            roll = doubleRoll.min_roll;
            rollStr = " ( " + to_string(doubleRoll.min_roll) + " , " + to_string(doubleRoll.max_roll) + " ) => " + to_string(roll);
        }
    } else {
        roll = d.rolldX(maxBaseRoll);
        rollStr = to_string(roll);
    }
    
    int total = roll + modifier;

    string modStr = "";
    if (modifier >= 0){
        modStr = " + " + to_string(abs(modifier));
    } else {
        modStr = " - " + to_string(abs(modifier));
    }

    string totalStr = advDisResStrMod + ": " + rollStr + modStr + " => " + to_string(total);
    return totalStr;
}

void Roller::rollAbilityCheck(ability_score ab, string name, bool advantage, bool disadvantage)
{
    Character c;
    LedgerAccessor::getCharacter(name, c);

    string rollStr = rollCheck(c.getAbilityMod(ab), advantage, disadvantage);

    stringstream result;
    result << c.getName() << "'s " << getAbilityScoreName(ab) << " check" << rollStr;

    cout << result.str() << endl;
}

void Roller::rollSkillCheck(skill skill, string name, bool advantage, bool disadvantage)
{
    Character c;
    LedgerAccessor::getCharacter(name, c);
    string rollStr = rollCheck(c.getSkillMod(skill), advantage, disadvantage);
    stringstream result;
    result << c.getName() << "'s " << getSkillName(skill) << " check" << rollStr;
    cout << result.str() << endl;
}

void Roller::rollInitiative(string name, bool advantage, bool disadvantage)
{
    Character c;
    LedgerAccessor::getCharacter(name, c);
    string rollStr = rollCheck(c.getAbilityMod(DEXTERITY), advantage, disadvantage);
    stringstream result;
    result << c.getName() << "'s initiative" << rollStr;
    cout << result.str() << endl;
}

void Roller::roll(uint32_t cap, bool disadvantage, bool advantage, uint32_t numRolls, int modifier){
    if (disadvantage && advantage){
        throw optionsException("You can't have both advantage and disadvantage at the same time.");
    } 

    if ((advantage || disadvantage) && numRolls > 1){
        throw optionsException("You can't have advantage or disadvantage with multiple rolls.");
    }
    
    int finalRoll = modifier;
    stringstream rolls, result;
    Dice d;
    string modSignStr = modifier >= 0 ? "+" : "-";
    result << "Rolled " << numRolls << "d" << cap << modSignStr << abs(modifier);
    if (advantage){
        result << " with advantage: ";
        dice_res roll = d.doubleRoll(cap);
        rolls << roll.min_roll << " < " << roll.max_roll << " => " << roll.max_roll;
        finalRoll += roll.max_roll;
        result << rolls.str();
    } else if (disadvantage){
        result << " with disadvantage: ";
        dice_res roll = d.doubleRoll(cap);
        rolls << roll.min_roll << " < " << roll.max_roll << " => " << roll.min_roll;
        finalRoll += roll.min_roll;
        result << rolls.str();
    } else {
        result << ": ";
        vector<int> rolls = d.multiRoll(cap, numRolls);
        for (int i = 0; i < numRolls; i++){
            result << rolls[i];
            if (i < numRolls -1) result << " + ";
            finalRoll += rolls[i];
        }
    }

    stringstream modStr;
    modStr << "";
    if (modifier < 0){
        modStr << " - " << abs(modifier);
    } else if (modifier > 0) {
        modStr << " + " << modifier;
    } 
    result << modStr.str();
    result << " => " << finalRoll;

    cout << result.str() << endl;
}