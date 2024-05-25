#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// my stuff
#include "library/base/dice.h"

using namespace std;
using namespace boost::property_tree;
using namespace dnd;

int main(int argc, char * argv[]){
    // TODO
    // have a main while loop 
    // with a way to safely get out
    // have a function that prompts for a character file
    // have a function that generates a random number
    srand(time(nullptr));
    int rand_val = rand();
    int d20_rand = (rand() % 20) + 1;

    cout << "HELLO WORLD\n";
    cout << "This is a random number: " << rand_val << "\n";
    cout << "This is a random d20 roll: " << d20_rand << "\n";

    Dice * mydice = new Dice();

    cout << "This is a d4 from my dice class: " << mydice->rolld4() << "\n";
    cout << "This is a d6 from my dice class: " << mydice->rolld6() << "\n";
    cout << "This is a d8 from my dice class: " << mydice->rolld8() << "\n";
    cout << "This is a d10 from my dice class: " << mydice->rolld10() << "\n";
    cout << "This is a d12 from my dice class: " << mydice->rolld12() << "\n";
    cout << "This is a d20 from my dice class: " << mydice->rolld20() << "\n";
    cout << "This is a d100 from my dice class: " << mydice->rolld100() << "\n";

    string charfile("/home/jenglander/dndcode/testfiles/chartemp.json");
    cout << "Reading in the following character file: " << charfile << "\n";

    ptree root;
    read_json(charfile, root);
    string charName = root.get<string>("character.base-info.name");
    cout << "The character's name is " << charName << "\n";

    return 0;
}   