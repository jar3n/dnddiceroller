#include "ledger.h"
#include <boost/algorithm/string.hpp>

void ledger::createCharacterHelper()
{
    string name, short_name;
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
    int strength;
    cout << "Enter the Character's Strength Ability(integer): ";
    cin >> strength;
    if(cin.fail()){
        cin.clear();
        cout << "Received an invalid value for the Strength Ability. Aborting current character creation.\n";
        return;
    }
    cin.ignore(256, '\n');
    cout << "Adding a character named: " << name << "\n";
    dnd::character * new_character = _ledger_data.add_characters();
    new_character->set_name(name);
    new_character->set_strength(strength);
    new_character->set_short_name(boost::algorithm::to_lower_copy(short_name));
}

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

void ledger::createCharacter()
{
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

void ledger::getCharacterInfo(string name)
{
    name = boost::algorithm::to_lower_copy(name);
    bool found_no_character = true;
    for(int i = 0; i < _ledger_data.characters_size(); i++){
        dnd::character c = _ledger_data.characters(i);
        if (c.short_name() == name){
            cout << c.name() << ": " << endl;
            cout << "    Strength: " << c.strength() << endl;
            found_no_character = false;
            break;
        }
    }
    if (found_no_character){
        cout << "Found no character with the name: " << name << "\n"; 
    }
}

void ledger::listCharacters()
{
    cout << "Available Characters:" << endl;
    for (int i = 0; i < _ledger_data.characters_size(); i++){
        cout << _ledger_data.characters(i).name() << endl;
    }
}

ledger_exception::ledger_exception(string msg) : _msg(msg)
{
}

string ledger_exception::what()
{
    return "Encountered the following issue with the ledger: " + _msg;
}
