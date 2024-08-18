#ifndef _ROLLER_H_
#define _ROLLER_H_

#include "accessor.h"
#include "dice.h"

using namespace std;

class optionsException : public exception{
    public:
        optionsException(string msg) :
        _msg(msg){}

        string what(){
            return "options error: " + _msg;
        }

    private:
        string _msg;

};


class Roller : public LedgerAccessor {
    private:

        string rollCheck(int modifier, bool advantage, bool disadvantage);
        void rollAbilityCheck(ability_score ab, string name, bool advantage, bool disadvantage);
        void rollSkillCheck(skill skill, string name, bool advantage, bool disadvantage);
    public:
        Roller();
        ~Roller();

        // raw roll taken from main
        void roll(uint32_t cap, bool disadvantage = false, bool advantage = false, uint32_t numRolls = 1, int modifier = 0);

        void rollStrength(string, bool, bool);
        void rollDexterity(string, bool, bool);
        void rollIntelligence(string, bool, bool);
        void rollWisdom(string, bool, bool);
        void rollCharisma(string, bool, bool);
        void rollConstitution(string, bool, bool);

        void rollAcrobatics(string, bool, bool);
        void rollAnimalHandling(string, bool, bool);
        void rollArcana(string, bool, bool);
        void rollAthletics(string, bool, bool);
        void rollDeception(string, bool, bool);
        void rollHistory(string, bool, bool);
        void rollInsight(string, bool, bool);
        void rollIntimidation(string, bool, bool);
        void rollInvestigation(string, bool, bool);
        void rollMedicine(string, bool, bool);
        void rollNature(string, bool, bool);
        void rollPerception(string, bool, bool);
        void rollPerformance(string, bool, bool);
        void rollPersuasion(string, bool, bool);
        void rollReligion(string, bool, bool);
        void rollSleightOfHand(string, bool, bool);
        void rollStealth(string, bool, bool);
        void rollSurvival(string, bool, bool);
        
};

#endif
