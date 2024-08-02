#ifndef _ACCESSOR_H_
#define _ACCESSOR_H_

#include "../serial/ledger.h"
#include "character.h"

class LedgerAccessor {
    private:
        ledger * _characterLedger;

        void getCharacter(string name, Character &c);

    public:
        void getCharacterAbilityScores(string name);
        void getCharacterPersonality(string name);
        void getCharacterBackstory(string name);
        void getCharacterPhysicalTraits(string name);
        void getAlignment(string name);
        void listCharacters();

        LedgerAccessor();
        ~LedgerAccessor();

};


#endif
