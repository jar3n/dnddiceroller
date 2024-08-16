#ifndef _ROLLER_H_
#define _ROLLER_H_

#include "accessor.h"
#include "dice.h"

using namespace std;

class Roller : public LedgerAccessor {
    private:
        void rollAbilityCheck(ability_score ab, string name, bool advantage, bool disadvantage);

    public:
        Roller();
        ~Roller();

        void rollStrength(string, bool, bool);
        void rollDexterity(string, bool, bool);
        void rollIntelligence(string, bool, bool);
        void rollWisdom(string, bool, bool);
        void rollCharisma(string, bool, bool);
        void rollConstitution(string, bool, bool);
    
};

#endif
