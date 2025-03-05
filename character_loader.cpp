#include "entity_loader.h"

// Function to load entities from CSV file
std::vector<Entity*> loadEntities(const std::string& filename, const std::unordered_map<std::string, Weapon>& weapons) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Entity*> entities;
    
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return entities;
    }

    std::getline(file, line); // Skip header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, type, healthStr, strStr, strMaxStr, defStr, defMaxStr, weaponName;

        std::getline(ss, name, ',');
        std::getline(ss, type, ',');
        std::getline(ss, healthStr, ',');
        std::getline(ss, strStr, ',');
        std::getline(ss, strMaxStr, ',');
        std::getline(ss, defStr, ',');
        std::getline(ss, defMaxStr, ',');
        std::getline(ss, weaponName, ',');

        int health = std::stoi(healthStr);
        int strength = std::stoi(strStr);
        int strengthMax = std::stoi(strMaxStr);
        int defense = std::stoi(defStr);
        int defenseMax = std::stoi(defMaxStr);

        Weapon weapon;
        // Convert weaponName to lowercase before searching in the map
        std::string lowerWeaponName = toLowerCase(weaponName);

        if (weapons.find(lowerWeaponName) != weapons.end()) {
            weapon = weapons.at(lowerWeaponName);
        } else {
            std::cerr << "Warning: Weapon not found for entity " << name << ": " << weaponName << std::endl;
        }

        // Create specific entity types based on 'type'
        Entity* entity = nullptr;
        if (type == "Character") {
            entity = new Character(name, health, strength, strengthMax, defense, defenseMax, weapon);
        } else if (type == "Enemy") {
            entity = new Enemy(name, health, strength, strengthMax, defense, defenseMax, weapon);
        } else if (type == "Mob") {
            entity = new Mob(name, health, strength, strengthMax, defense, defenseMax, weapon);
        }
        

        if (entity) {
            entities.push_back(entity);
        }
    }

    return entities;
}

// Function to print entity details
void printEntity(const Entity* entity) {
    if (entity) {
        entity->print();
    }
}
