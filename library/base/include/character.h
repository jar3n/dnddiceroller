#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <cstdint>
#include <string>

#include "range.h"

using namespace std;



#define ABILITY_NAMES ((const char *[]){"Strength", \
                                        "Dexterity", \
                                        "Constitution", \
                                        "Intelligence", \
                                        "Wisdom", \
                                        "Charisma"})
#define MIN_LEVEL 1
#define MAX_LEVEL 20
#define MIN_PROFICIENCY_BONUS 2
#define MAX_PROFICIENCY_BONUS 6
#define MIN_ABILITY_SCORE_VAL 1
#define MAX_ABILITY_SCORE_VAL 20
#define MIN_ABILITY_SCORE_MOD -5
#define MAX_ABILITY_SCORE_MOD 10
#define NUM_ABILITY_SCORES 6
#define NUM_SKILLS 18

enum ability_score {
    STRENGTH = 0,
    DEXTERITY = 1,
    CONSTITUTION = 2,
    INTELLIGENCE = 3,
    WISDOM = 4,
    CHARISMA = 5
};

enum skill {
    ACROBATICS = 0,
    ANIMAL_HANDLING = 1,
    ATHLETICS = 2,
    ARCANA = 3,
    DECEPTION = 4,
    HISTORY = 5,
    INSIGHT = 6,
    INTIMIDATION = 7,
    INVESTIGATION = 8,
    MEDICINE = 9,
    NATURE = 10,
    PERCEPTION = 11,
    PERFORMANCE = 12,
    PERSUASION = 13,
    RELIGION = 14,
    SLEIGHT_OF_HAND = 15,
    STEALTH = 16,
    SURVIVAL = 17
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

class CharacterException : public std::exception {
private:
    std::string _message;

public:
    CharacterException(const std::string& message) : _message(message) {}

    const char* what() const throw() {
        return _message.c_str();
    }
};

class Character {
    private:
        physical_traits _physical_traits;
        personality_traits _personality_traits;

        // general information
        string _name, _short_name;

        string _backstory;

        // functional information
        int32_t _ability_scores[NUM_ABILITY_SCORES];
        bool _proficient_skills[18];
        bool _expert_skills[18];
        int _level;

        void checkGivenIndex(size_t index, size_t max_array_value, string array_name);

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

        void setLevel(int level);
        int getLevel();

        int getProficiencyBonus();

        void setProficiency(size_t index, bool val);
        bool isProficient(size_t index);

        void setExpertise(size_t index, bool val);
        bool isExpert(size_t index);

        int getAbilityMod(size_t index);
        int getSkillMod(size_t index);

};

#endif
