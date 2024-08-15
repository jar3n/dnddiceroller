#include "roller.h"
#include <sstream>

using namespace std;

Roller::Roller()
{
}

Roller::~Roller(){}

void Roller::rollAbilityCheck(ability_score ab, string name)
{
    Character c;
    Dice d;
    LedgerAccessor::getCharacter(name, c);
    int roll = d.rolld20();
    int modifier = c.getAbilityMod(ab);
    int total = roll + modifier;

    stringstream result;
    result << c.getName() << "'s " << c.getAbilityScoreName(ab) << " check result: ";
    result << roll << " + " << modifier << " => " << total;
    
    cout << result.str() << endl;

}

void Roller::rollStrength(string name)
{
    rollAbilityCheck(STRENGTH, name);
}

void Roller::rollDexterity(string name)
{
    rollAbilityCheck(DEXTERITY, name);
}

void Roller::rollIntelligence(string name)
{
    rollAbilityCheck(INTELLIGENCE, name);
}

void Roller::rollWisdom(string name)
{
    rollAbilityCheck(WISDOM, name);
}

void Roller::rollCharisma(string name)
{
    rollAbilityCheck(CHARISMA, name);
}

void Roller::rollConstitution(string name)
{
    rollAbilityCheck(CONSTITUTION, name);
}
