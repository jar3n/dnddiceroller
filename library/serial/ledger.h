#ifndef LEDGER_H
#define LEDGER_H

#include <string>
#include <fstream>
#include "characterbook.pb.h"
#include <exception>
#include <climits>

using namespace std;

#define NUM_ABILITY_SCORES 6
#define ABILITY_NAMES ((const char *[]){"Strength", \
                                        "Dexterity", \
                                        "Constitution", \
                                        "Intelligence", \
                                        "Wisdom", \
                                        "Charisma"})

#define PROMPT_RETRIES 5

enum ability_score {
    STRENGTH = 0,
    DEXTERITY = 1,
    CONSTITUTION = 2,
    INTELLIGENCE = 3,
    WISDOM = 4,
    CHARISMA = 5
};

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

    public:
    ledger();
    ~ledger();
   
    void getCharacterAbilityScores(string name);
    void getCharacterPersonality(string name);
    void getCharacterBackstory(string name);
    void getCharacterPhysicalTraits(string name);
    void getAlignment(string name);
    void listCharacters();

};

#endif
