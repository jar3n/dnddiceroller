#ifndef _EQUIPMENT_ITEM_H_
#define _EQUIPMENT_ITEM_H_

#include <string>
using namespace std;

class EquipmentException : public exception {
    private:
    string name;
    string msg;
    public:
    EquipmentException(string name, string msg) : name(name), msg(msg){}
    string what(){
        return "There is an error with the equipment item " + name + ": " + msg;
    }
};

class EquipmentItem {
    protected:
    string name;
    int cost;
    int weight;
    string description;

    public:
    EquipmentItem(string name, 
                  int cost, 
                  int weight, 
                  string description);
    
    virtual string getDescription();

};

class EquippableItem : public EquipmentItem {
    protected:
    bool equipped;

    public:
    EquippableItem(string name,
                   int cost,
                   int weight,
                   string description, 
                   bool equipped = false);

    void equip();
    virtual string getDescription();
};

class MagicItem : public EquippableItem {
    protected:
    bool attuned;

    public:
    MagicItem(string name,
                   int cost,
                   int weight,
                   string description, 
                   bool equipped = false,
                   bool attuned = false);
    
    void attune();
    virtual string getDescription();
};

class MagicItemWithCharges : public MagicItem {
    private:
    int numCharges;
    int maxNumCharges;
    bool canRecharge;

    public:
    MagicItemWithCharges(string name,
                         int cost,
                         int weight,
                         string description,
                         int numCharges = 1, 
                         bool canRecharge = true,
                         bool equipped = false,
                         bool attuned = false);

    void useCharge();
    void refillCharge();
    void refillAllCharges();
    virtual string getDescription();

};

// magic items that do not have special properties
typedef MagicItem Ring;
typedef MagicItem Rod;
typedef MagicItemWithCharges Staff;
typedef MagicItemWithCharges Wand;
typedef MagicItem Scroll;
typedef MagicItem WonderousItem;

typedef enum ArmorWeightClass {
    none = 0,
    light = 1,
    medium = 2,
    heavy = 3
};

class Armor : public EquippableItem {
    private:
        ArmorWeightClass awc;
        int baseArmorClass;
        int minimumStr;
        bool stealthDisadvantage;
        bool hasDexModCap;
        int dexModCap;

    public:
    Armor(string name,
          int cost,
          int weight,
          string description, 
          bool equipped = false,
          ArmorWeightClass awc = none,
          int baseArmorClass = 10,
          int minimumStr = 0,
          bool stealthDisadvantage = false,
          bool hasDexModCap = false,
          int dexModCap = 2);

    virtual string getDescription();
    int getBaseArmorClass();
    int getMinimumStr();
    bool hasStealthDisadvantage();
    bool doesHaveDexModCap();
    int getDexModCap();

};

class MagicArmor : public MagicItem {
    private:
        ArmorWeightClass awc;
        int baseArmorClass;
        int minimumStr;
        bool stealthDisadvantage;
        bool hasDexModCap;
        int dexModCap;    

    public:
    MagicArmor(string name,
               int cost,
               int weight,
               string description, 
               bool equipped = false,
               bool attuned = false, 
               ArmorWeightClass awc = none,
               int baseArmorClass = 10,
               int minimumStr = 0,
               bool stealthDisadvantage = false,
               bool hasDexModCap = false,
               int dexModCap = 2);

    virtual string getDescription();
};

typedef enum WeaponCategory {
    simple,
    martial
};

typedef enum DamageType {
    acid,
    bludgeoning,
    cold,
    fire,
    force,
    lightning,
    necrotic,
    piercing,
    poison,
    psychic,
    radiant,
    slashing,
    thunder
};

class Weapon : public EquippableItem {
    private:
        DamageType damageType;
        int damageDice;
        int numDamageDice;
        WeaponCategory category;

        // ranged weapon property values
        bool ammunition;
        int ammunitionAmount;
        int silveredAmmunitionAmount;
        bool loading;
        bool range;
        int normalRange;
        int longRange;

        // finesse property values
        bool finesse;

        bool heavy;
        bool light;

        bool reach;
        bool thrown;
        bool twoHanded;

        // versitile weapon proprtly values
        bool versitile;
        int twoHandedDamage;

        // improvised is fun because it has a few meanings
        // 1. pick up something from the ground and treat it 
        // like another weapon
        // 2. it could be a ranged weapon used as a melee weapon or 
        // a thrown melee weapon without the thrown property
        // for ranged weapon used as a melee weapon it does 1d4 damage
        // for a melee weapon thrown without thrown property it does 1d4 damage
        // the range for a improvised thrown melee weapon is 20 normal and 60 long
        bool improvised;
        bool silvered;

        // enum helper functions
        string getWeaponDamageType();
        string getWeaponCategory();
        string getWeaponProperties();
        string getRange(); // string is "ranged (normalrange/longrange)"


    public:
        Weapon(string name,
               int cost,
               int weight,
               string description, 
               bool equipped = false,
               DamageType damageType, 
               int damageDice,
               int numDamageDice,
               WeaponCategory category,
               bool ranged = false, 
               bool loading = false,
               bool ammunition = false, 
               int ammunitionAmount = 0,
               int silveredAmmunitionAmount = 0,
               int normalRange = 0,
               int longRange = 0,
               bool finesse = false,
               bool heavy = false,
               bool light = false,
               bool reach = false,
               bool thrown = false,
               bool twoHanded = false,
               bool versitile = false, 
               int twoHandedDamage = 0,
               bool improvised = false,
               bool silvered = false);

        virtual string getDescription();

        int getAmmunition(bool silvered); // returns both regular and silvered ammunition
        void useAmmunition(bool silvered); // uses ammunition if its a ranged weapon
        void restockAmmunition(bool silvered, int numToRestock);
        void convertToSilverAmmunition(int numToConvert);
        int getNormalRange();
        int getLongRange();
        bool isRanged(); // returns whether this is a ranged weapon (,a thrown melee weapon) or a melee weapon

        bool isFinesse();
        
        bool isVersitile();
        int useTwoHandsDamage(bool choice); // if false use single hand attack

};

class MagicWeapon : public MagicItem {
    private:
        DamageType damageType;
        int damageDice;
        int numDamageDice;
        WeaponCategory category;

        // ranged weapon property values
        bool ammunition;
        int ammunitionAmount;
        int silveredAmmunitionAmount;
        bool loading;
        bool range;
        int normalRange;
        int longRange;

        // finesse property values
        bool finesse;

        bool heavy;
        bool light;

        bool reach;
        bool thrown;
        bool twoHanded;

        // versitile weapon proprtly values
        bool versitile;
        int twoHandedDamage;

        // improvised is fun because it has a few meanings
        // 1. pick up something from the ground and treat it 
        // like another weapon
        // 2. it could be a ranged weapon used as a melee weapon or 
        // a thrown melee weapon without the thrown property
        // for ranged weapon used as a melee weapon it does 1d4 damage
        // for a melee weapon thrown without thrown property it does 1d4 damage
        // the range for a improvised thrown melee weapon is 20 normal and 60 long
        bool improvised;
        bool silvered;

        // enum helper functions
        string getWeaponDamageType();
        string getWeaponCategory();
        string getWeaponProperties();
        string getRange(); // string is "ranged (normalrange/longrange)"


    public:
        MagicWeapon(string name,
               int cost,
               int weight,
               string description, 
               bool equipped = false,
               bool attuned = false,
               DamageType damageType, 
               int damageDice,
               int numDamageDice,
               WeaponCategory category,
               bool ranged = false, 
               bool loading = false,
               bool ammunition = false, 
               int ammunitionAmount = 0,
               int silveredAmmunitionAmount = 0,
               int normalRange = 0,
               int longRange = 0,
               bool finess = false,
               bool useStrengthOrDex = false,
               bool heavy = false,
               bool light = false,
               bool reach = false,
               bool thrown = false,
               bool twoHanded = false,
               bool versitile = false, 
               int twoHandedDamage = 0,
               bool improvised = false,
               bool silvered = false);

        virtual string getDescription();

        int getAmmunition(bool silvered); // returns both regular and silvered ammunition
        void useAmmunition(bool silvered); // uses ammunition if its a ranged weapon
        void restockAmmunition(bool silvered, int numToRestock);
        void convertToSilverAmmunition(int numToConvert);
        int getNormalRange();
        int getLongRange();
        bool isRanged(); // returns whether this is a ranged weapon (,a thrown melee weapon) or a melee weapon

        bool isFinesse();
        
        bool isVersitile();
        int useTwoHandsDamage(bool choice); // if false use single hand attack


};



#endif