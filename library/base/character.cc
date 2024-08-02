#include "character.h"

void Character::checkGivenIndex(size_t index, size_t max_array_value, string array_name)
{
    if (index >= max_array_value){
        throw CharacterException("Received out of range index when accessing " + array_name);
    }
}

Character::Character()
{
    // for safety provide initial
    // values for all character object
    // attributes

    _name = "";
    _short_name = "";
    _physical_traits.age = 0;
    _physical_traits.height = 0;
    _physical_traits.weight = 0;
    _physical_traits.eye_color = "";
    _physical_traits.hair_color = "";
    _physical_traits.skin_tone = "";
    _personality_traits.bonds = "";
    _personality_traits.flaws = "";
    _personality_traits.ideals = "";
    _personality_traits.alignment = "";
    _backstory = "";

    for (size_t i = 0; i < NUM_ABILITY_SCORES; i++){
        _ability_scores[i] = 0;
    }
    
    for (size_t i = 0; i < NUM_SKILLS; i++){
        _proficient_skills[i] = false;
        _expert_skills[i] = false;
    }

    _level = 1;
}

Character::~Character()
{
}

physical_traits Character::getPhysicalTraits() const
{
    return _physical_traits;
}

void Character::setPhysicalTraits(physical_traits physical_traits)
{
    _physical_traits = physical_traits;
}

personality_traits Character::getPersonalityTraits() const
{
    return _personality_traits;
}

void Character::setPersonalityTraits(personality_traits personality_traits){
    _personality_traits = personality_traits;
}

string Character::getName() const
{
    return _name;
}

void Character::setName(string name)
{
    _name = name;
}

string Character::getShortName() const
{
    return _short_name;
}

void Character::setShortName(string short_name)
{
    _short_name = short_name;
}

void Character::setAbilityScore(size_t index, int32_t value)
{
    checkGivenIndex(index, NUM_ABILITY_SCORES, "the ability scores.");
    _ability_scores[index] = value;
}

int32_t Character::getAbilityScore(size_t index)
{
    checkGivenIndex(index, NUM_ABILITY_SCORES, "the ability scores.");
    return _ability_scores[index];
}

void Character::setBackstory(string backstory)
{
    _backstory = backstory;
}

string Character::getBackstory()
{
    return _backstory;
}

void Character::setLevel(int level)
{
    _level = level;
}

int Character::getLevel()
{
    return _level;
}

int Character::getProficiencyBonus()
{
    AltRangeConverter *rc = new AltRangeConverter(0, 4);
    int bonus = rc->convertVal(_level) + 1;
    delete rc;
    return bonus;
    
}

void Character::setProficiency(size_t index, bool val)
{
    checkGivenIndex(index, NUM_SKILLS, "the proficiencies.");
    _proficient_skills[index] = val;
}

bool Character::isProficient(size_t index){
    checkGivenIndex(index, NUM_SKILLS, "the proficiencies.");
    return _proficient_skills[index];
}

void Character::setExpertise(size_t index, bool val)
{
    checkGivenIndex(index, NUM_SKILLS, "the expertise.");
    _expert_skills[index] = val;
}

bool Character::isExpert(size_t index)
{
    checkGivenIndex(index, NUM_SKILLS, "the expertise.");
    return _expert_skills[index];
}

int Character::getAbilityMod(size_t index)
{
    AltRangeConverter *rc = new AltRangeConverter(10, 2);
    int mod = rc->convertVal(getAbilityScore(index));
    delete rc;

    return mod;
}

int Character::getSkillMod(size_t index){
    int mod = getAbilityMod(index);
    if (isProficient(index)) mod += getProficiencyBonus();
    if (isExpert(index)) mod += getProficiencyBonus();
    return mod;
}
