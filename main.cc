#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>

#include "library/base/include/dice.h"
#include "library/interface/creator.h"
#include "library/interface/accessor.h"

namespace po = boost::program_options;
using namespace std;

class optionsException : public exception{
    public:
        optionsException(string msg) :
        _msg(msg){}

        string what(){
            return "options error: " + _msg;
        }

    private:
        string _msg;

};

string applyMod(int roll, int mod){
    stringstream ss;
    int final_roll = roll + mod;
    if (mod > 0){
        ss << roll << " + " << mod << " => " << final_roll;
    } else if (mod < 0){
        ss << roll << " - " << mod - 2*mod << " => " << final_roll;
    } else {
        ss << roll;
    }
    return ss.str();
}

int main(int argc, char * argv[]){
    // setting up the options
    po::options_description desc("Options");
    bool adv_flag = false;
    bool dis_flag = false;

    // used to check if no options were specified 
    // annoying but thats how it is
    size_t num_options_with_defaults = 3; 

    desc.add_options() 
        ("help,h", "produce help message")
        ("roll,r", po::value<int>(), "roll a dice with the provided max value")
        ("advantage,A", po::bool_switch(&adv_flag), "roll with advantage")
        ("disadvantage,D", po::bool_switch(&dis_flag), "roll with disadvantage")
        ("modifier,m", po::value<int>()->default_value(0), "add a modifier to the roll")
        ("list_characters,l", "list names of saved characters.")
        ("create_character,c", "start prompt to create a character.")
        ("ability_scores,a", po::value<string>(), "list ability scores of a given character.")
        ("character_bio,b",po::value<string>(), "get a the fluff for a character.")
        ("delete_character,d", po::value<string>(), "remove a character from the ledger.");
    
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::error const& e){
        cout << e.what() << endl;
    }

    // parsing the options
    try {
        if (vm.count("help")){
            cout << desc << endl;
        } else if (vm.size() == num_options_with_defaults){
            cout << "You must specify at least one option. See available options below." << endl;
            cout << desc << endl;
        } else if (vm.count("roll")){
            Dice *d = new Dice();
            if (adv_flag && dis_flag){
                throw optionsException("cannot use both --adv and --dis options must pick one.");
            }
            int mod = vm.count("modifier") ? vm["modifier"].as<int>() : 0;
            int diceMaxVal = vm["roll"].as<int>();
            cout << "Rolled a d" << diceMaxVal;
            if (adv_flag || dis_flag){
                dice_res res_roll = d->doubleRoll(diceMaxVal);
                string rolls = to_string(res_roll.roll_1) + " " + to_string(res_roll.roll_2);
                if (adv_flag){
                    cout << " at advantage: " << rolls << " => " << applyMod(res_roll.max_roll, mod) << endl;
                } else if (dis_flag){
                    cout << " at disadvantage: " << rolls << " => " << applyMod(res_roll.min_roll, mod) << endl;
                }
            } else {
                int roll = d->rolldX(diceMaxVal);
                cout << ": " << applyMod(roll, mod) << endl;
            }
            delete d;
        } else if (vm.count("list_characters") ||
                   vm.count("create_character") || 
                   vm.count("ability_scores") ||
                   vm.count("character_bio") ||
                   vm.count("delete_character")){
            LedgerAccessor * access = new LedgerAccessor();
            if (vm.count("list_characters")){
                access->listCharacters();
            } else if (vm.count("create_character")){
                CharacterCreator * creator = new CharacterCreator();
                creator->createCharacter();
                delete creator;
            } else if (vm.count("ability_scores")){
                string name = vm["ability_scores"].as<string>();
                access->getCharacterAbilityScores(name);
            } else if(vm.count("character_bio")){
                string name = vm["character_bio"].as<string>();
                access->getCharacterPhysicalTraits(name);
                access->getCharacterPersonality(name);
                access->getAlignment(name);
                access->getCharacterBackstory(name);
            } else if(vm.count("delete_character")){
                string name = vm["delete_character"].as<string>();
                access->deleteCharacter(name);
            }
            
        } 
    } catch (optionsException &e){
        cout << e.what() << endl;
    }
      catch(ledger_exception &e){
        cout << e.what() << endl;
    }

   
    return 0;
}   
