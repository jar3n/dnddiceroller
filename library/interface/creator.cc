#include "creator.h"

CharacterCreator::CharacterCreator()
{
}

CharacterCreator::~CharacterCreator()
{
}

void CharacterCreator::promptGetLine(string prompt, string error_msg, string &response){
    cout << prompt;
    getline(cin, response);
    if (response.empty()){
        throw create_character_exception(error_msg);
    }
}

void CharacterCreator::promptNumber(string prompt, 
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

void CharacterCreator::promptStringNoSpaces(string prompt, string error_msg, string &response){
    cout << prompt;
    cin >> response;
    if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        throw create_character_exception(error_msg);
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

void CharacterCreator::setAbilityScoreHelper(dnd::character *c){
    int ability_score;
    for (size_t i = 0; i < NUM_ABILITY_SCORES; i++){   
        promptNumber("Enter the Character's " + string(ABILITY_NAMES[i]) + " Ability(integer): ", 
                     ability_score,
                     pair<int32_t, int32_t>(0,20));
        c->add_ability_scores(ability_score);
    }
}

void CharacterCreator::setCharacterFluffHelper(dnd::character *c){
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

bool CharacterCreator::createCharacterHelper(){
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

void CharacterCreator::createCharacter(){
    if(_createdCharacterInConstructor){
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
    _haveUpdateToLedger = createdACharacter;
}

create_character_exception::create_character_exception(string msg) : _msg(msg){}

string create_character_exception::what(){
    return "Received an invalid response: " + _msg;
}

