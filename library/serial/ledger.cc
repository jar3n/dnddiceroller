#include "ledger.h"
#include <boost/algorithm/string.hpp>
#include <limits>
#include <unistd.h>

ledger::ledger(){
    char resolved_path[PATH_MAX];
    if (getcwd(resolved_path, sizeof(resolved_path)) == NULL){
        throw ledger_exception("Error locating the install directory, check the permissions on the parent folder.");
    }
    _full_ledger_path = string(resolved_path) + "character_ledger";

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

ledger::~ledger(){
    fstream ledger_out_stream(_full_ledger_path, ios::out | ios::binary | ios::trunc);
    if (!_ledger_data.SerializeToOstream(&ledger_out_stream)){
        cout << "Failed to write to the character ledger. Check it exists in " << _full_ledger_path << endl;
    }
}

void ledger::promptGetLine(string prompt, string error_msg, string &response){
    cout << prompt;
    getline(cin, response);
    if (response.empty()){
        throw create_character_exception(error_msg);
    } 
}

void ledger::promptNumber(string prompt, 
                          int32_t &response,
                          pair<int32_t,int32_t> range){
    cout << prompt;
    cin >> response;
    if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        throw create_character_exception("Received a non integer value.");
    } else if (response <= range.first || response > range.second ){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        throw create_character_exception("Received a value out of range.");
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ledger::promptStringNoSpaces(string prompt, string error_msg, string &response){
    cout << prompt;
    cin >> response;
    if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        throw create_character_exception(error_msg);
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

void ledger::setAbilityScoreHelper(dnd::character *c){
    int ability_score;
    for (size_t i = 0; i < NUM_ABILITY_SCORES; i++){   
        promptNumber("Enter the Character's " + string(ABILITY_NAMES[i]) + " Ability(integer): ", 
                     ability_score,
                     pair<int32_t, int32_t>(0,20));
        c->add_ability_scores(ability_score);
    }
}

void ledger::setCharacterFluffHelper(dnd::character *c){
    string response;
    dnd::personality_traits personality = c->personality();
    promptGetLine("Enter the Character's Personality Trait: ", 
                  "Character must have a personality trait.", response);
    personality.set_personality_trait(response);
    promptGetLine("Enter the Character's Ideal: ", 
                  "Character must have a ideal.", response);
    personality.set_ideals(response);
    promptGetLine("Enter the Character's Bond: ", 
                  "Character must have a bond.", response);
    personality.set_bonds(response);
    promptGetLine("Enter the Character's Flaw: ", 
                  "Character must have a Flaw.", response);
    personality.set_flaws(response);
    promptGetLine("Enter the Character's Alignment: ", 
                  "Character must have an alignment.", response);
    personality.set_alignment(response);

    int32_t numResponse;
    dnd::physical_traits presence = c->presence();
    promptNumber("Enter the Character's Age in years: ", numResponse, pair<int,int>(0, INT32_MAX));
    presence.set_age(numResponse);
    promptNumber("Enter the Character's Height in inches: ", numResponse, pair<int,int>(1, INT32_MAX));
    presence.set_age(numResponse);    
    promptNumber("Enter the Character's Weight in lbs: ", numResponse, pair<int,int>(1, INT32_MAX));
    promptGetLine("Enter the Character's Skin Tone: ", 
                  "Character must have a skin tone.", response);
    presence.set_skin_tone(response);
    promptGetLine("Enter the Character's Hair Color: ", 
                  "Character must have a hair color.", response);
    presence.set_hair_color(response);
    promptGetLine("Enter the Character's Eye Color: ", 
                  "Character must have a Eye Color.", response);
    presence.set_eye_color(response);

    promptGetLine("Enther the Character's Backstory: ", 
                  "Character must have a backstory.", response);
    c->set_backstory(response);
}

bool ledger::createCharacterHelper(){
    string name, short_name;
    dnd::character * new_character = _ledger_data.add_characters();
    try {
        promptGetLine("Enter the Full Name for your Character: ", 
                      "Character must have a name.", name);
        promptStringNoSpaces("Enter a Short Name for your Character with no spaces: ", 
                      "Character must have a Short Name.", short_name);
        setAbilityScoreHelper(new_character);
        setCharacterFluffHelper(new_character);
    } catch(ledger_exception &e){
        cout << e.what() << "\n";
        return false;
    } catch(create_character_exception &e){
        cout << e.what() << "\n";
        return false;
    }

    cout << "Adding a character named: " << name << "\n";
    new_character->set_name(name);
    new_character->set_short_name(boost::algorithm::to_lower_copy(short_name));
    return true;
}

void ledger::createCharacter(){
    if (createdCharacterInConstructor){
        return;
    }
    cout << "Welcome to the Character Creator:\n";   
    bool createdACharacter = createCharacterHelper();

    while (true){
        string resp;
        if (createdACharacter){
            promptStringNoSpaces("Would you like to add another character? (y or n) ", 
                          "Recieved invalid response, Exiting Character Creator.", resp);
        } else {
            promptStringNoSpaces("Would you like to retry? (y or n) ",
                                 "Recieved invalid response, Exiting Character Creator.", resp);
        }
        if (resp.compare("n") == 0){
            cout << "Exiting Character Creator." << endl;
            break;
        } else if (resp.compare("y") == 0){
            createdACharacter = createCharacterHelper();
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
    } else if (createdCharacterInConstructor){
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

create_character_exception::create_character_exception(string msg) : _msg(msg){}

string create_character_exception::what(){
    return "Received an invalid response: " + _msg;
}
