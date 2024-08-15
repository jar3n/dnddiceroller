#ifndef _ROLLER_H_
#define _ROLLER_H_

#include "accessor.h"
#include "dice.h"

using namespace std;

class Roller : public LedgerAccessor {
    private:
        // might put something here later
        void rollAbilityCheck(ability_score ab, string name);

    public:
        Roller();
        ~Roller();

        void rollStrength(string name);
        void rollDexterity(string name);
        void rollIntelligence(string name);
        void rollWisdom(string name);
        void rollCharisma(string name);
        void rollConstitution(string name);
    
};

#endif