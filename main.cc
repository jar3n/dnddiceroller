#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>

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
        "charisma"
    };

    // used to check if no options were specified 
    // annoying but thats how it is
    size_t num_options_with_defaults = 3; 

    // setting up the options
    po::options_description rollOpsDesc("Straight Roll Options");
    rollOpsDesc.add_options()
        ("roll,r", po::value<int>(), "roll a dice with the provided max value")
        ("advantage,A", po::bool_switch(&adv_flag), "roll with advantage")
        ("disadvantage,D", po::bool_switch(&dis_flag), "roll with disadvantage")
        ("modifier,m", po::value<int>()->default_value(0), "add a modifier to the roll")
        ("multiple,M", po::value<int>()->default_value(1), "set number of times to roll");


    po::options_description infoOpsDesc("Informational Options");
    infoOpsDesc.add_options() 
        ("help", "produce help message")
        ("list", "list names of saved characters.")
        ("create", "start prompt to create a character.")
        ("scores", po::value<string>(), "list ability scores of a given character.")
        ("bio",po::value<string>(), "get a the fluff for a character.")
        ("delete", po::value<string>(), "remove a character from the ledger.");
    
    po::options_description characterRollOpsDesc("Character Roll Options");
    characterRollOpsDesc.add_options()
        ("strength,s", po::value<string>(), "roll with a strength mod")
        ("dexterity,d", po::value<string>(), "roll with a dexterity mod")
        ("intelligence,i", po::value<string>(), "roll with an intelligence mod")
        ("wisdom,w", po::value<string>(), "roll with a wisdom mod")
        ("charisma,c", po::value<string>(), "roll with a charisma mod")
        ("constitution,C", po::value<string>(), "roll with a constitution mod");
    
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
        delete access;

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
        
        if(vm.count("strength")){
            characterRoller->rollStrength(vm["strength"].as<string>(), adv_flag, dis_flag);
        }
        if(vm.count("dexterity")){
            characterRoller->rollDexterity(vm["dexterity"].as<string>(), adv_flag, dis_flag);
        }
        if(vm.count("constitution")){
            characterRoller->rollConstitution(vm["constitution"].as<string>(), adv_flag, dis_flag);
        }
        if(vm.count("intelligence")){
            characterRoller->rollIntelligence(vm["intelligence"].as<string>(), adv_flag, dis_flag);
        }
        if(vm.count("wisdom")){
            characterRoller->rollWisdom(vm["wisdom"].as<string>(), adv_flag, dis_flag);
        }
        if(vm.count("charisma")){
            characterRoller->rollCharisma(vm["charisma"].as<string>(), adv_flag, dis_flag);
        }
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
