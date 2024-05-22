#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <vector>

using namespace std;

class Character {
    public:

    Character(int level, int base_stats[6]){}
    virtual ~Character() = 0;
    
    int getStrength();
    int getDexterity();
    int getConstitution();
    int getIntelligence();
    int getWisdom();
    int getCharisma();

    int getStrengthMod();
    int getDexterityMod();
    int getConstitutionMod();
    int getIntelligenceMod();
    int getWisdomMod();
    int getCharismaMod();

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
    int getModifier(int base_stat);

    protected:
    /*
        Order of base stats:
        0. strength
        1. dexterity
        2. constitution
        3. intelligence
        4. wisdom
        5. charisma

        for simplicity these are the base stats before any 
        ability score improvement features are applied
        i.e. level 1 base stats
    */
    int base_stats[6];

    int level;
    bool death_saves_success[3];
    bool death_saves_fails[3];

    // based on the class
    int hit_points;

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

     determined by background, class, race, and 
    */
    unsigned int proficient_skills;
    unsigned int expertise_skils;

    // determined based on class
    unsigned int proficient_saving_throws;

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