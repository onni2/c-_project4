#include "character_loader.h"
#include "weapon_loader.h"

int main() {
    std::string weaponFile = "weapons.csv";
    std::string characterFile = "characters.csv";

    // Load weapons
    auto weapons = loadWeapons(weaponFile);

    // Load characters
    auto characters = loadCharacters(characterFile, weapons);

    // Print characters
    for (const auto& character : characters) {
        printCharacter(character);
    }

    return 0;
}