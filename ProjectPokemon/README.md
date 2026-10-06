# POKEMON LIST AND TEAM BUILDER PROGRAM

##  PROJECT OVERVIEW

This program allows users to manage a list of Pokemon and build custom teams by performing CRUD operations. 
Data is handled using `.csv` files and structured file I/O in C.
It provides a console-based interface for users to interact with their Pokemon Data, including adding, deleting, updating, and viewing Pokemon in both the list and the user's custom team.
It is designed to be user-friendly, with clear prompts and error handling to guide users through the process.


===========================================================================

## TABLE OF CONTENTS

- [FEATURES](#features)
- [HOW TO RUN THE PROGRAM (Windows)](#how-to-run-the-program-windows)
- [FILE CONTENTS](#file-contents)
- [SCREENSHOTS](#screenshots)
- [TROUBLESHOOTING TIPS](#troubleshooting-tips)
- [NOTES](#notes)

===========================================================================

## FEATURES

- **Manage Pokemon List**: Add, delete, update, and view Pokemon in the list.
- **Manage Team**: Add and remove Pokemon from a custom team, view the team, and save/load the team.
- **File I/O**: Read and write Pokemon data to/from `.csv` files.
- **User-Friendly Interface**: Console-based menu system with clear prompts and error handling.
- **Error Handling**: Validates user input and handles file errors gracefully.
- **Data Persistence**: Changes to the Pokemon list and team are saved to files, allowing for persistent data across program runs.  
- **Cross-Platform Compatibility**: Designed to run on Windows, but can be adapted for other platforms with minor changes.

===========================================================================

## HOW TO RUN THE PROGRAM (Windows)

1. **Open Command Prompt or PowerShell** in the directory containing the files.

2. **Compile The Code** using GCC:
`gcc project.c -o project`
    - If you have MinGW installed, ensure that the `gcc` command is available in your PATH. If not, you may need to specify the full path.
    - If you encounter any errors during compilation, eensure that you have the necessary permissions and that the `project.c` file is in the same directory.
    - If your are using an IDE like Code::Blocks or Visual Studio, you can open the project file and build it directly from there.

3. **Run The Program**:
    `.\project`
    - This will execute the compiled program, and you will see the main menu displayed in thee console.

4. **Follow the On-Screen Prompts** to navigate through the program.
    - You can choose to manage the Pokemon List or your Custom Team.

5. **Exit The Program** by selecting the exit option from the main menu.

6. **Ensure You Have The Required Files**
    - The program requires `pokemon_list.csv` and `my_team.csv` to function correctly.

7. Make sure the following files are in the **same directory** as the compiled executable::
    - `pokemon_list.csv`- Contains the list of all available Pokemon.
    - `my_team.csv` - Stores the user's custom-built Pokemon team.

===========================================================================

## FILE CONTENTS

---------------------------------------------------------------------------
| File              | Description                                         |
|-------------------|-----------------------------------------------------|
| `screenShots`     | Contains Screenshots Of The Program's Output        |
|-------------------|-----------------------------------------------------| 
| `project.c`       | The Main Source Code Of The Program                 |
|-------------------|-----------------------------------------------------| 
| `project.exe`     | Compiled Executable (Windows)                       |               
|-------------------|-----------------------------------------------------| 
| `pokemon_list.csv`| Sample Pokemon Entries (e.g., Name, Type, HP, etc.) |
|-------------------|-----------------------------------------------------| 
| `my_team.csv`     | User's Custom-Built Pokemon Team                    |      
|-------------------|-----------------------------------------------------| 
| `README.md`       | Instructions And Documentation                      |
---------------------------------------------------------------------------

===========================================================================

## PROGRAM SCREENSHOTS

### CODE SNIPPET

![Set Ups And Utilities](screenShots/includes_utilities.png)
![Validation Input](screenShots/validationInput.png)
![View Pokemon](screenShots/viewPokemon.png)
![Load And Save](screenShots/loadAndSave.png)
![Add Pokemon](screenShots/addPokemon.png)
![Update Pokemon](screenShots/updatePokemon.png)
![Delete Pokemon](screenShots/deletePokemon.png)
![View Team](screenShots/viewTeam.png)
![Add To Team](screenShots/addToTeam.png)
![Add To Team Cont.](screenShots/addToTeam_1.png)
![Remove Pokemon](screenShots/removeFromTeam.png)
![Remove Pokemon Cont.](screenShots/removeFromTeam_1.png)
![Load Pokemon To Team](screenShots/loadTeam.png)
![Manage Pokemon List](screenShots/managePokemonList.png)
![Manage Pokemon List Cont.](screenShots/managePokemonList_1.png)
![Manage Team](screenShots/manageTeam.png)
![Manage Team Cont.](screenShots/manageTeam_1.png)
![Main Menu](screenShots/mainMenu.png)
![Main Function](screenShots/mainFunction.png)

### OUTPUT

![Main Menu Output](screenShots/output_mainMenuSystem.png)
![Manage Pokemon](screenShots/output_managePokemonListMenu.png)
![Manage Team](screenShots/output_manageTeamMenu.png)
![Add Pokemon To The List](screenShots/output_addPokemon.png)
![Delete Pokemon From The List](screenShots/output_deletePokemon.png)
![View Pokemon List](screenShots/output_viewPokemonList.png)
![Update Pokemon From The List](screenShots/output_updatePokemon.png)
![Save Changes](screenShots/output_saveChanges.png)
![Add Pokemon To The Team](screenShots/output_addToTeam.png)
![Remove Pokemon From The Team](screenShots/output_removeFromTeam.png)
![View Team](screenShots/output_viewTeam.png)
![Load Team](screenShots/output_loadTeam.png)
![Save Team](screenShots/output_saveTeam.png)
![Exit Program](screenShots/output_exitMessage.png)

---------------------------------------------------------------------------

###  ERROR HANDLING

![Main Menu Invalid Input](screenShots/mainMenu_Invalid_Input.png)
![Manage Pokemon List Invalid Input](screenShots/managePokemon_Invalid_Input.png)
![Manage Team Invalid Input](screenShots/manageTeam_Invalid_Input.png)
![View Empty List](screenShots/viewList_emptyList.png)
![Add Pokemon Invalid Input](screenShots/addPokemon_Invalid_Input.png)
![Add Pokemon ID Already Exists](screenShots/addPokemon_pokemonId_alreadyExists.png)
![Delete Pokemon Invalid Input](screenShots/deletePokemon_Invalid_Input.png)
![Delete Pokemon Pokemon ID Not Found](screenShots/deletePokemon_pokemonId_notFound.png)
![No Pokemon List File](screenShots/pokemonList_notFound.png)
![No Pokemon Available](screenShots/pokemonList_pokemon_unavailable.png)
![Update Pokemon Invalid Input](screenShots/updatePokemon_Invalid_Input.png)
![Update Pokemon Pokemon ID Not Found](screenShots/updatePokemon_pokemonId_notFound.png)
![Add To Team Invalid Input](screenShots/addToTeam_Invalid_Input.png)
![Add To Team Pokemon ID Not Found](screenShots/addToTeam_pokemonId_notFound.png)
![Remove From Team Pokemon Invalid Input](screenShots/removeFromTeam_Invalid_Input.png)
![Remove From Team Pokemon Pokemon ID Not Found](screenShots/removeFromTeam_pokemonId_notFound.png)
![Empty Team](screenShots/loadTeam_Empty_Message.png)

===========================================================================

## TROUBLESHOOTING TIPS
---------------------------------------------------------------------------

- **"gcc Is Not Recognized"**: Make sure GCC (from MinGW or another distribution) is installed and added to your system PATH.
- **Blank Screen or File Errors**: Confirm that `pokemon_list.csv` and `my_team.csv` are in the same folder as the compiled `.exe`.
- **Compilation Warnings**: Don't ignore them! They may point to logic issues or missing headers.
- **File Not Found Errors**: Ensure the `.csv` files are correctly named and located in the same directory as the executable.
- **Invalid Input Handling**: If you enter an invalid option, the program will prompt you to try again. Follow the prompts carefully.
- **Data Not Saving**: Ensure you have write permissions in the directory where the program is running. If the program crashes or exits unexpectedly, it may not save changes to the files.
- **Team Management Issues**: If you encounter issues with adding or removing Pokemon from your team, ensure that the Pokemon ID exists in the list and that you are following the prompts correctly.
- **File Format Issues**: Ensure that the `.csv` files are formatted correctly. Each line should contain the Pokemon's ID, Name, Type, HP, Attack, Defense, and Description separated by commas. For example:

  ```
  4,Gengar,Ghost/Poison,60,65,60,A Mischievous Pokemon That Lurks In The Shadows And Causes Nightmares.
  5,Alakazam,Psychic,55,50,45,A Highly Intelligent Pokemon With Powerful Psychic Abilities.
  ```
- **Unexpected Behavior**: If the program behaves unexpectedly, try recompiling it or checking for any syntax errors in the code.
- **Cross-Platform Issues**: If you are trying to run the program on a non-Windows platform, you may need to adjust file paths or input methods. The code is designed to be cross-platform, but some minor adjustments may be necessary.

===========================================================================

##  NOTES
---------------------------------------------------------------------------
- The code uses `fscanf()` and `fprintf()` for reading and writing structured `.csv` files.
- File validation and input handling are implemented to ensure reliability.
- The program is designed to be user-friendly and provides clear prompt messages for each operation.
- The program is written in C and is intended to be compiled with a C compiler like GCC.
- The program is designed to be cross-platform, but the provided instructions are specifically for Windows users.
- The program is structured to allow easy modifications and additions, such as new features or additional Pokemon types.
- The program is a good example of file handling, data structures, and user interface design in C.
- The program can be used as a learning tool for beginners to understand file I/O, data structures, and basic C programming concepts.
- The program can be adapted for other platforms with minor changes, such as using different file paths or handling different console input methods.
- The program is a fun and interactive way to manage Pokemon data and build custom teams, making it suitable for fans of the Pokemon franchise and C programming enthusiasts alike.
- The program is a great starting point for anyone interested in learning C programming, file handling, and data management.

===========================================================================