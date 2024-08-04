#include "creator.h"

CharacterCreator::CharacterCreator()
{
}

CharacterCreator::~CharacterCreator()
{
}

void CharacterCreator::promptGetLine(string prompt, string error_msg, string &response)
{
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

void CharacterCreator::setAbilityScoreHelper(Character *c){
    int ability_score;
    for (size_t i = 0; i < NUM_ABILITY_SCORES; i++){   
        promptNumber("Enter the Character's " + string(ABILITY_NAMES[i]) + " Ability(integer): ", 
                     ability_score,
                     pair<int32_t, int32_t>(0,20));
        c->setAbilityScore(i, ability_score);
    }
}

void CharacterCreator::setCharacterFluffHelper(Character *c){
    string response;
    personality_traits personality;
    promptGetLine("Enter the Character's Personality Trait: ", 
                  "Character must have a personality trait.", response);
    personality.personality_trait = response;
    promptGetLine("Enter the Character's Ideal: ", 
                  "Character must have a ideal.", response);
    personality.ideals = response;
    promptGetLine("Enter the Character's Bond: ", 
                  "Character must have a bond.", response);
    personality.bonds = response;
    promptGetLine("Enter the Character's Flaw: ", 
                  "Character must have a Flaw.", response);
    personality.flaws = response;
    promptGetLine("Enter the Character's Alignment: ", 
                  "Character must have an alignment.", response);
    personality.alignment = response;
    c->setPersonalityTraits(personality);

    int32_t numResponse;
    physical_traits presence;
    promptNumber("Enter the Character's Age in years: ", numResponse, pair<int,int>(0, INT32_MAX));
    presence.age = numResponse;
    promptNumber("Enter the Character's Height in inches: ", numResponse, pair<int,int>(1, INT32_MAX));
    presence.height = numResponse;    
    promptNumber("Enter the Character's Weight in lbs: ", numResponse, pair<int,int>(1, INT32_MAX));
    presence.weight = numResponse;
    promptGetLine("Enter the Character's Skin Tone: ", 
                  "Character must have a skin tone.", response);
    presence.skin_tone = response;
    promptGetLine("Enter the Character's Hair Color: ", 
                  "Character must have a hair color.", response);
    presence.hair_color = response;
    promptGetLine("Enter the Character's Eye Color: ", 
                  "Character must have a Eye Color.", response);
    presence.eye_color = response;
    c->setPhysicalTraits(presence);

    promptGetLine("Enther the Character's Backstory: ", 
                  "Character must have a backstory.", response);
    c->setBackstory(response);
}

bool CharacterCreator::createCharacterHelper(){
    string name, short_name;
    Character * new_character = new Character();
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
    new_character->setName(name);
    new_character->setShortName(boost::algorithm::to_lower_copy(short_name));
    _createdCharacters.push_back(*new_character);

    return true;
}

void CharacterCreator::createCharacter(){
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
    
    if(_createdCharacters.size() > 0) addCharactersToLedger();
}

void CharacterCreator::addCharactersToLedger()
{
    ledger * character_ledger = new ledger();
    for(Character character : _createdCharacters){
        character_ledger->addCharacter(character);
    }
    delete character_ledger;
}

create_character_exception::create_character_exception(string msg) : _msg(msg){}

string create_character_exception::what(){
    return "Received an invalid response: " + _msg;
}

