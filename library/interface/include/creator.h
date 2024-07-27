#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <vector>
#include "character.h"
#include "ledger.h"

class create_character_exception : public exception {
    private:
        string _msg;
    
    public:
        create_character_exception(string msg);
        string what();
};

class CharacterCreator {
    private:
        // list of characters to be loaded onto the ledger
        vector<Character> createdCharacters;

        // load characters into ledger
        void loadLedger();

        void promptGetLine(string prompt, string error_msg, string &response);
        void promptNumber(string prompt, 
                      int32_t &response,
                      pair<int32_t,int32_t> range = pair<int32_t,int32_t>(INT32_MIN, INT32_MAX)); 
        void promptStringNoSpaces(string prompt, string error_msg, string &response);


        // creating character helper functions
        void setCharacterFluffHelper(dnd::character *c);
        void setAbilityScoreHelper(dnd::character *c);
        bool createCharacterHelper();
        void createCharacter();
        


    public:
        CharacterCreator();
        ~CharacterCreator();

        void createCharacter();


};

#endif
