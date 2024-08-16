#include "roller.h"
#include <sstream>
#include <cmath>

using namespace std;

Roller::Roller()
{
}

Roller::~Roller(){}

void Roller::rollAbilityCheck(ability_score ab, string name, bool advantage, bool disadvantage){
    if(advantage && disadvantage){
        cout << "You cannot have both advantage and disadvantage on a roll." << endl;
        return;
    }

    Character c;
    Dice d;
    LedgerAccessor::getCharacter(name, c);
    int maxBaseRoll = 20;
    int roll;
    dice_res doubleRoll;

    string advDisResStrMod = "";
    string rollStr = "";
    if (advantage || disadvantage){
        if (advantage){
            advDisResStrMod = "with advantage";
            doubleRoll = d.doubleRoll(maxBaseRoll);
            roll = doubleRoll.max_roll;
            rollStr = " ( " + to_string(doubleRoll.min_roll) + " , " + to_string(doubleRoll.max_roll) + " ) => " + to_string(roll);
        } else {
            advDisResStrMod = "with disadvantage";
            doubleRoll = d.doubleRoll(maxBaseRoll);
            roll = doubleRoll.min_roll;
            rollStr = " ( " + to_string(doubleRoll.min_roll) + " , " + to_string(doubleRoll.max_roll) + " ) => " + to_string(roll);
        }
    } else {
        roll = d.rolldX(maxBaseRoll);
        rollStr = to_string(roll);
    }
    
    int modifier = c.getAbilityMod(ab);
    int total = roll + modifier;

    string modStr = "";
    if (modifier >= 0){
        modStr = " + " + to_string(abs(modifier));
    } else {
        modStr = " - " + to_string(abs(modifier));
    }

    stringstream result;
    result << c.getName() << "'s " << c.getAbilityScoreName(ab) << " check " << advDisResStrMod << ": ";
    result << rollStr << modStr << " => " << total;
    
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
