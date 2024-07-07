#include "ledger.h"
#include <boost/algorithm/string.hpp>

ledger::ledger(string ledger_path)
{
    char resolved_path[PATH_MAX];
    realpath(ledger_path.c_str(), resolved_path);
    _full_ledger_path = string(resolved_path);

    fstream ledger_in_stream(_full_ledger_path, ios::in | ios::binary);
    if (!ledger_in_stream){
        cout << "There is no ledger. Loading the Character creator to make one.\n";
        createCharacter();
        createdCharacterInConstructor = true;
    } else if (!_ledger_data.ParseFromIstream(&ledger_in_stream)){
        throw ledger_exception("Failed to parse the characters ledger.");
    } else if (_ledger_data.characters_size() == 0){
        cout << "There are no characters in the character ledger. Loading the Charater creator to make one.\n";
        createCharacter();
        createdCharacterInConstructor = true;
    } 
}

ledger::~ledger()
{
    fstream ledger_out_stream(_full_ledger_path, ios::out | ios::binary | ios::trunc);
    if (!_ledger_data.SerializeToOstream(&ledger_out_stream)){
        cout << "Failed to write to the character ledger. Check it exists in " << _full_ledger_path << endl;
    }
}

void ledger::setAbilityScoreHelper(dnd::character *c){
    int ability_score;
    for (size_t i = 0; i < NUM_ABILITY_SCORES; i++){   
        cout << "Enter the Character's " << string(ABILITY_NAMES[i]) << " Ability(integer): ";
        cin >> ability_score;
        if(cin.fail()){
            cin.clear();
            throw ledger_exception("Received a non integer value for the " + string(ABILITY_NAMES[i]) + " Ability. Aborting current character creation.");
        } else if(ability_score <= 0 || ability_score > 20) {
            cin.clear();
            throw ledger_exception("Received a value out of range for the " + string(ABILITY_NAMES[i]) + " Ability. Abilities range between 1 and 20 inclusive. Aborting current character creation.");
        }
        c->add_ability_scores(ability_score);
    }
}

void ledger::createCharacterHelper(){
    string name, short_name;
    dnd::character * new_character = _ledger_data.add_characters();
    cout << "Enter the Full Name for your Character: ";
    getline(cin, name);
    if (name.empty()){
        cout << "Character must have a name.\n";
        return;
    } 
    cout << "Enter a Short Name for your Character with no spaces: ";
    getline(cin, short_name);
    if (short_name.empty()){
        cout << "Character must have a Short Name. Aborting current character creation.\n";
        return;
    } else if (short_name.find(" ") != string::npos){
        cout << "The Short Name must have no spaces. Aborting current character creation.\n";
        return;
    }
    setAbilityScoreHelper(new_character);
    cin.ignore(256, '\n'); // at end of
    cout << "Adding a character named: " << name << "\n";
    new_character->set_name(name);
    new_character->set_short_name(boost::algorithm::to_lower_copy(short_name));


}

void ledger::createCharacter(){
    if (createdCharacterInConstructor){
        return;
    }
    cout << "Welcome to the Character Creator:\n";   
    createCharacterHelper();

    while (true){
        string resp;
        cout << "Would you like to add another character? (y or n) ";
        getline(cin, resp);
        if (resp.compare("n") == 0){
            cout << "Exiting Character Creator." << endl;
            break;
        } else if (resp.compare("y") == 0){
            createCharacterHelper();
        } else {
            cout << "Recieved invalid response, Exiting Character Creator." << endl;
            break;
        }
    }
}

void ledger::getCharacterAbilityScores(string name){
    size_t numAbilityScores = 6;
    dnd::character c;
    getCharacter(name, c);
    cout << c.name() << "'s Ability Scores:\n";
    for(size_t i = 0; i < NUM_ABILITY_SCORES; i++){
        cout << "  " << string(ABILITY_NAMES[i]) << ": " << c.ability_scores(i) << "\n";
    }
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

int32_t ledger::strength(string name){
    dnd::character c;
    getCharacter(name, c);
    return c.ability_scores(STRENGTH);
}

int32_t ledger::dexterity(string name){
    dnd::character c;
    getCharacter(name, c);
    return c.ability_scores(DEXTERITY);
}

int32_t ledger::constitution(string name){
    dnd::character c;
    getCharacter(name, c);
    return c.ability_scores(CONSTITUTION);
}

int32_t ledger::intelligence(string name){
    dnd::character c;
    getCharacter(name, c);
    return c.ability_scores(INTELLIGENCE);
}

int32_t ledger::wisdom(string name){
    dnd::character c;
    getCharacter(name, c);
    return c.ability_scores(WISDOM);
}

int32_t ledger::charisma(string name){
    dnd::character c;
    getCharacter(name, c);
    return c.ability_scores(CHARISMA);
}

void ledger::listCharacters(){
    cout << "Available Characters:" << endl;
    for (int i = 0; i < _ledger_data.characters_size(); i++){
        cout << _ledger_data.characters(i).name() << " (" << _ledger_data.characters(i).short_name() << ")" << endl;
    }
}

ledger_exception::ledger_exception(string msg) : _msg(msg){}

string ledger_exception::what(){
    return "Encountered the following issue with the ledger: " + _msg;
}
