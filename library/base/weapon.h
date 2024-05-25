#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <string>
#include <vector>
#include "dice.h"

using namespace std;
using namespace dnd;

class Weapon {
    public:
        Weapon(string name, 
            int cost, 
            int damage_dice, 
            int num_damage_dice,
            string damage_type,
            int weight,
            int range, 
            vector<string> properties);

        int rollDamage();

        string getDetails();
        string getName();
    
    private:
        string name;
        int cost; 
        int damage_dice;
        string damage_type;
        int num_damage_dice;
        int weight;
        vector<string> properties;
        Dice * weaponDice;
        int range;

};

#endif 