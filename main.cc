#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>

#include "build/characterbook.pb.h"
#include "library/base/dice.h"

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
    if (mod > 0){
        ss << roll << " + " << mod << " => " << roll + mod;
    } else if (mod < 0){
        ss << roll << " - " << mod << " => " << roll - mod;
    } else {
        ss << roll;
    }
    return ss.str();
}

bool listCharacters(dnd::character_ledger & ledger){
    cout << "Available Characters:" << endl;
    for (int i = 0; i < ledger.characters_size(); i++){
        cout << ledger.characters(i).name() << endl;
    }
    return false; // does not write to ledger
}

bool createCharacter(dnd::character_ledger & ledger){
    string name;
    cout << "Welcome to the Character Creator:" << endl;   
    cout << "Enter a Name for your Character: ";
    getline(cin, name);
    if (name.empty()){
        cout << "Character must have a name." << endl;
    } else {
        cout << "Adding a character named: " << name << endl;
        dnd::character * new_character = ledger.add_characters();
        new_character->set_name(name);
    }

    while (true){
        string resp;
        cout << "Would you like to add another character? (y or n) ";
        getline(cin,resp);
        if (resp.compare("n") == 0){
            cout << "Exiting Character Creator." << endl;
            break;
        } else if (resp.compare("y") == 0){
            cout << "Enter a Name for your Character: ";
            getline(cin, name);
            if (name.empty()){
                cout << "Character must have a name." << endl;
            } else {
                cout << "Adding a character named: " << name << endl;
                dnd::character * new_character = ledger.add_characters();
                new_character->set_name(name);
            }
        } else {
            cout << "Recieved invalid response, Exiting Character Creator." << endl;
        }
    }
    return true; //wrote to ledger
}

void accessCharacterLedger(bool (*ledgerOperation)(dnd::character_ledger&)){
    char resolved_path[PATH_MAX];
    realpath("./build/character_ledger", resolved_path);
    static string full_ledger_path(resolved_path);

    dnd::character_ledger ledger;
    fstream input(full_ledger_path, ios::in | ios::binary);
    bool wroteToLedger = false;
    if (!input){
        cout << "You have not created a Character ledger, Loading Character Creator to create one." << endl;
        wroteToLedger = createCharacter(ledger);
    } else if (!ledger.ParseFromIstream(&input)){
        throw optionsException("Failed to parse the characters ledger.");
    } else if (ledger.characters_size() == 0){
        cout << "There are no characters in the character ledger. Loading Character Creator to create one." << endl;
        wroteToLedger = createCharacter(ledger);
    } else {
        wroteToLedger = ledgerOperation(ledger);
    }

    if (wroteToLedger){
        fstream output(full_ledger_path, ios::out | ios::binary | ios::trunc);
        if (!ledger.SerializeToOstream(&output)){
            cout << "Failed to write to ledger. Check it exists in " << full_ledger_path << endl;
        }
    }
}

int main(int argc, char * argv[]){
    // initializing some variables
    Dice *d = new Dice();

    // setting up the options
    po::options_description desc("Options");
    bool adv_flag = false;
    bool dis_flag = false;

    desc.add_options() 
        ("help,h", "produce help message")
        ("roll,r", po::value<int>(), "roll a dice with the provided max value")
        ("advantage,adv", po::bool_switch(&adv_flag), "roll with advantage")
        ("disadvantage,dis", po::bool_switch(&dis_flag), "roll with disadvantage")
        ("modifier,m", po::value<int>()->default_value(0), "add a modifier to the roll")
        ("list_characters,lc", "list names of saved characters.")
        ("create_character,cc", "start prompt to create a character.");
    
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
        } else if (vm.count("list_characters")){
            accessCharacterLedger(listCharacters);
        } else if (vm.count("create_character")){
            accessCharacterLedger(createCharacter);
        }
    } catch (optionsException &e){
        cout << e.what() << endl;
    }

    return 0;
}   
