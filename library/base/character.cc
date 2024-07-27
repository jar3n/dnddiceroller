#include "character.h"

Character::Character()
{
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
