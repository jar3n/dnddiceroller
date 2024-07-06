#include "ledger.h"

dnd::character_ledger ledger::accessLedger()
{
    _ledger_in_stream = fstream(_full_ledger_path, ios::in | ios::binary);
    bool wroteToLedger = false;
    if (!_ledger_in_stream){
        cout << "You have not created a Character ledger, Loading Character Creator to create one." << endl;
        wroteToLedger = createCharacter();
    } else if (!_ledger_data.ParseFromIstream(&_ledger_in_stream)){
        throw ledger_exception("Failed to parse the characters ledger.");
    } else if (_ledger_data.characters_size() == 0){
        cout << "There are no characters in the character ledger. Loading Character Creator to create one." << endl;
        wroteToLedger = createCharacter();
    } else {
        wroteToLedger = ledgerOperation();
    }
    _ledger_in_stream.close();

}

void ledger::createCharacterHelper()
{
    string name;
    cout << "Enter a Name for your Character: ";
    getline(cin, name);
    if (name.empty()){
        cout << "Character must have a name." << endl;
        return;
    } 
    int strength;
    cout << "Enter the Character's Strength Ability(integer): ";
    cin >> strength;
    if(cin.fail()){
        cin.clear();
        cout << "Received an invalid value for the Strength Ability." << endl;
        return;
    }

    cout << "Adding a character named: " << name << endl;
    dnd::character * new_character = _ledger_data.add_characters();
    new_character->set_name(name);
    new_character->set_strength(strength);
}

void ledger::writeToLedger()
{
    fstream _ledger_out_stream(_full_ledger_path, ios::out | ios::binary | ios::trunc);
    if (!_ledger_data.SerializeToOstream(&_ledger_out_stream)){
        cout << "Failed to write to the character ledger. Check it exists in " << _full_ledger_path << endl;
    }
    _ledger_out_stream.close();
}

ledger::ledger(string ledger_path)
{
    char resolved_path[PATH_MAX];
    realpath(ledger_path.c_str(), resolved_path);
    _full_ledger_path = string(resolved_path);
}

bool ledger::createCharacter()
{
    string name;
    cout << "Welcome to the Character Creator:" << endl;   
    createCharacterHelper();

    while (true){
        string resp;
        cout << "Would you like to add another character? (y or n) ";
        getline(cin,resp);
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

    return true; // wrote to ledger 
}

bool ledger::getCharacterInfo(string name)
{
    for(int i = 0; i < _ledger_data.characters_size(); i++){
        dnd::character c = _ledger_data.characters(i);
        if (c.name().compare(name) == 0){
            cout << c.name() << ": " << endl;
            cout << "\tStrength: " << c.strength() << endl;
        }
    }
    return false; // does not write to ledger
}

bool ledger::listCharacters()
{
    cout << "Available Characters:" << endl;
    for (int i = 0; i < _ledger_data.characters_size(); i++){
        cout << _ledger_data.characters(i).name() << endl;
    }
    return false; // does not write to ledger
}

ledger_exception::ledger_exception(string msg) : _msg(msg)
{
}

const char *ledger_exception::what()
{
    return ("Encountered the following issue with the ledger: " + _msg).c_str();
}
