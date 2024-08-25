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

    public:
        Roller();
        ~Roller();

        // raw roll taken from main
        void roll(uint32_t cap, bool disadvantage = false, bool advantage = false, uint32_t numRolls = 1, int modifier = 0);
        void rollAbilityCheck(ability_score ab, string name, bool advantage, bool disadvantage);
        void rollSkillCheck(skill skill, string name, bool advantage, bool disadvantage);
        void rollInitiative(string name, bool advantage, bool disadvantage);
        void rollSave(ability_score ab, string name, bool advantage, bool disadvantage);
};

#endif
