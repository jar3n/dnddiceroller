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
    result << c.getName() << "'s " << c.getAbilityScoreName(ab) << " check" << rollStr;

    cout << result.str() << endl;
}

void Roller::rollSkillCheck(skill skill, string name, bool advantage, bool disadvantage)
{
    Character c;
    LedgerAccessor::getCharacter(name, c);
    string rollStr = rollCheck(c.getSkillMod(skill), advantage, disadvantage);
    stringstream result;
    result << c.getName() << "'s " << c.getSkillName(skill) << " check" << rollStr;
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

void Roller::rollStrength(string name, bool advantage, bool disadvantage)
{
    rollAbilityCheck(STRENGTH, name, advantage, disadvantage);
}

void Roller::rollDexterity(string name, bool advantage, bool disadvantage)
{
    rollAbilityCheck(DEXTERITY, name, advantage, disadvantage);
}

void Roller::rollIntelligence(string name, bool advantage, bool disadvantage)
{
    rollAbilityCheck(INTELLIGENCE, name, advantage, disadvantage);
}

void Roller::rollWisdom(string name, bool advantage, bool disadvantage)
{
    rollAbilityCheck(WISDOM, name, advantage, disadvantage);
}

void Roller::rollCharisma(string name, bool advantage, bool disadvantage)
{
    rollAbilityCheck(CHARISMA, name, advantage, disadvantage);
}

void Roller::rollConstitution(string name, bool advantage, bool disadvantage)
{
    rollAbilityCheck(CONSTITUTION, name, advantage, disadvantage);
}

void Roller::rollAcrobatics(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(ACROBATICS, name, advantage, disadvantage);
}

void Roller::rollAnimalHandling(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(ANIMAL_HANDLING, name, advantage, disadvantage);
}

void Roller::rollArcana(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(ARCANA, name, advantage, disadvantage);
}

void Roller::rollAthletics(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(ATHLETICS, name, advantage, disadvantage);
}

void Roller::rollDeception(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(DECEPTION, name, advantage, disadvantage);
}

void Roller::rollHistory(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(HISTORY, name, advantage, disadvantage);
}

void Roller::rollInsight(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(INSIGHT, name, advantage, disadvantage);
}

void Roller::rollIntimidation(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(INTIMIDATION, name, advantage, disadvantage);
}

void Roller::rollInvestigation(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(INVESTIGATION, name, advantage, disadvantage);
}

void Roller::rollMedicine(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(MEDICINE, name, advantage, disadvantage);
}

void Roller::rollNature(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(NATURE, name, advantage, disadvantage);
}

void Roller::rollPerception(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(PERCEPTION, name, advantage, disadvantage);
}

void Roller::rollPerformance(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(PERFORMANCE, name, advantage, disadvantage);
}

void Roller::rollPersuasion(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(PERSUASION, name, advantage, disadvantage);
}

void Roller::rollReligion(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(RELIGION, name, advantage, disadvantage);
}

void Roller::rollSleightOfHand(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(SLEIGHT_OF_HAND, name, advantage, disadvantage);
}

void Roller::rollStealth(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(STEALTH, name, advantage, disadvantage);
}

void Roller::rollSurvival(string name, bool advantage, bool disadvantage)
{
    rollSkillCheck(SURVIVAL, name, advantage, disadvantage);
}
