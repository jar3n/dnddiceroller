#include "ledger.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <limits>
#include <unistd.h>


ledger::ledger(){
    // put the ledger in the same directory as the dice roller executable
    // this is linux only 
    // need to add windows and other OS ways later
    char executableDir[PATH_MAX];
    size_t path_length = readlink("/proc/self/exe", executableDir, sizeof(executableDir));
    string exeDirStr(executableDir, path_length);
    boost::filesystem::path exe_path(exeDirStr);

    _full_ledger_path = exe_path.parent_path().string() + "/character_ledger";

    fstream ledger_in_stream(_full_ledger_path, ios::in | ios::binary);
    if (!ledger_in_stream){
        // todo figure out what goes here since the character creator is not in this class
        cout << "There is no ledger. Loading the Character creator to make one.\n";
    } else if (!_ledger_data.ParseFromIstream(&ledger_in_stream)){
        throw ledger_exception("Failed to parse the characters ledger.");
    } else if (_ledger_data.characters_size() == 0){
        // todo figure out what goes here since the character creator is not in this class
        cout << "There are no characters in the character ledger. Loading the Charater creator to make one.\n";
    } 
}

ledger::~ledger(){
    if (_haveUpdateToLedger){
        fstream ledger_out_stream(_full_ledger_path, ios::out | ios::binary | ios::trunc);
        if (!_ledger_data.SerializeToOstream(&ledger_out_stream)){
            cout << "Failed to write to the character ledger. Check it exists in " << _full_ledger_path << endl;
        }
    }

}

void ledger::getCharacterAbilityScores(string name){
    dnd::character c;
    getCharacter(name, c);
    cout << c.name() << "'s Ability Scores:\n";
    for(size_t i = 0; i < NUM_ABILITY_SCORES; i++){
        cout << "  " << string(ABILITY_NAMES[i]) << ": " << c.ability_scores(i) << "\n";
    }
}

void ledger::getCharacterPersonality(string name){
    dnd::character c;
    getCharacter(name, c);
    dnd::personality_traits traits = c.personality();
    cout << c.name() << "'s Personality, Ideals, Bonds, and Flaws:\n";
    cout << " Personality Trait: " << traits.personality_trait() << "\n";
    cout << " Ideal: " << traits.ideals() << "\n";
    cout << " Bond: " << traits.bonds() << "\n";
    cout << " Flaw: " << traits.flaws() << "\n";
}

void ledger::getAlignment(string name){
    dnd::character c;
    getCharacter(name, c);
    cout << c.name() << "'s Alignment is " << c.personality().alignment() << ".\n";
}

void ledger::getCharacterBackstory(string name){
    dnd::character c;
    getCharacter(name, c);
    cout << c.name() << "'s Backstory:\n";
    cout << "   " << c.backstory() << "\n";
}

void ledger::getCharacterPhysicalTraits(string name){
    dnd::character c;
    getCharacter(name, c);
    dnd::physical_traits traits = c.presence();
    cout << c.name() << "'s Physical Features:\n";
    cout << " Age: " << traits.age() << "\n";
    cout << " Height: " << traits.height() << "\n";
    cout << " Weight: " << traits.weight() << "\n";
    cout << " Skin Tone: " << traits.skin_tone() << "\n";
    cout << " Hair Color: " << traits.hair_color() << "\n";
    cout << " Eye Color: " << traits.eye_color() << "\n";
}

void ledger::getCharacter(string name, dnd::character &character){
    name = boost::algorithm::to_lower_copy(name);
    bool found_no_character = true;
    for(int i = 0; i < _ledger_data.characters_size(); i++){
        if (_ledger_data.characters(i).short_name() == name){
            character = _ledger_data.characters(i);
            found_no_character = false;
            break;
        }
    }
    if (found_no_character){
        throw ledger_exception("Found no character with the name: " + name +"\n"); 
    }
}

void ledger::listCharacters(){
    if (_ledger_data.characters_size() == 0){
        throw ledger_exception("There are no characters in the ledger. Launch the Character Creator to make one.");
    } else if (_createdCharacterInConstructor){
        return;
    } else {
        cout << "Available Characters:" << endl;
            for (int i = 0; i < _ledger_data.characters_size(); i++){
                cout << _ledger_data.characters(i).name() << " (" << _ledger_data.characters(i).short_name() << ")" << endl;
            }
    }
}

ledger_exception::ledger_exception(string msg) : _msg(msg){}

string ledger_exception::what(){
    return "Encountered the following issue with the ledger: " + _msg;
}

