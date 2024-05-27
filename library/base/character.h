#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <vector>

using namespace std;

class Character {
    public:

    Character(int level, int base_stats[6]);
    virtual ~Character(){};

    string getAbilityScoresAndModifiers();
    
    string getHitPoints();
    string takeDamage(int damage);
    string heal(int health);

    string getDeathSaves();
    string rollDeathSave();

    string getMoney();
    // string buyItem();
    // string sellItem();

    // vector<string> getEquipment();

    // int getPassivePerception();

    private:

    /*
        look up the modifer 
        for a base stat
    */
    int getModifier(int base_stat);

    // short cut functions for accessing the ability scores
    int strength();
    int dexterity();
    int constitution();
    int intelligence();
    int wisdom();
    int charisma();

    protected:
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
    
    // TODO add Background class 
    // background class provides proficiencies 
    // to the character
    // and determines size

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