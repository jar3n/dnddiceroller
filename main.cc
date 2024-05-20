#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    


    return 0;
}   