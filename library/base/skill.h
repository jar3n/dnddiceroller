#ifndef _SKILL_H_
#define _SKILL_H_

#include <string>

using namespace std;

class SkillException : public exception {
    private:
    string msg;
    string skillName;
    public:

    SkillException(string skillName, string msg) : 
    skillName(skillName),
    msg(msg){}

    const char * what(string msg){
        return ("There is an error with " + skillName + ": " + msg).c_str();
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

    virtual int rollSkill();

    int getModifier();

    bool isProficient();
    bool hasExpertise();

    private:
    string name;
    int modifier;
    bool proficient;
    bool expert;
    int proficiency_bonus;
};

#endif