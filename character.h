#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <vector>

using namespace std;

class Character {
    public:
    Character();
    ~Character();

    int getStrength();
    int getDexterity();
    int getConstitution();
    int getIntelligence();
    int getWisdom();
    int getCharisma();

    int getProficiency();
    int getExpertise();
    
    int getHitPoints();

    bool * getDeathSaves();

    vector<string> getEquipment();

    int getPassivePerception();

    private:

    /*
        look up the modifer 
        for a base stat
    */
    int getModifier();


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

    int level;
    int hit_points;
    bool death_saves_success[3];
    bool death_saves_fails[3];

    /* using a number where the least signifcant 18 bits 
     represent the dnd skill proficiency and expertise
     0 means not proficient
     1 means proficient
     list of the bits and their significance
     0x00001 Acrobatics
     0x00002 Animal Handling
     0x00004 Arcana
     0x00008 Athletics
     0x00010 Deception
     0x00020 History
     0x00040 Insight
     0x00080 Intimidation
     0x00100 Investigation
     0x00200 Medicine
     0x00400 Nature
     0x00800 Perception
     0x01000 Performance
     0x02000 Persuasion
     0x04000 Religion
     0x08000 Sleight of Hand
     0x10000 Stealth
     0x20000 Survival
    */
    unsigned int proficient_skills;
    unsigned int expertise_skils;

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

    
    // TODO add Background class 
    // background class provides proficiencies 
    // to the character

    // TODO add an equipment 
    // class for equipment items so that 
    // you can store descriptions and amounts of equipment items
    vector<string> equipment;

    // TODO add race class 
    // race determines speed
    // race also has abilities

    /*
        Spell slots
    */
    int spell_slot_totals[10];
    int spell_slots_available[10];
    // TODO add a Spell class
    // contains descriptions, damange types, DC save values
    // base spell slot (i.e. the lowest spell slot to cast the spell at)
    // spell cost
    vector<string> spells;

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