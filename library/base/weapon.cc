#include "weapon.h"

Weapon::Weapon(string name, 
               int cost, 
               int damage_dice, 
               int num_damage_dice,
               string damage_type, 
               int weight,
               int range,
               vector<string> properties) :
               name(name),
               cost(cost),
               damage_dice(damage_dice),
               num_damage_dice(num_damage_dice),
               damage_type(damage_type),
               weight(weight),
               range(range),
               properties(properties)
{
    weaponDice = new Dice();
}

int Weapon::rollDamage()
{
    int damage = 0;
    for (int i = 0; i < num_damage_dice; i++){
        damage += weaponDice->rolldX(damage_dice);
    }

    return damage;
}

string Weapon::getDetails()
{
    string desc = "The " + name + ": \n";
    desc += "\tDamage Type: " + damage_type + "\n";
    desc += "\tDamage Dice: " + to_string(num_damage_dice) + "d" + to_string(damage_dice) + "\n";
    desc += "\tWeight: " + to_string(weight) + "\n";
    desc += "\tProperties: \n";

    for (string& i : properties){
        desc += "\t\t" + i + "\n";
    }

    return desc;
}

string Weapon::getName()
{
    return name;
}
