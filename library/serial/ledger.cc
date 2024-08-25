#include "ledger.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <limits>
#include <unistd.h>
#include <sys/stat.h>

using namespace boost::filesystem;


ledger::ledger(){
    // put the ledger in the same directory as the dice roller executable
    // this is linux only 
    // need to add windows and other OS ways later
    char executableDir[PATH_MAX];
    size_t path_length = readlink("/proc/self/exe", executableDir, sizeof(executableDir));
    string exeDirStr(executableDir, path_length);
    path exe_path(exeDirStr);

    _full_ledger_path = exe_path.parent_path().string() + "/ledger/";

    if ( !exists(path(_full_ledger_path))){
        create_directories(path(_full_ledger_path));
    }


}

ledger::~ledger(){
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

    for(ability_score i : ability_score_vector){
        character.setAbilityScore(i, ledger_character.ability_scores(i));
        character.setSaveProficiency(i, ledger_character.save_proficiencies(i));
    }

    for(skill i : skill_vector){
        character.setSkillProficiency(i, ledger_character.skill_proficiencies(i));
        character.setSkillExpertise(i, ledger_character.skill_expertise(i));
    }
    character.setBackstory(ledger_character.backstory());

}

string ledger::createCharacterFile(string name){

    string character_file_string = _full_ledger_path + name;
    
    struct stat buffer;
    if (stat(character_file_string.c_str(), &buffer) != 0){
        // check the file does not exist before creating it
        fstream ledger_file;
        ledger_file.open(character_file_string, ios::out);
        if(!ledger_file){
            throw ledger_exception("Unable to create the character file.");
        }
        ledger_file.close();
    } else {
        throw ledger_exception("There is already a character in the ledger with the name: " + name);
    }

    return character_file_string;

}

string ledger::getCharacterFile(string name)
{
    name = boost::algorithm::to_lower_copy(name);
    string character_file_string = _full_ledger_path + name;
    
    struct stat buffer;
    if (stat(character_file_string.c_str(), &buffer) != 0){
        // create the character file if it doesn't already exist
        throw ledger_exception("The character is not in the ledger. run the character creator to add it.");
    }

    return character_file_string;
}

void ledger::addCharacter(Character c)
{
    dnd::character lc;

    lc.set_name(c.getName());
    lc.set_short_name(c.getShortName());
    lc.set_backstory(c.getBackstory());
    
    dnd::personality_traits * p = lc.mutable_personality();
    personality_traits pc = c.getPersonalityTraits();
    p->set_personality_trait(pc.personality_trait);
    p->set_ideals(pc.ideals);
    p->set_bonds(pc.bonds);
    p->set_flaws(pc.flaws);
    p->set_alignment(pc.alignment);

    dnd::physical_traits * ph = lc.mutable_presence();
    physical_traits phc = c.getPhysicalTraits();
    ph->set_age(phc.age);
    ph->set_eye_color(phc.eye_color);
    ph->set_hair_color(phc.hair_color);
    ph->set_height(phc.height);
    ph->set_weight(phc.weight);
    ph->set_skin_tone(phc.skin_tone);

    for(ability_score i : ability_score_vector){
        lc.add_ability_scores(c.getAbilityScore(i));
        lc.add_save_proficiencies(c.isSaveProficient(i));
    }

    for(skill s : skill_vector){
        lc.add_skill_proficiencies(c.isSkillProficient(s));
        lc.add_skill_expertise(c.isSkillExpert(s));
    }

    // write the character to the file
    fstream ledger_out_stream(createCharacterFile(c.getShortName()), ios::out | ios::binary | ios::trunc);
    if (!lc.SerializeToOstream(&ledger_out_stream)){
        throw ledger_exception("Failed to save character.");
    }
    ledger_out_stream.close();

}

void ledger::getCharacter(string name, Character& character){
    name = boost::algorithm::to_lower_copy(name);
    string character_file = getCharacterFile(name);

    dnd::character lc;
    fstream character_stream(character_file, ios::in | ios::binary);
    if(!lc.ParseFromIstream(&character_stream)){
        throw ledger_exception("Unable to parse character file.");
    }
    character_stream.close();

    convertLedgerCharactertoCharacter(lc, character);
    
}

vector<Character> ledger::getAllCharacters()
{
    vector<Character> characters;
    for(directory_iterator i(_full_ledger_path); i != directory_iterator(); i++){
        dnd::character lc;
        fstream character_stream(i->path().string(), ios::in | ios::binary);
        if(!lc.ParseFromIstream(&character_stream)){
            throw ledger_exception("Unable to parse character file.");
        }
        character_stream.close();
        Character c;
        convertLedgerCharactertoCharacter(lc, c);
        characters.push_back(c);
    }

    return characters;
}

void ledger::deleteCharacter(string name){
    string character_file = getCharacterFile(name);
    remove(character_file.c_str());
}

size_t ledger::size()
{
    size_t size = 0;
    for(directory_iterator i(_full_ledger_path); i != directory_iterator(); i++){
        ++size;
    }
    return size;
}

ledger_exception::ledger_exception(string msg) : _msg(msg){}

string ledger_exception::what(){
    return "Encountered the following issue with the ledger: " + _msg;
}

