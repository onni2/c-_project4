#include <cstdlib>  // For system()
#include <filesystem>  // For current_path()
#include <iostream>

int main() {
    // Get the current working directory
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::filesystem::path gameExecutable = currentDir / "game.exe";  // Adjust the executable name if needed

    // Prompt user to open the game in a new terminal
    char choice;
    std::cout << "Do you want to run the game in a new terminal window?\nGood if you are running the code in you vscode terminal\nThis code only works in windows, if mac/linux then press no (y/n): ";
    std::cin >> choice;

    // If user wants to run in a new terminal, use system() to open a new command prompt
    if (choice == 'y' || choice == 'Y') {
        std::string command = "start cmd /K \"" + gameExecutable.string() + "\"";
        system(command.c_str());  // Run the game in a new terminal
        return 0;  // Exit launcher after opening the new terminal
    }

    // Otherwise, run in the current terminal
    system(gameExecutable.string().c_str());
    return 0;
}
