#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <cstdint>
#include <string>
using namespace std;

#define NUM_ABILITY_SCORES 6

#define ABILITY_NAMES ((const char *[]){"Strength", \
                                        "Dexterity", \
                                        "Constitution", \
                                        "Intelligence", \
                                        "Wisdom", \
                                        "Charisma"})

enum ability_score {
    STRENGTH = 0,
    DEXTERITY = 1,
    CONSTITUTION = 2,
    INTELLIGENCE = 3,
    WISDOM = 4,
    CHARISMA = 5
};

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
        int32_t _ability_scores[NUM_ABILITY_SCORES] = {10};

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

        void setAbilityScore(size_t index, int32_t value);
        int32_t getAbilityScore(size_t index);

        void setBackstory(string backstory);
        string getBackstory();

};



#endif
