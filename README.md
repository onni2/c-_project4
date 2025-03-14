# C++ Project 4: Battle Simulator

This project is a battle simulator inspired by Pokémon, where you create and control characters that battle against random mobs in a turn-based fashion.
You also have a option to create your own character to play but that is optional

## Features:
- Start a new game and choose to create a new character.
- Select a weapon for your newly created character.
- Choose a premade or your custom character to start the game.
- Walk encounter random mobs to battle.
- Defeat all the mobs and the 2 bosses to win the game.

## How to Run:

1. **Build the Project:**
   - Compile the project using the provided `Makefile` with make.
   - This will generate two executables: `launcher.exe` and `game.exe`.

2. **Launch the Game:**
   - Run the `launcher.exe` to start the game.
   - Follow the prompts to create a character, select a weapon, and battle mobs.

## Files:
- **`launcher.exe`**: The main executable for starting the game.
- **`game.exe`**: The game engine executable that handles the gameplay and battles.
- **`includes.h`**: This file contains the necessary headers for the project. i did this before todays lecture (14.3.25).

## Notes:
- The project was developed in C++.
- The includes were structured as per best practices after initial guidance.
- The game involves creating a character, selecting weapons, and encountering mobs for battle.

## How to Build:
- Clone or download the repository.
- Navigate to the project directory and run:
  ```bash
  make
