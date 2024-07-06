#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <map>
#include <vector>

#include "equipment_item.h"
#include "skill.h"

using namespace std;

enum base_stats {
    STRENGTH = 0,
    DEXTERITY = 1,
    CONSTITUTION = 2,
    INTELLIGENCE = 3,
    WISDOM = 4,
    CHARISMA = 5
};

enum derived_stats {
    ACROBATICS = 0,
    ANIMAL_HANDLING = 1,
    ARCANA = 2,
    ATHLETICS = 3,
    DECEPTION = 4,
    HISTORY = 5,
    INSIGHT = 6,
    INTIMIDATION = 7,
    INVESTIGATION = 8,
    MEDICINE = 8,
    NATURE = 10,
    PERCEPTION = 11,
    PERFORMANCE = 12,
    PERSUASION = 13,
    RELIGION = 14,
    STEALTH = 15,
    SLEIGHT_OF_HAND = 16,
    SURVIVAL = 17
};

class Character {
    public:

    Character();
    virtual ~Character(){};

    int getSavingThrowMod(base_stats base_stat);
    int getBaseStatMod(base_stats base_stat);
    int getDerivedStatMod(derived_stats derived_stat);

    private:

    /*
        Order of base stats:
        0. strength
        1. dexterity
        2. constitution
        3. intelligence
        4. wisdom
        5. charisma
    */
    int base_stats[6];
    int proficiency_bonus;

    int level;
    int death_saves_success;
    int death_saves_fails;

    // based on the class
    int hit_points;
    int max_hit_points;
    int temp_hit_points;

    int inspiration;

    /*
        Currencies:
        0. Copper Pieces
        1. Silver Pieces
        2. Electrum Pieces
        3. Gold Pieces
        4. Platinum Pieces
    */
    int money[5];

    // just character info no actual affect on rolls
    string name;
    string personality_traits;
    string ideals;
    string bonds;
    string flaws;
    string alignment;
    string player_name;
    int age;
    int height; // height in inches 
    int weight; // in lbs
    string eye_color;
    string skin_color;
    string hair_color;

    map<string, EquipmentItem*> equipment;
    vector<string> attunedItems;

    /*
        Spell slots
    */
    int spell_slot_totals[10];
    int spell_slots_available[10];
    // TODO add a Spell class
    // contains descriptions, damange types, DC save values
    // base spell slot (i.e. the lowest spell slot to cast the spell at)
    // spell cost
    map<string, string> spells;

    // these are also determined by class in part
    int spellcasting_ability;
    int spell_save_dc;
    int spell_attack_bonus;

    /*
        Features
    */
    // TODO add a Feature class that contains
    // proficiency/expertise bonuses
    // description
    vector<string> features;
};

#endif