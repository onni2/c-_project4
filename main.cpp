#include "entity_loader.h"
#include "weapon_loader.h"
#include "battle.h"

// Function to select a character interactively
Entity* selectCharacter(const std::vector<Entity*>& characters) {
    std::vector<Entity*>::size_type choice;  // Use the correct type here for choice
    std::cout << "Select a character (1-" << characters.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > characters.size()) {
        std::cerr << "Invalid choice.\n";
        return nullptr;  // Or handle the error as needed
    }
    return characters[choice - 1];  // Access character with the selected choice
}

Entity* createNewCharacter(const std::unordered_map<std::string, Weapon>& availableWeapons) {
    std::string name;
    int health, strength, defense;
    

    // Get character details from the user
    std::cout << "Enter character name: ";
    std::getline(std::cin, name);

    health = 10 + (rand() % 41);

    std::cout << "Enter strength (max 10): ";
    std::cin >> strength;
    strength = std::min(strength, 10); // Ensure strength does not exceed 10

    std::cout << "Enter defense (max 10): ";
    std::cin >> defense;
    defense = std::min(defense, 10); // Ensure defense does not exceed 10

    std::cin.ignore(); // Clear the newline character

    // Auto-assign max stats to be equal to the entered values
    int strengthMax = 10;
    int defenseMax = 10;

    // Show available weapons
    std::cout << "\nAvailable Weapons:\n";
    int index = 1;
    for (const auto& weapon : availableWeapons) {
        std::cout << index++ << ". " << weapon.second.name 
                  << " (Damage: " << weapon.second.damage 
                  << ", Magic: " << weapon.second.magic << ")\n";
    }

    // Get weapon choice from user
    std::cout << "\nChoose a weapon by number: ";
    int weaponChoiceIndex;
    std::cin >> weaponChoiceIndex;
    std::cin.ignore(); // Clear the newline character

    // Find the chosen weapon by index
    auto it = availableWeapons.begin();
    std::advance(it, weaponChoiceIndex - 1);
    Weapon selectedWeapon = it->second;

    // Create the new Character
    return new Character(name, health, strength, strengthMax, defense, defenseMax, selectedWeapon);
}



int main() {

    srand(time(nullptr));

    std::string weaponFile = "csv/weapons.csv";
    std::string characterFile = "csv/characters.csv";
    std::string enemyFile = "csv/enemies.csv";
    std::string mobFile = "csv/mobs.csv";

    // Load weapons
    auto weapons = loadWeapons(weaponFile);

    // Load entities (characters, enemies, and mobs)
    std::vector<Entity*> allEntities;

    // Load characters

    // Load enemies
    auto enemies = loadEntities(enemyFile, weapons);  
    allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());

    // Load mobs
    auto mobs = loadEntities(mobFile, weapons);  
    allEntities.insert(allEntities.end(), mobs.begin(), mobs.end());

    // Create a new Character interactively
    char choice;  // Change to char to store character input
    std::cout << "Do you want to create a new Character? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(); // To clear out the newline character
    if (choice == 'y' || choice == 'Y') {
        Entity* newCharacter = createNewCharacter(weapons);  // Create new Character interactively
        allEntities.push_back(newCharacter);  // Add to the list of all entities

        // Save the new character to the characters.csv file
        std::ofstream outFile(characterFile, std::ios::app);  // Open in append mode
        if (outFile) {
            outFile << newCharacter->getName() << ",Character," 
                    << newCharacter->getHealth() << ","
                    << newCharacter->getStrength() << ","
                    << newCharacter->getStrengthMax() << ","
                    << newCharacter->getDefense() << ","
                    << newCharacter->getDefenseMax() << ","
                    << newCharacter->getWeapon().name << "\n";
            std::cout << "New character added to " << characterFile << std::endl;
        } else {
            std::cerr << "Error opening file: " << characterFile << std::endl;
        }
        
    }
    auto characters = loadEntities(characterFile, weapons);  
    allEntities.insert(allEntities.end(), characters.begin(), characters.end());

    // Print all entities
    //for (Entity* entity : allEntities) {
    //    printEntity(entity);  // Print details of each entity
    //    delete entity;  // Free memory for each entity after printing
    //}
    std::cout << "\nAvailable Characters:\n";
    for (Entity* entity : characters) {  
        printEntity(entity);
    }

    // Select character
    Entity* player = selectCharacter(characters);
    if (!player) {
        std::cerr << "Character selection failed. Exiting game...\n";
        return 1;
    }
    do {
        Entity* mob = pickRandomMob(mobs);
        printFightStats(player, mob);
        fight(player, mob);

        std::cout << "\nDo you want to continue or go home? (c for continue, h for home): ";
        std::cin >> choice;
        std::cin.ignore();
    } while (choice == 'c' || choice == 'C');

    std::cout << "Thanks for playing!\n";
    return 0;
}
