#ifndef _SKILL_H_
#define _SKILL_H_

#include <string>

#include "dice.h"

using namespace std;
using namespace dnd;

class SkillException : public exception {
    private:
    string msg;
    string skillName;
    public:

    SkillException(string skillName, string msg) : 
    skillName(skillName),
    msg(msg){}

    string what(){
        string err_msg = "There is an error with ";
        err_msg += skillName;
        err_msg += ": ";
        err_msg += msg;
        return err_msg;
    }

};

class Skill {
    public:
        Skill(string name, 
            int base_stat_modifier,
            int proficiency_bonus,
            bool isProficient, 
            bool hasExpertise);
        ~Skill(){}

        int rollSkill();

        int getModifier();

        bool isProficient();
        bool hasExpertise();

        string getName();

    private:
        string name;
        int modifier;
        bool proficient;
        bool expert;
        int proficiency_bonus;

        Dice * skillDice;
};

#endif