# Intro

## Entry
The cheat starts in entry.cpp at entry() with initializing utilities with their respective Initialize() functions, then installs all Hooks() via hooks::Install(), and finally creates the main loop thread with std::thread(main_loop).detach().

The main loop is where the main cheat logic is, this is seperate from the UI because that's ran inside the games Present function, this is also true for most other game features like chams and world modulation

## Config
It's loaded and saved with config::Load/Save(), the config is stored in the same directory as the game as "config.json", to make new setting sections, you can create a new struct in the Config namespace with the setting variables you want and do NLOHMANN_DEFINE_TYPE_INTRUSIVE(StructName, Variables, ...), then you add that struct as a member to the main Config struct and add it to its respective NLOHMANN_DEFINE_TYPE_INTRUSIVE() macro.
