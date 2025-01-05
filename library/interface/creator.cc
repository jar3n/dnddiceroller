#include "creator.h"

CharacterCreator::CharacterCreator()
{
}

CharacterCreator::~CharacterCreator()
{
}

void CharacterCreator::promptGetLine(string prompt, string error_msg, string &response){
    uint16_t attempts = 0;
    do {
        cout << prompt;
        getline(cin, response); 
        if (response.empty()) {
            cout << "Please provide a response (attempts left " << PROMPT_RETRIES - attempts << ")" << endl;
        }
    } while (response.empty() && attempts++ < PROMPT_RETRIES);

    if (response.empty()){
        throw create_character_exception(error_msg);
    }
}

void CharacterCreator::promptGetYesNo(string prompt, bool &response)
{
    uint16_t attempts = 0;
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Please provide a response (attempts left " << PROMPT_RETRIES - attempts
            << ")" << endl;
        } else if (input == "yes" || input == "y") {
            response = true;
            break;
        } else if (input == "no" || input == "n") {
            response = false;
            break;
        } else {
            cout << "Invalid input. Please enter 'yes' or 'no' (attempts left " << PROMPT_RETRIES - attempts << ")" << endl;
            }
        } while (input.empty() || (input != "yes" && input != "y" && input != "no" && input != "n") && attempts++ < PROMPT_RETRIES);
        
        if (input.empty() || (input != "yes" && input != "y" && input != "no" && input != "n") || attempts++ >= PROMPT_RETRIES){
            throw create_character_exception("Did not receive a valid response. Exiting Character creator.");
        } 
}

void CharacterCreator::promptNumber(string prompt, 
                          int32_t &response,
                          pair<int32_t,int32_t> range){
    uint16_t attempts = 0;
    do {
        cout << prompt;
        cin >> response;
        if (cin.fail() || 
            response <= range.first || response > range.second){
            cin.clear();
            cout << "Please provide a numerical value within the range (" 
            << range.first << "-" << range.second << ")" << endl;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while ((cin.fail() || 
              response <= range.first || 
              response > range.second) && 
              attempts++ < PROMPT_RETRIES);

    if (attempts >= PROMPT_RETRIES){
            throw create_character_exception("Did not receive a valid response. Exiting Character creator.");
    } 
}

void CharacterCreator::promptStringNoSpaces(string prompt, string error_msg, string &response){
    uint16_t attempts = 0;
    do {
        cout << prompt;
        cin >> response;
        if (cin.fail()){
            cin.clear();
            cout << error_msg << endl;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    } while (cin.fail() && attempts++ < PROMPT_RETRIES);

    if (attempts >= PROMPT_RETRIES){
        throw create_character_exception("Did not receive a valid reponse. Exiting Character creator.");
    }

}

void CharacterCreator::setAbilityScoreHelper(Character *c){
    int score;
    for (ability_score i : ability_score_vector){   
        promptNumber("Enter the Character's " + string(ABILITY_NAMES[i]) + " Ability(integer): ", 
                     score,
                     pair<int32_t, int32_t>(0,20));
        c->setAbilityScore(i, score);
    }
}

void CharacterCreator::setProficiencyHelper(Character *c)
{
    bool proficient;
    for (ability_score i : ability_score_vector){
        promptGetYesNo("Is the Character proficient at " + string(ABILITY_NAMES[i]) + " saves? (yes or no): ", proficient);
        c->setSaveProficiency(i, proficient);
    }

    for(skill s : skill_vector){
        promptGetYesNo("Is the Character proficient at " + string(SKILL_NAMES[s]) + "? (yes or no): ", proficient);
        c->setSkillProficiency(s, proficient);
        if (proficient){
            promptGetYesNo("Is the Character an expert at " + string(SKILL_NAMES[s]) + "? (yes or no): ", proficient);
            c->setSkillExpertise(s, proficient);
        }
    }
}

void CharacterCreator::setClassHelper(Character *c)
{
    // generating the prompt for the character class
    // it will print a list of 
    // classes and associated numbers
    // then prompt the user for a number 
    std::string classPrompt = "";
    int count = 0;
    for (character_class i : character_class_vector){
        classPrompt += string(CHARACTER_CLASS[i]) + ": " + std::to_string(count) + "\n";
        count++;
    }
    classPrompt += "Type the number associated with the desired class: ";
    int class_int;
    promptNumber(classPrompt, class_int, pair<int,int>(0, count));
    c->setClass(character_class_vector[class_int]);
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
    int level;
    Character * new_character = new Character();
    try {
        promptGetLine("Enter the Full Name for your Character: ", 
                      "Character must have a name.", name);
        promptStringNoSpaces("Enter a Short Name for your Character with no spaces: ", 
                      "Character must have a Short Name.", short_name);
        promptNumber("Enter the level of your Character (integer): ", level, pair<int,int>(1,20));
        setAbilityScoreHelper(new_character);
        setProficiencyHelper(new_character);
        setCharacterFluffHelper(new_character);
        setClassHelper(new_character);
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
    new_character->setLevel(level);
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

