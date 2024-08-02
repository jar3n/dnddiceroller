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
        bool _createdLedgerInConstructor = false;
        
        void writeToLedger();
        void convertLedgerCharactertoCharacter(dnd::character &ledger_character, 
                                               Character &character);

    public:
        ledger();
        ~ledger();

        void addCharacter(Character c);
        void getCharacter(string name, Character& character);
        void getCharacter(size_t index, Character& character);
        size_t size();

};

#endif
