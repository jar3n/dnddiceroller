#include "equipment_item.h"

using namespace std;

EquipmentItem::EquipmentItem(string name, 
                             int cost, 
                             int weight,
                             string description) :
                             name(name),
                             cost(cost),
                             weight(weight),
                             description(description),
                             attuned(false),
                             equipped(false)
{
}

EquipmentItem::EquipmentItem(string name, 
                             int cost, 
                             int weight,
                             string description,
                             bool equipped) :
                             name(name),
                             cost(cost),
                             weight(weight),
                             description(description),
                             equipped(equipped),
                             attuned(false)
{
}

EquipmentItem::EquipmentItem(string name, 
                             int cost, 
                             int weight,
                             string description, 
                             bool equipped, 
                             bool attuned) :
                             name(name),
                             cost(cost),
                             weight(weight),
                             description(description),
                             equipped(equipped),
                             attuned(attuned)
{
    if (!equipped && attuned){
        throw EquipmentException(name, "the item must be equipped to be attuned.");
    }
}

void EquipmentItem::attune()
{
    if(equipped){
        attuned = true;
    } else {
        throw EquipmentException(name, "the item must be equipped to be attuned.");
    }
}

void EquipmentItem::equip()
{
    equipped = true;
}
