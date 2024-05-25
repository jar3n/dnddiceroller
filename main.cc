#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// my stuff
#include "library/base/dice.h"
#include "library/base/skill.h"

using namespace std;
using namespace boost::property_tree;
using namespace dnd;

int main(int argc, char * argv[]){
    // TODO
    // have a main while loop 
    // with a way to safely get out
    // have a function that prompts for a character file
    // have a function that generates a random number
    cout << "HELLO WORLD\n";

    Dice * mydice = new Dice();

    cout << "This is a d4 from my dice class: " << mydice->rolld4() << "\n";
    cout << "This is a d6 from my dice class: " << mydice->rolld6() << "\n";
    cout << "This is a d8 from my dice class: " << mydice->rolld8() << "\n";
    cout << "This is a d10 from my dice class: " << mydice->rolld10() << "\n";
    cout << "This is a d12 from my dice class: " << mydice->rolld12() << "\n";
    cout << "This is a d20 from my dice class: " << mydice->rolld20() << "\n";
    cout << "This is a d100 from my dice class: " << mydice->rolld100() << "\n";
    cout << "This is a dX from my dice class with cap of 1000: " << mydice->rolldX(1000) << "\n";

    int proficiency_bonus = 2;
    int base_modifier = 3;

    Skill * testBaseSkill = new Skill("test_base_skill", base_modifier, proficiency_bonus, false, false);
    Skill * testProficientSkill = new Skill("test_proficient_skill", base_modifier, proficiency_bonus, true, false);
    Skill * testExpertSkill = new Skill("test_expert_skill", base_modifier, proficiency_bonus, false, true);

    cout << "Skill: "  << testBaseSkill->getName() << "\n\tModifier " << testBaseSkill->getModifier() << "\n\troll: " << testBaseSkill->rollSkill() << "\n";
    cout << "Skill: "  << testProficientSkill->getName() << "\n\tModifier " << testProficientSkill->getModifier() << "\n\troll: " << testProficientSkill->rollSkill() << "\n";
    cout << "Skill: "  << testExpertSkill->getName() << "\n\tModifier " << testExpertSkill->getModifier() << "\n\troll: " << testProficientSkill->rollSkill() << "\n";

    try {
        Skill * testFailSkill = new Skill("test_fail_skill", base_modifier, proficiency_bonus, true, true);
    } catch(SkillException e){
        cout << e.what() << "\n";
    }
    

    string charfile("/home/jenglander/dndcode/testfiles/chartemp.json");
    cout << "Reading in the following character file: " << charfile << "\n";

    ptree root;
    read_json(charfile, root);
    string charName = root.get<string>("character.base-info.name");
    cout << "The character's name is " << charName << "\n";

    return 0;
}   