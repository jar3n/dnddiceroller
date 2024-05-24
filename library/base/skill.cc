#include "skill.h"

Skill::Skill(string name, 
             int base_stat_modifier, 
             int proficiency_bonus,
             bool isProficient, 
             bool hasExpertise) :
name(name),
proficiency_bonus(proficiency_bonus),
proficient(isProficient),
expert(hasExpertise) {
    if (proficient && expert){
        throw SkillException(name, "Cannot be both proficient and have expertise.");
    }
    else if (proficient){
        modifier = proficiency_bonus + base_stat_modifier;
    } else if (expert){
        modifier = (2 * proficiency_bonus) + base_stat_modifier;
    } else {
        modifier = base_stat_modifier;
    }
}

int Skill::getModifier(){
    return modifier;
}

bool Skill::isProficient(){
    return proficient;
}

bool Skill::hasExpertise(){
    return expert;
}

