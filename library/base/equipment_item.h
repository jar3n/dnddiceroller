#ifndef _EQUIPMENT_ITEM_H_
#define _EQUIPMENT_ITEM_H_

#include <string>
using namespace std;

class EquipmentException : public exception {
    private:
    string name;
    string msg;
    public:
    EquipmentException(string name, string msg) : name(name), msg(msg){}
    string what(){
        return "There is an error with the equipment item " + name + ": " + msg;
    }
};

class EquipmentItem {
    private:
    string name;
    int cost;
    int weight;
    string description;
    bool attuned;
    bool equipped;

    public:
    EquipmentItem(string name, int cost, int weight, string description);
    EquipmentItem(string name, int cost, int weight, string description, bool equipped);
    EquipmentItem(string name, int cost, int weight, string description, bool equipped, bool attuned);
    
    void attune();
    void equip();

};


#endif