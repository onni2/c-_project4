#include "entity_loader.h"



// Helper function to safely convert strings to integers with error handling
int safeConvertToInt(const std::string& str, int defaultValue = 0) {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid integer: " << str << " - Using default value " << defaultValue << std::endl;
        return defaultValue;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range integer: " << str << " - Using default value " << defaultValue << std::endl;
        return defaultValue;
    }
}

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

        int health = safeConvertToInt(healthStr);
        int strength = safeConvertToInt(strStr);
        int strengthMax = safeConvertToInt(strMaxStr);
        int defense = safeConvertToInt(defStr);
        int defenseMax = safeConvertToInt(defMaxStr);

        Weapon weapon;
        std::string lowerWeaponName = toLowerCase(weaponName);

        if (weapons.find(lowerWeaponName) != weapons.end()) {
            weapon = weapons.at(lowerWeaponName);
        } else {
            std::cerr << "Warning: Weapon not found for entity " << name << ": " << weaponName << std::endl;
        }

        
        // Create specific entity types based on 'type'
        Entity* entity = nullptr;
        if (type == "Character") {
            std::string healthStr,lvlStr;
            std::getline(ss, healthStr, ',');
            std::getline(ss, lvlStr, ',');
            int startingHealth = safeConvertToInt(healthStr);  // Starting health comes from the CSV column
            int lvl = safeConvertToInt(lvlStr);  // Convert the Lvl to an integer

            // Now create the Character with the additional arguments
            entity = new Character(name, health, strength, strengthMax, defense, defenseMax, weapon, startingHealth, lvl);
        } else if (type == "Mob") {
            entity = new Mob(name, health, strength, strengthMax, defense, defenseMax, weapon);
        }

        if (entity) {
            entities.push_back(entity);
        } else {
            std::cerr << "Warning: Unknown entity type for " << name << ": " << type << std::endl;
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
