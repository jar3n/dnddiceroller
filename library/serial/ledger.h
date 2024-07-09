#ifndef LEDGER_H
#define LEDGER_H

#include <string>
#include <fstream>
#include "build/characterbook.pb.h"
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
    bool createdCharacterInConstructor = false;

    // real base helpers
    void promptGetLine(string prompt, string error_msg, string &response);
    void promptNumber(string prompt, 
                      int32_t &response,
                      pair<int32_t,int32_t> range = pair<int32_t,int32_t>(INT32_MIN, INT32_MAX)); 

    void setAbilityScoreHelper(dnd::character *c);
    bool createCharacterHelper();
    void getCharacter(string name, dnd::character& character);
    void setCharacterFluffHelper(dnd::character *c);

    // helper functions for getting character ability scores
    int32_t strength(string name);
    int32_t dexterity(string name);
    int32_t constitution(string name);
    int32_t intelligence(string name);
    int32_t wisdom(string name);
    int32_t charisma(string name);

    public:
    ledger(string ledger_path = "./build/character_ledger");
    ~ledger();
    void createCharacter();
    void getCharacterAbilityScores(string name);
    void getCharacterPersonality(string name);
    void getCharacterBackstory(string name);
    void getCharacterPhysicalTraits(string name);
    void getAlignment(string name);
    void listCharacters();

};

#endif
