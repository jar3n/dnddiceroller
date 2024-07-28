#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>

#include "library/base/include/dice.h"
#include "library/serial/ledger.h"
#include "library/interface/creator.h"

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

    desc.add_options() 
        ("help,h", "produce help message")
        ("roll,r", po::value<int>(), "roll a dice with the provided max value")
        ("advantage,A", po::bool_switch(&adv_flag), "roll with advantage")
        ("disadvantage,D", po::bool_switch(&dis_flag), "roll with disadvantage")
        ("modifier,m", po::value<int>()->default_value(0), "add a modifier to the roll")
        ("list_characters,l", "list names of saved characters.")
        ("create_character,c", "start prompt to create a character.")
        ("ability_scores,a", po::value<string>(), "list ability scores of a given character.")
        ("character_bio,b",po::value<string>(), "get a the fluff for a character.");
    
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
                   vm.count("character_bio")){
            ledger * character_ledger = new ledger();
            if (vm.count("list_characters")){
                character_ledger->listCharacters();
            } else if (vm.count("create_character")){
                CharacterCreator * creator = new CharacterCreator();
                creator->createCharacter();
                delete creator;
            } else if (vm.count("ability_scores")){
                string name = vm["ability_scores"].as<string>();
                character_ledger->getCharacterAbilityScores(name);
            } else if(vm.count("character_bio")){
                string name = vm["character_bio"].as<string>();
                character_ledger->getCharacterPhysicalTraits(name);
                character_ledger->getCharacterPersonality(name);
                character_ledger->getAlignment(name);
                character_ledger->getCharacterBackstory(name);
            }
            delete character_ledger;
        } 
    } catch (optionsException &e){
        cout << e.what() << endl;
    }
      catch(ledger_exception &e){
        cout << e.what() << endl;
    }

   
    return 0;
}   
