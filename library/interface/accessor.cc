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
    for(ability_score i : ability_score_vector){
        string modSignStr = c.getAbilityMod(i) >= 0 ? "+" : "-";
        string modSaveSignStr = c.getSaveMod(i) >= 0 ? "+" : + "-";
        cout << "  " << getAbilityScoreName(i) << ": " << c.getAbilityScore(i);
        cout << " (mod: " << modSignStr << " " << abs(c.getAbilityMod(i)) << ", save mod: ";
        cout << modSaveSignStr << " " << abs(c.getSaveMod(i)) << ")" << "\n";
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

void LedgerAccessor::getCharacterSkills(string name){
    Character c;
    getCharacter(name, c);
    cout << c.getName() << "'s Skills:\n";
    for(skill i : skill_vector){
        string modSignStr = c.getSkillMod(i) >= 0 ? "+" : "-";
        string profTagStr = c.isSkillProficient(i) ? (c.isSkillExpert(i) ? "(proficient)" : "(expert)") : "";
        cout << "  " << getSkillName(i) << ": " << modSignStr << " " << abs(c.getSkillMod(i)) << " " << profTagStr << "\n";
    }
}

void LedgerAccessor::getAlignment(string name){
    Character c;
    getCharacter(name, c);
    cout << c.getName() << "'s Alignment is " << c.getPersonalityTraits().alignment << ".\n";
}

void LedgerAccessor::getCharacterClass(string name)
{
    Character c;
    getCharacter(name, c);
    cout << c.getName() << "'s Class is " << c.getClassStr() << ".\n";
}

void LedgerAccessor::getCharacterBackstory(string name){
    Character c;
    getCharacter(name, c);
    cout << c.getName() << "'s Backstory:\n  " << c.getBackstory() << endl;
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
    vector<Character> characters = _characterLedger->getAllCharacters();
    if (characters.size() == 0){
        cout << "No characters in the ledger. Create one with the Character creator. \n";
        return;
    }
    for (size_t i = 0; i < characters.size(); i++){
        cout << characters[i].getName() << " (command name: " << characters[i].getShortName() << ", level: " << characters[i].getLevel() << ")" << endl;
    }
}

void LedgerAccessor::deleteCharacter(string name)
{
    _characterLedger->deleteCharacter(name);
}

LedgerAccessor::LedgerAccessor()
{
    _characterLedger = new ledger();
}

LedgerAccessor::~LedgerAccessor()
{
    delete _characterLedger;
}
