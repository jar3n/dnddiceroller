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


int main(int argc, char * argv[]){
    Dice *d = new Dice();

    
        po::options_description desc("Options");

        desc.add_options() 
            ("help", "produce help message")
            ("roll", po::value<int>()->default_value(20), "roll a dice with provided max value")
            ("adv", po::value<bool>()->default_value(false), "roll with advantage")
            ("dis", po::value<bool>()->default_value(false), "roll with disadvantage");
        
        
        po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
        } catch (po::error const& e){
            cout << e.what() << endl;
        }

        if (vm.count("help")){
            cout << desc << endl;
        } else if (vm.count("roll")){
            int diceMaxVal = vm["roll"].as<int>();
            bool advantage = vm["advantage"].as<bool>();
            bool disadvantage = vm["disadvantage"].as<bool>();
            if (advantage && disadvantage){
                throw optionsException("cannot use both --adv and --dis options must pick one.");
            }
            cout << "Rolled a d" << diceMaxVal << " : " << d->rolldX(diceMaxVal) << endl;
        }


    return 0;
}   
