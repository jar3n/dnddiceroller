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

// add the following kinds of items
// weapon
// magic and not
// there are other types of magic items, but they arent special like 
// armor or weapons so they can be types basically
// despite some potions being magical items none are attunable so i will not list them here





#endif