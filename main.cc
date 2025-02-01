#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>
#include <algorithm>

#include "library/base/include/dice.h"
#include "library/interface/creator.h"
#include "library/interface/accessor.h"
#include "library/interface/roller.h"

namespace po = boost::program_options;
using namespace std;

int main(int argc, char * argv[]){
    bool adv_flag = false;
    bool dis_flag = false;

    vector<string> advAndDisRequiredOpts = {
        "roll",
        "strength",
        "dexterity",
        "constitution",
        "intelligence",
        "wisdom",
        "charisma",
        "acrobatics",
        "animal_handling",
        "arcana",
        "athletics",
        "deception",
        "history",
        "insight",
        "intimidation",
        "investigation"
        "medicine",
        "nature",
        "perception",
        "performance",
        "persuasion",
        "religion",
        "sleight_of_hand",
        "stealth",
        "survival"
    };

    vector<string> saveRequiredOpts = {advAndDisRequiredOpts.begin() + 1, advAndDisRequiredOpts.end() - 18};

    // used to check if no options were specified 
    // annoying but thats how it is
    size_t num_options_with_defaults = 4; 

    // setting up the options
    po::options_description rollOpsDesc("Straight Roll Options");
    rollOpsDesc.add_options()
        ("roll", po::value<int>(), "roll a dice with the provided max value")
        ("advantage", po::bool_switch(&adv_flag), "roll with advantage")
        ("disadvantage", po::bool_switch(&dis_flag), "roll with disadvantage")
        ("modifier", po::value<int>()->default_value(0), "add a modifier to the roll")
        ("multiple", po::value<int>()->default_value(1), "set number of times to roll");


    po::options_description infoOpsDesc("Informational Options");
    infoOpsDesc.add_options() 
        ("help", "produce help message")
        ("list", "list names of saved characters.")
        ("create", "start prompt to create a character.")
        ("scores", po::value<string>(), "list ability scores of a given character.")
        ("skills", po::value<string>(), "list skill mods of a given character.")
        ("bio",po::value<string>(), "get a the fluff for a character.")
        ("delete", po::value<string>(), "remove a character from the ledger.");
    
    po::options_description abilityScores("Ability Score Mod Rolls");
    abilityScores.add_options()
        ("strength", po::value<string>(), "roll with a strength mod")
        ("dexterity", po::value<string>(), "roll with a dexterity mod")
        ("intelligence", po::value<string>(), "roll with an intelligence mod")
        ("wisdom", po::value<string>(), "roll with a wisdom mod")
        ("charisma", po::value<string>(), "roll with a charisma mod")
        ("constitution", po::value<string>(), "roll with a constitution mod")
        ("save", "roll a saving throw instead of a ability check");
    
    po::options_description skillMods("Skill Mod Rolls");
    skillMods.add_options()
        ("acrobatics", po::value<string>(), "roll an acrobatics check")
        ("animal_handling", po::value<string>(), "roll an animal handling check")
        ("arcana", po::value<string>(), "roll an arcana check")
        ("athletics", po::value<string>(), "roll an athletics check")
        ("deception", po::value<string>(), "roll a deception check")
        ("history", po::value<string>(), "roll a history check")
        ("insight", po::value<string>(), "roll an insight check")
        ("intimidation", po::value<string>(), "roll an intimidation check")
        ("investigation", po::value<string>(), "roll an investigation check")
        ("medicine", po::value<string>(), "roll a medicine check")
        ("nature", po::value<string>(), "roll a nature check")
        ("perception", po::value<string>(), "roll a perception check")
        ("performance", po::value<string>(), "roll a performance check")
        ("persuasion", po::value<string>(), "roll a persuasion check")
        ("religion", po::value<string>(), "roll a religion check")
        ("sleight_of_hand", po::value<string>(), "roll a sleight of hand check")
        ("stealth", po::value<string>(), "roll a stealth check")
        ("survival", po::value<string>(), "roll a survival check");
    
    po::options_description combatRolls("Combat Rolls");
    combatRolls.add_options()
        ("initiative", po::value<string>(), "roll initiative")
        ("inspiration", "get inspiration")
        ("use_inspiration", "use inspiration")
        ("modify_inspiration", "modify inspiration");

    
    po::options_description characterRollOpsDesc("Character Roll Options");
    characterRollOpsDesc.add(abilityScores).add(skillMods).add(combatRolls);
    
    po::options_description desc;
    desc.add(infoOpsDesc).add(rollOpsDesc).add(characterRollOpsDesc);

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::error const& e){
        cout << e.what() << endl;
    }

    bool advOrDisAllowed = false;
    for (string opt : advAndDisRequiredOpts){
        if (vm.count(opt)){
            advOrDisAllowed = true;
            break;
        }
    }

    bool saveAllowed = false;
    for (string opt : saveRequiredOpts){
        if (vm.count(opt)){
            saveAllowed = true;
            break;
        }
    }

    // parsing the options
    try {
        if (vm.count("help")){
            cout << desc << endl;
        }
        
        if (vm.size() == num_options_with_defaults){
            throw optionsException("You must specify at least one option. See available options below.");
        } 

        if (!advOrDisAllowed){
            if(adv_flag || dis_flag){
                throw optionsException("You must specify a roll option with advantage or disadvantage.");
            }
        }

        if(!saveAllowed){
            if(vm.count("save")){
                throw optionsException("You must specify an ability score option with saving throws.");
            }
        }

        if (vm.count("roll") == 0 && (vm["modifier"].as<int>() != 0 || vm["multiple"].as<int>() != 1)){
            throw optionsException("You must specify the roll option with a modifier or multiple.");
        }

        LedgerAccessor * access = new LedgerAccessor();
        if (vm.count("list")){
            access->listCharacters();
        }
        if (vm.count("create")){
            CharacterCreator * creator = new CharacterCreator();
            creator->createCharacter();
            delete creator;
        } 
        if (vm.count("scores")){
            string name = vm["scores"].as<string>();
            access->getCharacterAbilityScores(name);
        }
        if (vm.count("skills")){
            string name = vm["skills"].as<string>();
            access->getCharacterSkills(name);
        }
        if(vm.count("bio")){
            string name = vm["bio"].as<string>();
            access->getCharacterPhysicalTraits(name);
            access->getCharacterPersonality(name);
            access->getAlignment(name);
            access->getCharacterBackstory(name);
        } 
        if(vm.count("delete")){
            string name = vm["delete"].as<string>();
            access->deleteCharacter(name);
        }
        

        Roller * characterRoller = new Roller();
        if (vm.count("roll")){
            // this is a straight roll using the 
            // options provided and not based on saved 
            // characters
            characterRoller->roll(vm["roll"].as<int>(),
                                  dis_flag, 
                                  adv_flag, 
                                  vm["multiple"].as<int>(), 
                                  vm["modifier"].as<int>());
        }

        for(ability_score ab : ability_score_vector){
            string optionFullName = boost::to_lower_copy(getAbilityScoreName(ab));
            replace(optionFullName.begin(), optionFullName.end(), ' ', '_');
            if (vm.count(optionFullName)){
                if(vm.count("save")){
                    characterRoller->rollSave(ab, vm[optionFullName].as<string>(), adv_flag, dis_flag);
                } else {
                    characterRoller->rollAbilityCheck(ab, vm[optionFullName].as<string>(), adv_flag, dis_flag);
                }
            }
        }

        for(skill s : skill_vector){
            string optionFullName = boost::to_lower_copy(getSkillName(s));
            replace(optionFullName.begin(), optionFullName.end(), ' ', '_');
            if (vm.count(optionFullName)){
                characterRoller->rollSkillCheck(s, vm[optionFullName].as<string>(), adv_flag, dis_flag);
            }
        }

        if (vm.count("initiative")){
            characterRoller->rollInitiative(vm["initiative"].as<string>(), adv_flag, dis_flag);
        }

        if (vm.count("inspiration")){
            string name = vm["inspiration"].as<string>();
            access->getInspiration(name);

        }

        if (vm.count("use_inspiration")){
            string name = vm["use_inspiration"].as<string>();
            access->modifyinspiration(name, -1);
        }

        if (vm.count("add_inspiration")){
            string name = vm["add_inspiration"].as<string>();
            access->modifyinspiration(name, 1);
        }
        delete access;
        delete characterRoller;
        
    } catch (optionsException &e){
        cout << e.what() << endl;
        cout << desc << endl;
    }
      catch(ledger_exception &e){
        cout << e.what() << endl;
    } catch (...){
        cout << desc << endl;
    }

   
    return 0;
}   
