#include "lvl_up.h"
#include <cstring>

void levelUp(Character* character) {
    // Prompt player for level-up choices
    std::cout << "You have leveled up! Choose a stat to increase:\n";
    std::cout << "1. Strength\n";
    std::cout << "2. Health\n";
    std::cout << "3. Defense\n";

    int choice;
    std::cin >> choice;

    int increaseAmount = rand() % 4 + 2; // Random value between 2 and 5

    switch (choice) {
        case 1:
            character->setStrength(character->getStrength() + increaseAmount);
            std::cout << "Strength increased by " << increaseAmount << "!\n";
            break;
        case 2:
            // Reset health to max
            character->setHealth(character->getStrengthMax());
            std::cout << "Health restored to max!\n";
            break;
        case 3:
            character->setDefense(character->getDefense() + increaseAmount);
            std::cout << "Defense increased by " << increaseAmount << "!\n";
            break;
        default:
            std::cout << "Invalid choice! No stat was increased.\n";
            return;
    }

    // Increase level by 1
    character->setLvl(character->getLvl() + 1);
    std::cout << "Level increased to " << character->getLvl() << "!\n";

    // Update the CSV file with the new stats
    updateCSV(*character);
}

void updateCSV(const Character& character) {
    // Open the CSV file in read mode
    std::ifstream inFile("csv/characters.csv");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading: " << strerror(errno) << std::endl;
        return;
    }

    // Temporary storage for updated lines
    std::vector<std::string> lines;
    std::string line;
    bool updated = false;

    // Process each line
    while (std::getline(inFile, line)) {
        std::stringstream lineStream(line);
        std::string Name, type, weapon;
        int health, strength, strengthMax, defense, defenseMax, startingHealth, lvl;

        std::getline(lineStream, Name, ',');  // Get name
        std::getline(lineStream, type, ',');  // Get type
        lineStream >> health >> strength >> strengthMax >> defense >> defenseMax;
        lineStream.ignore(); // Ignore the comma after defenseMax
        std::getline(lineStream, weapon, ','); // Get weapon
        lineStream >> startingHealth >> lvl;  // Get startingHealth and lvl

        // Check if this line corresponds to the character name
        if (Name == character.getName()) {
            // Update the line with new character data
            lines.push_back(character.getName() + "," +
                            "Character," + std::to_string(character.getHealth()) + "," +
                            std::to_string(character.getStrength()) + "," + std::to_string(character.getStrengthMax()) + "," +
                            std::to_string(character.getDefense()) + "," + std::to_string(character.getDefenseMax()) + "," +
                            character.getWeapon().name + "," + std::to_string(character.getStartingHealth()) + "," +
                            std::to_string(character.getLvl()));
            updated = true;
        } else {
            // Keep the line unchanged
            lines.push_back(line);
        }
    }

    // Close the input file after reading
    inFile.close();

    // Open the file in write mode to overwrite the content
    std::ofstream outFile("csv/characters.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing!\n";
        return;
    }

    // Write all lines back to the file
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }

    // Close the output file
    outFile.close();

    // Final message
    if (!updated) {
        std::cout << "Character not found in the CSV file.\n";
    } else {
        std::cout << "Character data updated successfully.\n";
    }
}
