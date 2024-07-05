#include "library/base/dice.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <exception>
#include <string>

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

int main(int argc, char * argv[]){
    Dice *d = new Dice();

    po::options_description desc("Options");
    bool adv_flag = false;
    bool dis_flag = false;

    desc.add_options() 
        ("help", "produce help message")
        ("roll,r", po::value<int>()->default_value(20), "roll a dice with provided max value")
        ("advantage,adv", po::bool_switch(&adv_flag), "roll with advantage")
        ("disadvantage,dis", po::bool_switch(&dis_flag), "roll with disadvantage")
        ("modifier,m", po::value<int>()->default_value(0), "add a modifier to the roll");
    
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::error const& e){
        cout << e.what() << endl;
    }

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
        }
    } catch (optionsException &e){
        cout << e.what() << endl;
    }



    return 0;
}   
