#include "library/base/dice.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <exception>

namespace po = boost::program_options;
using namespace std;


int main(int argc, char * argv[]){
    Dice *d = new Dice();

    
    try {
        po::options_description desc("Options");

        desc.add_options() 
            ("help", "produce help message")
            ("roll", po::value<int>()->default_value(20), "roll a dice with provided max value");
        
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("help")){
            cout << desc << endl;
        } else if (vm.count("roll")){
            int diceMaxVal = vm["roll"].as<int>();
            cout << "Rolled a d" << diceMaxVal << " : " << d->rolldX(diceMaxVal) << endl;
        }
    }catch (exception &e){
        cout << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}   