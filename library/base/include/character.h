#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <cstdint>
#include <string>
using namespace std;

struct physical_traits {
    int32_t age;
    int32_t height;
    int32_t weight;
    string skin_tone;
    string hair_color;
    string eye_color;
};

struct personality_traits {
    string personality_trait; 
    string ideals; 
    string bonds; 
    string flaws; 
    string alignment;
};

class Character {
    private:
        physical_traits _physical_traits;
        personality_traits _personality_traits;

        // general information
        string _name, _short_name;

        string _backstory;

        // functional information
        int32_t _ability_scores[6] = {10};

    public:
        Character();
        ~Character();

        physical_traits getPhysicalTraits() const;
        void setPhysicalTraits(physical_traits physical_traits);

        personality_traits getPersonalityTraits() const;
        void setPersonalityTraits(personality_traits personality_traits);

        string getName() const;
        void setName(string name);

        string getShortName() const;
        void setShortName(string short_name);

};



#endif
