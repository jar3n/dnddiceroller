#ifndef _CHARACTER_BACKGROUND_H_
#define _CHARACTER_BACKGROUND_H_

#include <string>
#include <vector>

using namespace std;

class Background {
    public:
    Background();
    

    private:
    // proficiencies use the same int 
    // as defined in character class
    int proficiencies_gained;
    // some backgrounds have options 
    // for the tools you get
    vector<string> tools;
    vector<string> tool_options;

    // backgrounds come with some gold
    int gold;

};

#endif