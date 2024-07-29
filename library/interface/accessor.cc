#include "accessor.h"

void LedgerAccessor::getCharacter(string name, Character &c)
{
    _characterLedger->getCharacter(name, c);
}

void LedgerAccessor::getCharacterAbilityScores(string name)
{
    Character c;
    getCharacter(name, c);
    cout << c.getName() << "'s Ability Scores:\n";
    for(size_t i = 0; i < NUM_ABILITY_SCORES; i++){
        cout << "  " << string(ABILITY_NAMES[i]) << ": " << c.getAbilityScore(i) << "\n";
    }
}

void LedgerAccessor::getCharacterPersonality(string name){
    Character c;
    getCharacter(name, c);
    personality_traits traits = c.getPersonalityTraits();
    cout << c.getName() << "'s Personality, Ideals, Bonds, and Flaws:\n";
    cout << " Personality Trait: " << traits.personality_trait << "\n";
    cout << " Ideal: " << traits.ideals << "\n";
    cout << " Bond: " << traits.bonds << "\n";
    cout << " Flaw: " << traits.flaws << "\n";
}

void LedgerAccessor::getAlignment(string name){
    Character c;
    getCharacter(name, c);
    cout << c.getName() << "'s Alignment is " << c.getPersonalityTraits().alignment << ".\n";
}

void LedgerAccessor::getCharacterBackstory(string name){
    Character c;
    getCharacter(name, c);
    cout << c.getName() << "'s Backstory:\n";
    cout << "   " << c.getBackstory() << "\n";
}

void LedgerAccessor::getCharacterPhysicalTraits(string name){
    Character c;
    getCharacter(name, c);
    physical_traits traits = c.getPhysicalTraits();
    cout << c.getName() << "'s Physical Features:\n";
    cout << " Age: " << traits.age << "\n";
    cout << " Height: " << traits.height << "\n";
    cout << " Weight: " << traits.weight << "\n";
    cout << " Skin Tone: " << traits.skin_tone << "\n";
    cout << " Hair Color: " << traits.hair_color << "\n";
    cout << " Eye Color: " << traits.eye_color << "\n";
}


void LedgerAccessor::listCharacters(){
    for (size_t i = 0; i < _characterLedger->size(); i++){
        Character c;
        _characterLedger->getCharacter(i, c);
        cout << c.getName() << " (" << c.getShortName() << ")" << endl;
    }
}

LedgerAccessor::LedgerAccessor()
{
    _characterLedger = new ledger();
}

LedgerAccessor::~LedgerAccessor()
{
    delete _characterLedger;
}
