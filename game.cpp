#include "entity/entity_loader.h"
#include "weapons/weapon_loader.h"
#include "battle/battle.h"

Entity* selectCharacter(const std::vector<Entity*>& characters) {
    size_t choice;
    std::cout << "Select a character (1-" << characters.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > characters.size()) {
        std::cerr << "Invalid choice.\n";
        return nullptr;
    }
    return characters[choice - 1];
}



Entity* createNewCharacter(const std::unordered_map<std::string, Weapon>& availableWeapons) {
    std::string name;
    int health, strength, defense, startingHealth, lvl;

    // Get character details from the user
    std::cout << "Enter character name: ";
    std::getline(std::cin, name);

    health = 10 + (rand() % 41);

    std::cout << "Enter strength (recomended around 10): ";
    std::cin >> strength;
    

    std::cout << "Enter defense (recomended around 10): ";
    std::cin >> defense;
   

    std::cin.ignore(); // Clear the newline character

    // Starting health and level
    startingHealth = health;
    lvl = 1; // Initialize level to 1 for new characters

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
    return new Character(name, health, strength, strengthMax, defense, defenseMax, selectedWeapon, startingHealth, lvl);
}


void displayCharacters(const std::vector<Entity*>& allEntities) {
    std::cout << "############################################\n"
              << "               Available Characters         \n"
              << "############################################";

    int index = 1;
    for (Entity* entity : allEntities) {
        // Check if the entity is of type Character
        if (entity->getType() == "Character") {
            std::cout << "\n[" << index++ << "] ";
            entity->print();  // Calls the print() function for the Character
        }
    }

    std::cout << "\n############################################\n"
              << "             Select a character (1-" << index-1 << "): \n"
              << "############################################\n";
}

int main() {
    srand(time(nullptr));
    // Prompt user to open the game in a new terminal
    
    std::string weaponFile = "csv/weapons.csv";
    std::string characterFile = "csv/characters.csv";
    //std::string enemyFile = "csv/enemies.csv";
    std::string mobFile = "csv/mobs.csv";

    // Load weapons
    auto weapons = loadWeapons(weaponFile);

    // Load entities (characters, enemies, and mobs)
    std::vector<Entity*> allEntities;

    // Load characters

    // Load enemies
    //auto enemies = loadEntities(enemyFile, weapons);  
    //allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());

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

        // Save the new character to the characters.csv file
        std::ofstream outFile(characterFile, std::ios::app);  // Open in append mode
        if (outFile) {
            outFile << newCharacter->getName() << ",Character," 
                    << newCharacter->getHealth() << ","
                    << newCharacter->getStrength() << ","
                    << newCharacter->getStrengthMax() << ","
                    << newCharacter->getDefense() << ","
                    << newCharacter->getDefenseMax() << ","
                    << newCharacter->getWeapon().name << ",";
            // Check if this entity is a Character
            Character* charPtr = dynamic_cast<Character*>(newCharacter);
            if (charPtr) {
                outFile  << charPtr->getStartingHealth() << "," << charPtr->getLvl() << "\n";
            }
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
    displayCharacters(allEntities);

    // Select character
    Entity* player = selectCharacter(characters);
    if (!player) {
        std::cerr << "Character selection failed. Exiting game...\n";
        return 1;
    }
    do {
        Entity* mob = pickRandomMob(mobs);
        
        if (mob == nullptr) { // Check if all mobs are dead
            std::cout << "Congratulations! You have defeated all enemies! You win!\n";
            break;
        }
    
        printFightStats(player, mob);
        fight(player, mob);
    
        if (player->getHealth() <= 0) { // Check if the player is dead
            std::cout << "You have been defeated! Game over.\n";
            break;
        }
    
        std::cout << "\nDo you want to continue or go home? (c for continue, h for home): ";
        std::cin >> choice;
        std::cin.ignore();
    
    } while (choice == 'c' || choice == 'C');
    
    std::cout << "Thanks for playing!\n";
    return 0;
}
