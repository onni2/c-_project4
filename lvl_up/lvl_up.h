#ifndef LVL_UP_H
#define LVL_UP_H

#include "../entity/entity_loader.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Function to prompt player for level-up choices and update stats
void levelUp(Character* character);

// Function to update the CSV file with the new character stats
void updateCSV(const Character& character);

#endif // LVL_UP_H
