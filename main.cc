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

vector<string> getOptionNames(po::options_description od){
    vector<string> names;
    for (std::vector<boost::shared_ptr<boost::program_options::option_description>>::const_iterator 
        it = od.options().begin(); it != od.options().end(); it++){
        names.push_back(it->operator->()->canonical_display_name());
    }

    return names;
}

int main(int argc, char * argv[]){
    bool adv_flag = false;
    bool dis_flag = false;

    // used to check if no options were specified 
    // annoying but thats how it is
    size_t num_options_with_defaults = 3; 

    // setting up the options
    po::options_description rollOpsDesc("Straight Roll Options");
    rollOpsDesc.add_options()
        ("roll,r", po::value<int>(), "roll a dice with the provided max value")
        ("advantage,A", po::bool_switch(&adv_flag), "roll with advantage")
        ("disadvantage,v", po::bool_switch(&dis_flag), "roll with disadvantage")
        ("modifier,m", po::value<int>()->default_value(0), "add a modifier to the roll");


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

    vector<string> parsedKeys;
    for (po::variables_map::iterator it = vm.begin(); it != vm.end(); it++){
        parsedKeys.push_back(it->first);
    }

    vector<string> rollOptionNames = getOptionNames(characterRollOpsDesc);
    vector<string> infoOptionNames = getOptionNames(infoOpsDesc);

    // parsing the options
    try {
        vector<string> infoIntersection;
        vector<string> rollIntersection;
        set_intersection(infoOptionNames.begin(),
                         infoOptionNames.end(),
                         parsedKeys.begin(),
                         parsedKeys.end(),
                         back_inserter(infoIntersection));
        set_intersection(rollOptionNames.begin(),
                         rollOptionNames.end(),
                         parsedKeys.begin(),
                         parsedKeys.end(),
        back_inserter(rollIntersection));

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
        } else if ((!infoIntersection.empty()) || (!rollIntersection.empty())){
            LedgerAccessor * access = new LedgerAccessor();
            if (vm.count("list")){
                access->listCharacters();
            } else if (vm.count("create")){
                CharacterCreator * creator = new CharacterCreator();
                creator->createCharacter();
                delete creator;
            } else if (vm.count("scores")){
                string name = vm["scores"].as<string>();
                access->getCharacterAbilityScores(name);
            } else if(vm.count("bio")){
                string name = vm["bio"].as<string>();
                access->getCharacterPhysicalTraits(name);
                access->getCharacterPersonality(name);
                access->getAlignment(name);
                access->getCharacterBackstory(name);
            } else if(vm.count("delete")){
                string name = vm["delete"].as<string>();
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
