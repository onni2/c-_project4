#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "entity_loader.h"

// Function declarations
void printFightStats(const Entity* player, const Entity* mob);
void fight(Entity* player, Entity* mob);
Entity* pickRandomMob(const std::vector<Entity*>& mobs);

#endif // BATTLE_H
