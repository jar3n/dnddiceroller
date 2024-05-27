#include "equipment_item.h"

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
