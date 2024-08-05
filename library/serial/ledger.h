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
    // part of the refactor
    // now the "ledger" is really a directory that contains 
    // a file for each character created
    // each file when read in will be updated if the command 
    // calls for it. 
    // for updating, the file will get deleted and a replaced with 
    // a new file that has the same character object but with 
    // new information 
    private:
        string _full_ledger_path;
        
        // void writeToLedger();
        void convertLedgerCharactertoCharacter(dnd::character &ledger_character, 
                                               Character &character);

        string createCharacterFile(string name);
        string getCharacterFile(string name);

    public:
        ledger();
        ~ledger();

        void addCharacter(Character c);
        void deleteCharacter(string name);
        void getCharacter(string name, Character& character);
        vector<Character> getAllCharacters();
        size_t size();

};

#endif
