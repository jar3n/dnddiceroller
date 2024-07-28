#ifndef LEDGER_H
#define LEDGER_H

#include <string>
#include <fstream>
#include "characterbook.pb.h"
#include <exception>
#include <climits>
#include "character.h"

using namespace std;

class ledger_exception : public exception {
    private:
        string _msg;

    public:
        ledger_exception(string msg);
        string what();
};


class ledger {
    // class for accessing the character ledger.
    private:
        string _full_ledger_path;
        dnd::character_ledger _ledger_data;
        bool _haveUpdateToLedger = false;
        bool _createdCharacterInConstructor = false;

        void getCharacter(string name, dnd::character& character);
        void writeToLedger();

    public:
        ledger();
        ~ledger();
    
        void getCharacterAbilityScores(string name);
        void getCharacterPersonality(string name);
        void getCharacterBackstory(string name);
        void getCharacterPhysicalTraits(string name);
        void getAlignment(string name);
        void listCharacters();

        void addCharacter(Character c);

};

#endif
