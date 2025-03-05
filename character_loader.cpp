#include "character_loader.h"


// Function to load characters from CSV file
std::vector<Character> loadCharacters(const std::string& filename, const std::unordered_map<std::string, Weapon>& weapons) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Character> characters;
    
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return characters;
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

        Character character;
        character.name = name;
        character.type = type;
        character.health = std::stoi(healthStr);
        character.strength = std::stoi(strStr);
        character.strengthMax = std::stoi(strMaxStr);
        character.defense = std::stoi(defStr);
        character.defenseMax = std::stoi(defMaxStr);

        if (weapons.find(weaponName) != weapons.end()) {
            character.weapon = weapons.at(weaponName);
        } else {
            std::cerr << "Warning: Weapon not found for character " << name << ": " << weaponName << std::endl;
        }

        characters.push_back(character);
    }

    return characters;
}

// Function to print character details
void printCharacter(const Character& character) {
    std::cout << "Name: " << character.name << " (" << character.type << ")\n";
    std::cout << "Health: " << character.health << "\n";
    std::cout << "Strength: " << character.strength << "/" << character.strengthMax << "\n";
    std::cout << "Defense: " << character.defense << "/" << character.defenseMax << "\n";
    std::cout << "Weapon: " << character.weapon.name << " (Damage: " << character.weapon.damage
              << ", Magic: " << character.weapon.magic << ")\n";
    std::cout << "-------------------------\n";
}
