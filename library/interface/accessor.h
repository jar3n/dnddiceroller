#ifndef _ACCESSOR_H_
#define _ACCESSOR_H_

#include "../serial/ledger.h"
#include "character.h"

class LedgerAccessor {
    private:
        ledger * _characterLedger;

    protected:
        void getCharacter(string name, Character &c);

    public:
        void getCharacterAbilityScores(string name);
        void getCharacterSkills(string name);
        void getCharacterPersonality(string name);
        void getCharacterBackstory(string name);
        void getCharacterPhysicalTraits(string name);
        void getAlignment(string name);
        void listCharacters();
        void deleteCharacter(string name);
        void getInspiration(string name);
        void modifyinspiration(string name, int amount);

        LedgerAccessor();
        ~LedgerAccessor();

};


#endif
