#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <boost/algorithm/string.hpp>
#include <vector>
#include "character.h"
#include "../serial/ledger.h"

#define PROMPT_RETRIES 5

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
        vector<Character> _createdCharacters;

        void promptGetLine(string prompt, string error_msg, string &response);
        void promptGetYesNo(string prompt,  bool &response);
        void promptNumber(string prompt, 
                      int32_t &response,
                      pair<int32_t,int32_t> range = pair<int32_t,int32_t>(INT32_MIN, INT32_MAX)); 
        void promptStringNoSpaces(string prompt, string error_msg, string &response);


        // creating character helper functions
        void setCharacterFluffHelper(Character *c);
        void setAbilityScoreHelper(Character *c);
        void setProficiencyHelper(Character *c);
        bool createCharacterHelper();
        
        void addCharactersToLedger();

    public:
        CharacterCreator();
        ~CharacterCreator();

        void createCharacter();


};

#endif
