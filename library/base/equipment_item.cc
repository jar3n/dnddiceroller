#include "equipment_item.h"
#include <string.h>

using namespace std;

EquipmentItem::EquipmentItem(string name, 
                             int cost, 
                             int weight,
                             string description) :
                             name(name),
                             cost(cost),
                             weight(weight),
                             description(description)
{
}

string EquipmentItem::getDescription()
{
    string equipmentDescription = name + ":\n";
    equipmentDescription += "Cost: " + to_string(cost) + "\n";
    equipmentDescription += "Weight: " + to_string(weight) + "\n";
    equipmentDescription += description + "\n";
    return equipmentDescription;
}

EquippableItem::EquippableItem(string name, 
                               int cost, 
                               int weight, 
                               string description, 
                               bool equipped = false) :
                               EquipmentItem(name, cost, weight, description),
                               equipped(equipped)

{
}

void EquippableItem::equip()
{
    if(equipped){
        throw EquipmentException(name, "is already equipped.");
    } else {
        equipped = true;
    }
}

string EquippableItem::getDescription()
{
    
    string equippedStatus = equipped ? "yes" : "no";
    string equipmentDescription = name + ":\n";
    equipmentDescription += "Cost: " + to_string(cost) + "\n";
    equipmentDescription += "Weight: " + to_string(weight) + "\n";
    equipmentDescription += "Equipped: " + equippedStatus + "\n";
    equipmentDescription += description + "\n";
    return equipmentDescription;
}

MagicItem::MagicItem(string name, 
                             int cost, 
                             int weight, 
                             string description, 
                             bool equipped = false, 
                             bool attuned = false) :
                             EquippableItem(name, cost, weight, description, equipped),
                             attuned(attuned)
{
    if (!equipped && attuned){
        throw EquipmentException(name, "cannot be attuned when not equipped.");
    }
}

void MagicItem::attune()
{
    if (!equipped){
        throw EquipmentException(name, "cannot be attuned when not equipped.");
    } else {
        attuned = true;
    }
}

string MagicItem::getDescription()
{
    string equippedStatus = equipped ? "yes" : "no";
    string attunedStatus = attuned ? "yes" : "no";
    string equipmentDescription = name + ":\n";
    equipmentDescription += "Cost: " + to_string(cost) + "\n";
    equipmentDescription += "Weight: " + to_string(weight) + "\n";
    equipmentDescription += "Equipped: " + equippedStatus + "\n";
    equipmentDescription += "Attuned: " + attunedStatus + "\n";
    equipmentDescription += description + "\n";
    return equipmentDescription;
}

MagicItemWithCharges::MagicItemWithCharges(string name, 
                                           int cost, 
                                           int weight, 
                                           string description, 
                                           int numCharges = 1, 
                                           bool canRecharge = true, 
                                           bool equipped = false, 
                                           bool attuned = false) :
                                           MagicItem(name, cost, weight, description, equipped, attuned),
                                           numCharges(numCharges),
                                           canRecharge(canRecharge)
{
    if(numCharges <= 0){
        throw EquipmentException(name, "must have at least one charge.");
    } 
}

void MagicItemWithCharges::useCharge()
{
    if(numCharges > 0) {
        numCharges -= 1;
    } else {
        throw EquipmentException(name, "has no more charges to expend.");
    }
}

void MagicItemWithCharges::refillCharge()
{
    if(canRecharge){
        if(numCharges == maxNumCharges){
            throw EquipmentException(name, "at full charge.");
        } else {
            numCharges++;
        }
    } else {
        throw EquipmentException(name, "cannot recharge.");
    }
}

void MagicItemWithCharges::refillAllCharges()
{
    if(canRecharge){
        numCharges = maxNumCharges;
    } else {
        throw EquipmentException(name, "cannot recharge.");
    }
}

string MagicItemWithCharges::getDescription()
{
    string equippedStatus = equipped ? "yes" : "no";
    string attunedStatus = attuned ? "yes" : "no";
    string equipmentDescription = name + ":\n";
    equipmentDescription += "Cost: " + to_string(cost) + "\n";
    equipmentDescription += "Weight: " + to_string(weight) + "\n";
    equipmentDescription += "Equipped: " + equippedStatus + "\n";
    equipmentDescription += "Attuned: " + attunedStatus + "\n";
    equipmentDescription += "Number of Charges: " + to_string(numCharges) + "\n"; 
    equipmentDescription += description + "\n";
    return equipmentDescription;
}

Armor::Armor(string name, 
             int cost, 
             int weight, 
             string description, 
             bool equipped, 
             ArmorWeightClass awc, 
             int baseArmorClass, 
             int minimumStr, 
             bool stealthDisadvantage, 
             bool hasDexModCap, 
             int dexModCap) :
             EquippableItem(name, cost, weight, description, equipped),
             awc(awc),
             baseArmorClass(baseArmorClass),
             minimumStr(minimumStr),
             stealthDisadvantage(stealthDisadvantage),
             hasDexModCap(hasDexModCap),
             dexModCap(dexModCap)
{
}

string Armor::getDescription()
{
    string equippedStatus = equipped ? "yes" : "no";
    string equipmentDescription = name + ":\n";
    equipmentDescription += "Cost: " + to_string(cost) + "\n";
    equipmentDescription += "Weight: " + to_string(weight) + "\n";
    equipmentDescription += "Equipped: " + equippedStatus + "\n";
    equipmentDescription += "Base Armor Class: " + to_string(baseArmorClass) + "\n";
    if (hasDexModCap) equipmentDescription += "Dexterity Modifier Cap: " + to_string(dexModCap) + "\n";
    if (stealthDisadvantage) equipmentDescription += "Armor has a Stealth Disadvantage.\n";
    equipmentDescription += description + "\n";
    return equipmentDescription;
}

int Armor::getBaseArmorClass()
{
    return baseArmorClass;
}

int Armor::getMinimumStr()
{
    return minimumStr;
}

bool Armor::hasStealthDisadvantage()
{
    return stealthDisadvantage;
}

bool Armor::doesHaveDexModCap()
{
    return hasDexModCap;
}

int Armor::getDexModCap()
{
    return dexModCap;
}

MagicArmor::MagicArmor(string name,
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
                       int dexModCap = 2) :
                       MagicItem(name, cost, weight, description, equipped, attuned)
{
}

string MagicArmor::getDescription()
{
    string equippedStatus = equipped ? "yes" : "no";
    string attunedStatus = attuned ? "yes" : "no";
    string equipmentDescription = name + ":\n";
    equipmentDescription += "Cost: " + to_string(cost) + "\n";
    equipmentDescription += "Weight: " + to_string(weight) + "\n";
    equipmentDescription += "Equipped: " + equippedStatus + "\n";
    equipmentDescription += "Attuned: " + attunedStatus + "\n";
    equipmentDescription += "Base Armor Class: " + to_string(baseArmorClass) + "\n";
    if (hasDexModCap) equipmentDescription += "Dexterity Modifier Cap: " + to_string(dexModCap) + "\n";
    if (stealthDisadvantage) equipmentDescription += "Armor has a Stealth Disadvantage.\n";
    equipmentDescription += description + "\n";
    return equipmentDescription;
}

string Weapon::getWeaponDamageType()
{   
    switch(damageType){
        case acid:
            return "acid";
        case bludgeoning:
            return "bludgeoning";
        case cold:
            return "cold";
        case fire:
            return "fire";
        case force:
            return "force";
        case lightning:
            return "lightning";
        case necrotic:
            return "necrotic";
        case piercing:
            return "piercing";
        case poison:
            return "poison";
        case psychic:
            return "psychic";
        case radiant:
            return "radiant";
        case slashing:
            return "slashing";
        case thunder:
            return "thunder";
        default:
            throw EquipmentException(name, "has an invalid damage type number: " + to_string(damageType));
    }
}

string Weapon::getWeaponCategory(){
    switch(category){
        case simple:
            return "simple";
        case martial:
            return "martial";
        default:
            throw EquipmentException(name, "has an invalid weapon category number: " + to_string(category));
    }
}

string Weapon::getWeaponProperties()
{
    string weaponProperties; 
    // properties: ammunition, range, loading, finesse, heavy, light, reach, thrown, twohanded, versitile
    // improvised, silvered

    weaponProperties += ammunition ? "Ammunition (" + to_string(ammunitionAmount) + "/" + to_string(silveredAmmunitionAmount) + "), " : "";
    weaponProperties += getRange() + ", ";
    weaponProperties += loading ? "Loading, " : "";
    weaponProperties += finesse ? "Finesse,  " : "";
    weaponProperties += light ? "Light, " : "";
    weaponProperties += heavy ? "Heavy, " : "";
    weaponProperties += reach ? "Reach, " : "";
    weaponProperties += twoHanded ? "Two Handed, " : "";
    weaponProperties += versitile ? "Versitile, " : "";
    weaponProperties += improvised ? "Improvised, " : "";
    weaponProperties += silvered ? "Silvered, " : "";

    char lastChar = weaponProperties.at(weaponProperties.length() - 1);
    if (lastChar == ',') weaponProperties.pop_back();

    return weaponProperties;
}

string Weapon::getRange()
{
    if (range){
        return "Ranged (" + to_string(normalRange) + "/" + to_string(longRange) + ")";
    } else if (thrown) {
        return "Thrown (" + to_string(normalRange) + "/" + to_string(longRange) + ")";
    } else {
        return "";
    }
}

Weapon::Weapon(string name, 
               int cost, 
               int weight, 
               string description, 
               bool equipped, 
               DamageType damageType, 
               int damageDice, 
               int numDamageDice, 
               WeaponCategory category, 
               bool ranged, 
               bool loading, 
               bool ammunition, 
               int ammunitionAmount, 
               int silveredAmmunitionAmount, 
               int normalRange, 
               int longRange, 
               bool finesse,
               bool heavy, 
               bool light, 
               bool reach, 
               bool thrown, 
               bool twoHanded, 
               bool versitile, 
               int twoHandedDamage, 
               bool improvised, 
               bool silvered) :
               EquippableItem(name, cost, weight, description, equipped),
               damageType(damageType),
               damageDice(damageDice),
               numDamageDice(numDamageDice),
               category(category),
               range(ranged),
               loading(loading),
               ammunition(ammunition),
               ammunitionAmount(ammunitionAmount),
               silveredAmmunitionAmount(silveredAmmunitionAmount),
               normalRange(normalRange),
               longRange(longRange),
               finesse(finesse),
               heavy(heavy),
               light(light),
               reach(reach),
               thrown(thrown),
               twoHanded(twoHanded),
               versitile(versitile),
               twoHandedDamage(twoHandedDamage),
               improvised(improvised),
               silvered(silvered)
{
}

string Weapon::getDescription()
{
    string equippedStatus = equipped ? "yes" : "no"; 
    string equipmentDescription = name + ":\n";
    equipmentDescription += "Cost: " + to_string(cost) + "\n";
    equipmentDescription += "Weight: " + to_string(weight) + "\n";
    equipmentDescription += "Category: " + getWeaponCategory() + "\n";
    equipmentDescription += "Damge Type" + getWeaponDamageType()  + "\n";
    equipmentDescription += "Properties: " + getWeaponProperties() +"\n";
    equipmentDescription += "Equipped: " + equippedStatus + "\n";
    equipmentDescription += description + "\n";
    return equipmentDescription;
}

int Weapon::getAmmunition(bool silvered)
{
    if (silvered){
        return silveredAmmunitionAmount;
    } else {
        return ammunitionAmount;
    }
}

void Weapon::useAmmunition(bool silvered)
{
    if (silvered){
        silveredAmmunitionAmount--;
    } else {
        ammunitionAmount--;
    }
}

void Weapon::restockAmmunition(bool silvered, int numToRestock)
{
    if (silvered){
        silveredAmmunitionAmount += numToRestock;
    } else {
        ammunitionAmount += numToRestock;
    }
}

void Weapon::convertToSilverAmmunition(int numToConvert)
{
    silveredAmmunitionAmount += numToConvert;
    ammunitionAmount -= numToConvert;
}

int Weapon::getNormalRange()
{
    if (range){
        return normalRange;
    } else {
        throw EquipmentException(name, "is not a ranged weapon and thus has no normal range.");
    }
}

int Weapon::getLongRange()
{
    if (range){
        return longRange;
    } else {
        throw EquipmentException(name, "is not a ranged weapon and thus has no long range.");
    }
}

bool Weapon::isRanged()
{
    return range;
}

bool Weapon::isFinesse()
{
    return finesse;
}

bool Weapon::isVersitile()
{
    return versitile;
}

int Weapon::useTwoHandsDamage(bool choice)
{
    if (versitile){
        if (choice){
            return twoHandedDamage;
        } else {
            return damageDice;
        }
    } else {
        throw EquipmentException(name, "is not a versitile weapon.");
    }
}
