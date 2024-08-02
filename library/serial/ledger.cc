#include "ledger.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <limits>
#include <unistd.h>
#include <sys/stat.h>


ledger::ledger(){
    // put the ledger in the same directory as the dice roller executable
    // this is linux only 
    // need to add windows and other OS ways later
    char executableDir[PATH_MAX];
    size_t path_length = readlink("/proc/self/exe", executableDir, sizeof(executableDir));
    string exeDirStr(executableDir, path_length);
    boost::filesystem::path exe_path(exeDirStr);

    _full_ledger_path = exe_path.parent_path().string() + "/character_ledger";

    struct stat buffer;
    if (stat(_full_ledger_path.c_str(), &buffer) != 0){
        fstream ledger_file;
        ledger_file.open(_full_ledger_path, ios::out);
        if(!ledger_file){
                throw ledger_exception("Unable to create the character ledger");
        }
        ledger_file.close();
    } 
    fstream ledger_in_stream(_full_ledger_path, ios::in | ios::binary);

    if (!_ledger_data.ParseFromIstream(&ledger_in_stream)){
        throw ledger_exception("Failed to parse the characters ledger.");
    } 
}

ledger::~ledger(){
}

void ledger::writeToLedger()
{
    fstream ledger_out_stream(_full_ledger_path, ios::out | ios::binary | ios::trunc);
    if (!_ledger_data.SerializeToOstream(&ledger_out_stream)){
        cout << "Failed to write to the character ledger. Check it exists in " << _full_ledger_path << endl;
    }
}

void ledger::convertLedgerCharactertoCharacter(dnd::character& ledger_character, Character &character)
{
    character.setName(ledger_character.name());
    character.setShortName(ledger_character.short_name());

    personality_traits pc;
    dnd::personality_traits dpc = ledger_character.personality();
    pc.personality_trait = dpc.personality_trait();
    pc.ideals = dpc.ideals();
    pc.bonds = dpc.bonds();
    pc.flaws = dpc.flaws();
    pc.alignment = dpc.alignment();
    character.setPersonalityTraits(pc);

    physical_traits phc;
    dnd::physical_traits dphc = ledger_character.presence();
    phc.age = dphc.age();
    phc.eye_color = dphc.eye_color();
    phc.hair_color = dphc.hair_color();
    phc.height = dphc.height();
    phc.skin_tone = dphc.skin_tone();
    phc.weight = dphc.weight();
    character.setPhysicalTraits(phc);

    for(size_t i = 0; i < NUM_ABILITY_SCORES; i++){
        character.setAbilityScore(i, ledger_character.ability_scores(i));
    }

}

void ledger::addCharacter(Character c)
{
    dnd::character * lc = _ledger_data.add_characters();

    lc->set_name(c.getName());
    lc->set_short_name(c.getShortName());
    lc->set_backstory(c.getBackstory());
    
    dnd::personality_traits * p = lc->mutable_personality();
    personality_traits pc = c.getPersonalityTraits();
    p->set_personality_trait(pc.personality_trait);
    p->set_ideals(pc.ideals);
    p->set_bonds(pc.bonds);
    p->set_flaws(pc.flaws);
    p->set_alignment(pc.alignment);

    dnd::physical_traits * ph = lc->mutable_presence();
    physical_traits phc = c.getPhysicalTraits();
    ph->set_age(phc.age);
    ph->set_eye_color(phc.eye_color);
    ph->set_hair_color(phc.hair_color);
    ph->set_height(phc.height);
    ph->set_weight(phc.weight);
    ph->set_skin_tone(phc.skin_tone);

    for(size_t i = 0; i < NUM_ABILITY_SCORES; i++){
        lc->add_ability_scores(c.getAbilityScore(i));
    }

    writeToLedger();
}

void ledger::getCharacter(string name, Character& character){
    size(); // check ledger has any characters

    name = boost::algorithm::to_lower_copy(name);
    bool found_no_character = true;
    dnd::character ledger_character;
    for(int i = 0; i < _ledger_data.characters_size(); i++){
        if (_ledger_data.characters(i).short_name() == name){
            ledger_character = _ledger_data.characters(i);
            found_no_character = false;
            break;
        }
    }
    if (found_no_character){
        throw ledger_exception("Found no character with the name: " + name +"\n"); 
    } else {
        convertLedgerCharactertoCharacter(ledger_character, character);
    }
}

void ledger::getCharacter(size_t index, Character &character)
{
   size();
   dnd::character ledger_character = _ledger_data.characters(index);
   convertLedgerCharactertoCharacter(ledger_character, character);
}

size_t ledger::size()
{
    if (_ledger_data.characters_size() == 0 ||
       (_ledger_data.characters_size() == 1 && _ledger_data.characters(1).short_name() == "")){
        throw ledger_exception("The ledger has no characters. Run the Character Creator to make one.");
    } else {
        return _ledger_data.characters_size();
    }
}

ledger_exception::ledger_exception(string msg) : _msg(msg){}

string ledger_exception::what(){
    return "Encountered the following issue with the ledger: " + _msg;
}

