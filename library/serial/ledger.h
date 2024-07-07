#ifndef LEDGER_H
#define LEDGER_H

#include <string>
#include <fstream>
#include "build/characterbook.pb.h"
#include <exception>

using namespace std;

class ledger_exception : public exception {
    private:
        string _msg;

    public:
        ledger_exception(string msg);
        const char * what();
};

class ledger {
    // class for accessing the character ledger.
    private:
    string _full_ledger_path;
    dnd::character_ledger _ledger_data;
    fstream _ledger_in_stream;

    void accessLedger();
    void createCharacterHelper();
    void writeToLedger();

    public:
    ledger(string ledger_path = "./build/character_ledger");
    void createCharacter();
    void getCharacterInfo(string name);
    void listCharacters();
};

#endif