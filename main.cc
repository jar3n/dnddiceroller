#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/program_options.hpp>
#include<map>

// my stuff
#include "library/base/dice.h"
#include "library/base/skill.h"
#include "library/base/weapon.h"

using namespace std;
using namespace boost::property_tree;
using namespace dnd;
using namespace boost::program_options;

typedef enum ability{
    strength = 0,
    dexerity = 1,
    constitution = 2,
    intelligence = 3,
    wisdom = 4,
    charisma = 5
};


class invalidArgException : public exception{
    private:
    string providedArg;
    vector<string> expArgs;

    public:
    invalidArgException(string providedArgument, vector<string> expArgs) : 
    providedArg(providedArgument),
    expArgs(expArgs){

    }
    string what(){
        string msg = "The provided argument is not one of the expected argumets. The expected arguments are:\n";
        for(string arg : expArgs){
            msg +=  "\t" + arg + "\n";
        }
    }
};


int isAbilityName(string name){
    if (name.compare("str")){return 0;}
    else if(name.compare("dex")){return 1;}
    else if(name.compare("con")){return 2;}
    else if(name.compare("int")){return 3;}
    else if(name.compare("wis")){return 4;}
    else if(name.compare("cha")){return 5;}
    else{
        throw invalidArgException(name, {"str", "dex", "con", "int", "wis", "cha"});
    }
}



int main(int argc, char * argv[]){
    /*
        Commands I want to have:
        - rolls:
            - saving throws
            - ability checks
                - skill checks
                - ability score checks
            - attack rolls
            - weapon damage rolls
            - spell damage rolls
            - death saves
        - get info;
            - character general info
            - Feature information
            - health
            - race information
            - background information
            - equipment
                - total weight
                - list of items
                    - attuned items
            - proficiencies (besides skill and saves)
            - languages
            - armor class
            - available and total spell slots
        - modify stats:
            - health
            - money
            - available spell slots
            - level up (this will be a doozy hold till after character class implementation)
            - clear death saves when revived
            - dropping item 
            - adding new item
    */

    // TEMP stuff that will go into character class
    int abilityScores[6] = {19, 16, 15, 11, 13, 11};
    

    options_description rolls("Dice Rolls");
    rolls.add_options()
                     ("saving", value<string>(),"roll a saving dice roll"
                                                "\tOptions are:"
                                                "\t\tstr (Strength)"
                                                "\t\tdex (Dexterity)"
                                                "\t\tcon (Constitution)"
                                                "\t\tint (Intelligence)"
                                                "\t\twis (Wisdom)"
                                                "\t\tcha (Charisma)")
                     ("abilitycheck", value<string>(), "roll an ability check"
                                                       "\tOptions are:"
                                                        "\t\tstr (Strength)"
                                                        "\t\tdex (Dexterity)"
                                                        "\t\tcon (Constitution)"
                                                        "\t\tint (Intelligence)"
                                                        "\t\twis (Wisdom)"
                                                        "\t\tcha (Charisma)")
                     ("skillcheck", value<string>(), "roll a skill check"
                                                     "\tOptions are:"
                                                     "\t\tacro (Acrobatics)"
                                                     "\t\tanim (Animal Handling)"
                                                     "\t\tarca (Arcana)"
                                                     "\t\tathl (Athletics)"
                                                     "\t\tdece (Deception)"
                                                     "\t\thist (History)"
                                                     "\t\tinsi (Insight)"
                                                     "\t\tinti (Intimidation)"
                                                     "\t\tinve (Investigation)"
                                                     "\t\tmedi (Medicine)"
                                                     "\t\tnatu (Nature)"
                                                     "\t\tperc (Perception)"
                                                     "\t\tperf (Performance)"
                                                     "\t\tpers (Persuasion)"
                                                     "\t\treli (Religion)"
                                                     "\t\tslei (Sleight of Hand)"
                                                     "\t\tstea (Stealth)"
                                                     "\t\tsurv  (Survival)")
                     ("attack", value<string>(), "roll to land a attack with the provided weapon")
                     ("damage", value<string>(), "roll for attack damage")
                     ("spelldamage", value<string>(), "roll damage of a spell")
                     ("deathsave", "roll a death saving dice");
    options_description info("Informational Commands");
    options_description modify_stats("Update Character Status Commands");

    command_line_parser parser{argc, argv};
    parser.options(rolls);
    variables_map vm;
    
    try{
        parsed_options parsed = parser.run();
        store(parsed, vm);
    } catch (exception& e){
        cout << e.what() << "\n";
    }
    notify(vm);

    ability selectedAbility;


    // TODO
    // have a main while loop 
    // with a way to safely get out
    // have a function that prompts for a character file
    // have a function that generates a random number
    // cout << "HELLO WORLD\n";

    // Dice * mydice = new Dice();

    // cout << "This is a d4 from my dice class: " << mydice->rolld4() << "\n";
    // cout << "This is a d6 from my dice class: " << mydice->rolld6() << "\n";
    // cout << "This is a d8 from my dice class: " << mydice->rolld8() << "\n";
    // cout << "This is a d10 from my dice class: " << mydice->rolld10() << "\n";
    // cout << "This is a d12 from my dice class: " << mydice->rolld12() << "\n";
    // cout << "This is a d20 from my dice class: " << mydice->rolld20() << "\n";
    // cout << "This is a d100 from my dice class: " << mydice->rolld100() << "\n";
    // cout << "This is a dX from my dice class with cap of 1000: " << mydice->rolldX(1000) << "\n";

    // int proficiency_bonus = 2;
    // int base_modifier = 3;

    // Skill * testBaseSkill = new Skill("test_base_skill", base_modifier, proficiency_bonus, false, false);
    // Skill * testProficientSkill = new Skill("test_proficient_skill", base_modifier, proficiency_bonus, true, false);
    // Skill * testExpertSkill = new Skill("test_expert_skill", base_modifier, proficiency_bonus, false, true);

    // cout << "Skill: "  << testBaseSkill->getName() << "\n\tModifier " << testBaseSkill->getModifier() << "\n\troll: " << testBaseSkill->rollSkill() << "\n";
    // cout << "Skill: "  << testProficientSkill->getName() << "\n\tModifier " << testProficientSkill->getModifier() << "\n\troll: " << testProficientSkill->rollSkill() << "\n";
    // cout << "Skill: "  << testExpertSkill->getName() << "\n\tModifier " << testExpertSkill->getModifier() << "\n\troll: " << testProficientSkill->rollSkill() << "\n";

    // try {
    //     Skill * testFailSkill = new Skill("test_fail_skill", base_modifier, proficiency_bonus, true, true);
    // } catch(SkillException e){
    //     cout << e.what() << "\n";
    // }
    
    // Weapon * testWeapon = new Weapon("test weapon", 10, 6, 3, "stabbing", 12, 5, {"thrown", "simple", "light"});
    // cout << testWeapon->getDetails();
    // cout << "Rolling damage with " << testWeapon->getName() << ": " << testWeapon->rollDamage() << "\n";

    // string charfile("/home/jenglander/dndcode/testfiles/chartemp.json");
    // cout << "Reading in the following character file: " << charfile << "\n";

    // ptree root;
    // read_json(charfile, root);
    // string charName = root.get<string>("character.base-info.name");
    // cout << "The character's name is " << charName << "\n";

    return 0;
}   