#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>


using namespace std;
using namespace boost::property_tree;

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
    
    string charfile("/home/jenglander/dndcode/chartemp.json");
    cout << "Reading in the following character file: " << charfile << "\n";

    ptree root;
    read_json(charfile, root);
    string charName = root.get<string>("character.base-info.name");
    cout << "The character's name is " << charName << "\n";


    return 0;
}   