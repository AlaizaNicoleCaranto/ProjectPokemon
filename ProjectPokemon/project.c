#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of the Pokemon Structure
struct Pokemon
{
    int id;                // Unique ID of the Pokemon
    char name[30];         // Pokemon Name (max 29 chars + null terminator)
    char type[20];         // Pokemon Type (max 19 chars + null terminator)
    int hp;                // Hit Points (HP)
    int attack;            // Attack Stat value
    int defense;           // Defense Stat value
    char description[100]; // Description of the Pokemon (max 99 chars + null terminator)
};

// Prints a line of characters for visual section separation
void printLine(char ch, int length)
{
    for (int i = 0; i < length; i++)
        putchar(ch);
    putchar('\n');
}

// Clears the Console Screen
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix/Linux/Mac
#endif
}

// Check If A Pokemon ID Already Exists In The List To Prevent Duplicates
int isDuplicateID(struct Pokemon list[], int count, int id)
{
    for (int duplicate = 0; duplicate < count; duplicate++)
    {
        if (list[duplicate].id == id)
            return 1; // Duplicate Found
    }
    return 0; // No Duplicate Found
}

// Prompt User And Read a Positive Integer With Validation Loop Until Correct Input Is Given
int getValidatedInt(const char *message)
{
    int value;
    while (1)
    {
        printf("%s", message);

        // scanf Returns Number of Successful Assignments
        if (scanf("%d", &value) == 1 && value > 0)
        {
            while (getchar() != '\n')
                ;         // Clear Remaining Input Buffer
            return value; // Valid Positive Integer
        }
        else
        {
            clearScreen();
            printLine('-', 90);
            printf(">>>>>>>>>>>>  \t\tOops! Please Enter A Valid Positive Number.\t      <<<<<<<<<<<<\n");
            printLine('-', 90);
            while (getchar() != '\n'); // Clear Buffer On Invalid Input
        }
    }
}

// Prompt User and Read a String Input Safely to Destination Buffer with Max Length
// Removes Trailing Newline If Present
void getValidatedString(char *destination, int maxlength, const char *message)
{
    printf("%s", message);
    fgets(destination, maxlength, stdin);

    // Replace Trailing Newline with Null Terminator, If Present
    size_t len = strlen(destination);
    if (len > 0 && destination[len - 1] == '\n')
        destination[len - 1] = '\0';
}

// View All Pokemon Currently Loaded In The List
void viewPokemonList(struct Pokemon list[], int count)
{
    if (count == 0)
    {
        printf("\n");
        printLine('-', 90);
        printf(">>>>>>>>>>>>\t            There Are No Pokemon In The List Yet.             <<<<<<<<<<<<\n");
        printLine('-', 90);
        return;
    }

    clearScreen();
    printLine('=', 139);
    printf("<<<<<<<<<<<<<<<<<<\t\t\t\t\t     \tPOKEMON LIST          \t\t\t\t\t>>>>>>>>>>>>>>>>>>>\n");
    printLine('=', 139);
    printf("ID   | Name                 | Type            | HP    | Attack | Defense | Description\n");
    printLine('-', 139);
    for (int i = 0; i < count; i++)
    {
        printf("%-4d | %-20s | %-15s | %-5d | %-6d | %-7d | %s\n",
               list[i].id, list[i].name, list[i].type,
               list[i].hp, list[i].attack, list[i].defense,
               list[i].description);
        printLine('-', 139);
    }
    printLine('=', 139);
}

// Load Pokemon list From 'pokemon_list.csv' Into List[]
// Updates Count With Number of Pokemon Loaded
void loadPokemonList(struct Pokemon list[], int *count)
{
    FILE *file = fopen("pokemon_list.csv", "r");
    if (!file)
    {
        printLine('-', 90);
        printf(">>>>>>>>>>>>  \t\tOops! File 'pokemon_list.csv' Not Found.\t      <<<<<<<<<<<<\n"
               ">>>>>>>>>>>>  \t\tPlease Create The File With Pokemon Data.\t      <<<<<<<<<<<<\n");
        printLine('-', 90);
        *count = 0;
        return;
    }

    *count = 0;
    // Read Lines Formatted As: id,name,type,hp,attack,defense,description
    // Using Fixed Sizes According to Struct Field Lengths
    while (fscanf(file, "%d,%29[^,],%19[^,],%d,%d,%d,%99[^\n]\n",
                  &list[*count].id, list[*count].name, list[*count].type,
                  &list[*count].hp, &list[*count].attack, &list[*count].defense,
                  list[*count].description) == 7)
    {
        (*count)++;
        if (*count >= 100) // Safety: Prevent Overflow Beyond List Size
            break;
    }
    fclose(file);
}

// Save Current Pokemon List to 'pokemon_list.csv'
void savePokemonList(struct Pokemon list[], int count)
{
    FILE *file = fopen("pokemon_list.csv", "w");
    if (!file)
    {
        printLine('-', 90);
        printf(">>>>>>>>>>>>  \t\tUh Oh! Unable To Save 'pokemon_list.csv'. Try Again.\t      <<<<<<<<<<<<\n");
        printLine('-', 90);
        return;
    }

    // Write Each Pokemon as CSV Line
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n",
                list[i].id, list[i].name, list[i].type,
                list[i].hp, list[i].attack, list[i].defense,
                list[i].description);
    }
    fclose(file);
}

// Add A New Pokemon To List After Checking For Duplicate ID and Validating Inputs
void addPokemon(struct Pokemon list[], int *count)
{
    clearScreen();
    printLine('=', 90);
    printf("<<<<<<<<<<<< \t\t         ADD NEW POKEMON TO THE LIST                   >>>>>>>>>>>\n");
    printLine('=', 90);

    // Prompt User For Unique ID
    int newID = getValidatedInt("Enter A Unique Pokemon ID (A Positive Whole Number): ");
    printLine('-', 90);

    // Check If ID Already Exists To Prevent Duplicates
    if (isDuplicateID(list, *count, newID))
    {
        printLine('-', 90);
        printf(">>>>>>>>>>>>  \t\t\tOops! Pokemon ID Already Exists.              <<<<<<<<<<<<\n");
        printLine('-', 90);
        return;
    }

    // Check If List Capacity Reached
    if (*count >= 100)
    {
        printLine('-', 90);
        printf(">>>>>>>>>>>>   \t\tSorry, Pokemon List Is Full. Cannot Add More.      <<<<<<<<<<<<\n");
        printLine('-', 90);
        return;
    }

    // Fill New Pokemon Details
    list[*count].id = newID;
    getValidatedString(list[*count].name, 30, "Enter Pokemon Name (30 Chars): ");
    getValidatedString(list[*count].type, 20, "Enter Pokemon Type (30 Chars): ");
    list[*count].hp = getValidatedInt("Enter HP (Positive Whole Integer): ");
    list[*count].attack = getValidatedInt("Enter Attack (Positive Whole Integer): ");
    list[*count].defense = getValidatedInt("Enter Defense (Positive Whole Integer): ");
    getValidatedString(list[*count].description, 100, "Enter Pokemon Description (100 Chars): ");

    (*count)++; // Increase Pokemon Count

    // Save Changes To File Immediately
    savePokemonList(list, *count);

    printLine('-', 90);
    printf(">>>>>>>>>>>>    Nice! '%s' Has Been Added To The Pokemon List.  <<<<<<<<<<<<\n", list[*count - 1].name);
    printLine('-', 90);
}

// Update Details For Existing Pokemon By ID
void updatePokemon(struct Pokemon list[], int count)
{
    clearScreen();
    printLine('=', 90);
    printf("<<<<<<<<<<<< \t\t       UPDATE EXISTING POKEMON DETAILS                 >>>>>>>>>>>\n");
    printLine('=', 90);

    // Prompt User For Pokemon ID To Update
    int id = getValidatedInt("Enter Pokemon ID To Update (See List For The ID): ");
    printLine('-', 90);

    // Find Pokemon By ID
    for (int i = 0; i < count; i++)
    {
        if (list[i].id == id)
        {
            // Get New Inputs For Fields
            getValidatedString(list[i].name, 30, "Enter New Pokemon Name (30 Chars): ");
            getValidatedString(list[i].type, 20, "Enter New Pokemon Type (30 Chars): ");
            list[i].hp = getValidatedInt("Enter New HP (Positive Whole Integer): ");
            list[i].attack = getValidatedInt("Enter New Attack (Positive Whole Integer): ");
            list[i].defense = getValidatedInt("Enter New Defense (Positive Whole Integer): ");
            getValidatedString(list[i].description, 100, "Enter New Pokemon Description (100 Chars): ");

            savePokemonList(list, count);
            printLine('-', 90);
            printf(">>>>>>>>>>>>\t    Great! '%s' Has Been Updated Successfully.\t      <<<<<<<<<<<<\n", list[i].name);
            printLine('-', 90);
            return;
        }
    }

    // If ID Not Found
    printLine('-', 90);
    printf(">>>>>>>>>>>>\t\t   No Pokemon Found With ID %d. Try Again.            <<<<<<<<<<<<\n", id);
    printLine('-', 90);
}

// Delete Pokemon From List By ID; Shifts List Elements Down
void deletePokemon(struct Pokemon list[], int *count)
{
    clearScreen();
    printLine('=', 90);
    printf("<<<<<<<<<<<< \t\t        DELETE A POKEMON FROM THE LIST                 >>>>>>>>>>>\n");
    printLine('=', 90);

    // Prompt User For Id To Delete
    int id = getValidatedInt("        \t\tEnter Pokemon ID to Delete (See List For The ID): ");
    printLine('-', 90);

    // Find Index To Remove
    for (int i = 0; i < *count; i++)
    {
        if (list[i].id == id)
        {
            // Store Removed Name For Message
            char removedName[30];
            strcpy(removedName, list[i].name);

            // Shift Elements Down To Fill Gap
            for (int j = i; j < *count - 1; j++)
            {
                list[j] = list[j + 1];
            }
            (*count)--;

            // Save Updated List To File
            savePokemonList(list, *count);
            printLine('-', 90);
            printf(">>>>>>>>>>>>\t     '%s' Has Been Removed From The Pokemon List.          <<<<<<<<<<<<\n", removedName);
            printLine('-', 90);
            return;
        }
    }
    printLine('-', 90);
    printf(">>>>>>>>>>>>\t            No Pokemon Found With ID %d. Try Again.            <<<<<<<<<<<<\n", id);
    printLine('-', 90);
}

// View User's Team By Reading From The 'my_team.csv' File Directly
void viewTeam()
{
    FILE *file = fopen("my_team.csv", "r");
    if (!file)
    {
        printLine('-', 90);
        printf(">>>>>>>>>>>>\t No Team Found. Add Pokemon To Your Team Or Load A Saved One.    >>>>>>>>>\n");
        fflush(stdout); // Ensure The Output Is Flushed
        printLine('-', 90);
        return;
    }

    struct Pokemon teamMember;
    clearScreen();
    printLine('=', 139);
    printf("<<<<<<<<<<<<<<<<<<\t\t\t\t\t     \tPOKEMON TEAM          \t\t\t\t\t>>>>>>>>>>>>>>>>>>>\n");
    printLine('=', 139);
    printf("ID   | Name                 | Type            | HP  | Attack | Defense | Description\n");
    printLine('-', 139);

    // Read And Display Each Pokemon In The Team
    while (fscanf(file, "%d,%29[^,],%19[^,],%d,%d,%d,%99[^\n]\n",
                  &teamMember.id, teamMember.name, teamMember.type,
                  &teamMember.hp, &teamMember.attack, &teamMember.defense,
                  teamMember.description) == 7)
    {
        printf("%-4d | %-20s | %-15s | %-3d | %-6d | %-7d | %-30s\n",
               teamMember.id, teamMember.name, teamMember.type,
               teamMember.hp, teamMember.attack, teamMember.defense,
               teamMember.description);
        printLine('-', 139);
    }
    printLine('=', 139);
    fclose(file);
}

// Add A Pokemon To User's Team After Validating Duplicates And Existence In Master List
void addPokemonToTeam(struct Pokemon list[], int count, struct Pokemon team[], int *teamCount)
{
    clearScreen();
    printLine('=', 90);
    printf("<<<<<<<<<<<<\t\t           ADD POKEMON TO YOUR TEAM                   >>>>>>>>>>>>\n");
    printLine('=', 90);
    int id = getValidatedInt("       \t\t\tEnter Pokemon ID To Add To Your Team: ");
    printLine('-', 90);

    // Check If Pokemon Is Already In Team
    for (int i = 0; i < *teamCount; i++)
    {
        if (team[i].id == id)
        {
            printf(">>>>>>>>>>>>\t\t    '%s' Is Already In Your Team.               <<<<<<<<<<<<\n", team[i].name);
            printLine('-', 90);
            printf("Press Enter To Continue...");
            getchar(); // Wait For User Input
            return;
        }
    }
    // Check If We Can Add More Pokemon
    if (*teamCount >= 100)
    {
        printf(">>>>>>>>>>>>\t    Your Team Is Full! Remove A Pokemon Before Adding More.           <<<<<<<<<<<<\n");
        printLine('-', 90);
        printf("Press Enter To Continue...");
        getchar(); // Wait For User Input
        return;
    }
    // Find Pokemon In Master List And Add
    for (int i = 0; i < count; i++)
    {
        if (list[i].id == id)
        {
            team[*teamCount] = list[i]; // Add To Team Array
            (*teamCount)++;

            // Append To Team File
            FILE *file = fopen("my_team.csv", "a");
            if (!file)
            {
                printf(">>>>>>>>>>>>\t          Uh Oh!Couldn't Save Your Team To File.             <<<<<<<<<<<<\n");
                printLine('-', 90);
                printf("Press Enter To Continue...");
                getchar(); // Wait For User Input
                return;
            }
            fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n",
                    list[i].id, list[i].name, list[i].type,
                    list[i].hp, list[i].attack, list[i].defense,
                    list[i].description);
            fclose(file);
            printf(">>>>>>>>>>>\t    Nice! '%s' Was Added To Your Team Successfully.     <<<<<<<<<<\n", list[i].name);
            printLine('-', 90);
            printf("Press Enter To Continue...");
            getchar(); // Wait For User Input
            return;
        }
    }

    // Not Found In Master List
    printf(">>>>>>>>>>>>\t          Pokemon ID Not Found In The Master List.            <<<<<<<<<<<<\n");
    printLine('-', 90);
    printf("Press Enter To Continue...");
    getchar(); // Wait For User Input
}

// Remove A Pokemon From User's Team By ID And Update The Team File
void removePokemonFromTeam(struct Pokemon team[], int *teamCount)
{
    clearScreen();
    printLine('=', 90);
    printf("<<<<<<<<<<<< \t\t        REMOVE POKEMON FROM YOUR TEAM                 >>>>>>>>>>>\n");
    printLine('=', 90);
    int id = getValidatedInt("        \t\tEnter Pokemon ID To Remove From Your Team:  ");
    printLine('-', 90);
    int foundIndex = -1; // Initialize To Track If ID Is Found

    // Find Pokemon To Remove
    for (int i = 0; i < *teamCount; i++)
    {
        if (team[i].id == id)
        {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1)
    {
        printf(">>>>>>>>>>>> \t             Pokemon ID Not Found In Your Team.               <<<<<<<<<<<<\n");
        printLine('-', 90);
        printf("Press Enter To Continue...");
        getchar(); // Wait For User Input
        return;
    }
    // Shift Remaining Pokemon To Remove Entry
    for (int i = foundIndex; i < *teamCount - 1; i++)
    {
        team[i] = team[i + 1];
    }
    (*teamCount)--;
    // Rewrite Team File With Updated Contents
    FILE *file = fopen("my_team.csv", "w");
    if (!file)
    {
        printLine('-', 90);
        printf(">>>>>>>>>>>>\tUh Oh! Couldn't Update Your Team File. Please Try Again Later.    <<<<<<<<<<\n");
        printLine('-', 90);
        printf("Press Enter To Continue...");
        getchar(); // Wait For User Input
        return;
    }
    for (int i = 0; i < *teamCount; i++)
    {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n",
                team[i].id, team[i].name, team[i].type,
                team[i].hp, team[i].attack, team[i].defense,
                team[i].description);
    }
    fclose(file);
    printf(">>>>>>>>>>>>\t\t   Bye-Bye! '%s' Removed From Your Team.         <<<<<<<<<<\n", team[foundIndex].name);
    printLine('-', 90);
    printf("Press Enter To Continue...");
    getchar(); // Wait For User Input
}

// Load User's Team From 'my_team.csv' File
void loadTeam(struct Pokemon team[], int *teamCount, int showMessage)
{
    FILE *file = fopen("my_team.csv", "r");
    if (!file)
    {
        // If the file does not exist, create it
        file = fopen("my_team.csv", "w");
        if (!file)
        {
            if (showMessage)
            {
                clearScreen();
                printLine('=', 90);
                printf(">>>>>>>>>>>> \tUh Oh!Unable To Create Team File. Please Check Permissions!\t <<<<<<<<<<<<\n");
                printLine('=', 90);
                printf("Press Enter To Continue...");
                getchar();
            }
            *teamCount = 0;
            return;
        }
        fclose(file);   // Close The Newly Created File
        *teamCount = 0; // Set Team Count To 0 Since The Team Is Empty
        return;         // Exit The Function
    }

    *teamCount = 0;
    while (fscanf(file, "%d,%29[^,],%19[^,],%d,%d,%d,%99[^\n]\n",
                  &team[*teamCount].id, team[*teamCount].name, team[*teamCount].type,
                  &team[*teamCount].hp, &team[*teamCount].attack, &team[*teamCount].defense,
                  team[*teamCount].description) == 7)
    {
        (*teamCount)++;
        if (*teamCount >= 100)
            break;
    }
    fclose(file);
    if (showMessage)
    {
        printLine('=', 90);
        if (*teamCount > 0)
        {
            printf(">>>>>>>>>>>> \t\t  Team Loaded Successfully With %d Pokemon!              <<<<<<<<<<\n", *teamCount);
        }
        else
        {
            printf(">>>>>>>>>>>> \t\t\tTeam File Is Empty Or Corrupted!                <<<<<<<<<<\n");
        }
        printLine('=', 90);
        printf("Press Enter To Continue...");
        getchar();
    }
}

// Menu For Managing Master Pokemon List
void managePokemonList(struct Pokemon list[], int *count)
{
    int choice;
    do
    {
        clearScreen();
        printLine('=', 90);
        printf("<<<<<<<<<<<<\t\t\t    Manage Pokemon List\t\t\t      >>>>>>>>>>>>\n");
        printLine('=', 90);
        if (*count == 0)
        {
            printf(">>>>>>>>>>>> \t\tNo Pokemon Available. PLease Add Some First.\t      <<<<<<<<<<<<\n");
            printLine('-', 90);
        }
        else
        {
            printf(">>>>>>>>>>>>     \t\tCurrent Pokemon Count: %d\t\t      <<<<<<<<<<<<\n", *count);
            printLine('-', 90);
        }

        printf("        \t\t\t1. View All Pokemon\n");
        printf("        \t\t\t2. Add a New Pokemon\n");
        printf("        \t\t\t3. Update Existing Pokemon\n");
        printf("        \t\t\t4. Delete a Pokemon\n");
        printf("        \t\t\t5. Save Changes\n");
        printf("        \t\t\t6. Back to Main Menu\n");

        while (1)
        {
            printf("        \t\t\tEnter your choice (1-6): ");
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 6)
            {
                while (getchar() != '\n');
                break;
            }
            else
            {
                printLine('-', 90);
                printf(">>>>>>>>>>>>\t     Oops! Please Enter A Valid Choice Between 1 and 6.       <<<<<<<<<<<<\n");
                printLine('-', 90);
                while (getchar() != '\n');
            }
        }

        switch (choice)
        {
        case 1:
            viewPokemonList(list, *count);
            break;
        case 2:
            addPokemon(list, count);
            break;
        case 3:
            updatePokemon(list, *count);
            break;
        case 4:
            deletePokemon(list, count);
            break;
        case 5:
            savePokemonList(list, *count);
            printLine('-', 90);
            printf(">>>>>>>>>>>>\t\t         Changes Saved Successfully!                  <<<<<<<<<<<<\n");
            printLine('-', 90);
            break;
        case 6:
            clearScreen();
            return; // Exit To Main Menu
        }
        printf("Press Enter To Continue...");
        getchar(); // Pause For User
    } while (1);
}

// Menu For Managing User's Pokemon Team
void manageTeam(struct Pokemon list[], int listCount)
{
    struct Pokemon team[100];
    int teamCount = 0;
    loadTeam(team, &teamCount, 0); // Initial Silent Load
    int choice;
    do
    {
        clearScreen();
        printLine('=', 90);
        printf("<<<<<<<<<<<<\t\t\t    Manage Your Team\t\t\t       >>>>>>>>>>>\n");
        printLine('=', 90);
        printf("        \t\t\t1. View Team\n");
        printf("        \t\t\t2. Add A Pokemon To Team\n");
        printf("        \t\t\t3. Remove A Pokemon From Team\n");
        printf("        \t\t\t4. Load Team\n");
        printf("        \t\t\t5. Save Team\n");
        printf("        \t\t\t6. Back To Main Menu\n");

        while (1)
        {
            printf("        \t\t\tEnter Your Choice (1-6): ");
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 6)
            {
                while (getchar() != '\n');
                break;
            }
            else
            {
                printLine('-', 90);
                printf(">>>>>>>>>>>>\t     Oops! Please Enter A Valid Choice Between 1 and 6.       <<<<<<<<<<<<\n");
                printLine('-', 90);
                while (getchar() != '\n');
            }
        }
        switch (choice)
        {
        case 1:
            viewTeam();
            printf("Press Enter To Continue...");
            getchar();
            break;
        case 2:
            addPokemonToTeam(list, listCount, team, &teamCount);
            break;
        case 3:
            removePokemonFromTeam(team, &teamCount);
            break;
        case 4:
            loadTeam(team, &teamCount, 1);
            break;
        case 5:
        {
            FILE *file = fopen("my_team.csv", "w");
            if (!file)
            {
                printLine('-', 90);
                printf(">>>>>>>>>>>>\t\t         Couldn't Save Your Team.                  <<<<<<<<<<<<\n");
                printLine('-', 90);
                printf("Press Enter To Continue...");
                getchar();
                break;
            }
            for (int i = 0; i < teamCount; i++)
            {
                fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n",
                        team[i].id, team[i].name, team[i].type,
                        team[i].hp, team[i].attack, team[i].defense,
                        team[i].description);
            }
            fclose(file);
            printLine('-', 90);
            printf(">>>>>>>>>>>>\t\t          Team Saved Successfully.                    <<<<<<<<<<<<\n");
            printLine('-', 90);
            printf("Press Enter To Continue...");
            getchar();
            break;
        }
        case 6:
            clearScreen();
            return;
        }
    } while (1);
}

// Main Menu That Drives The Program
void mainMenu(struct Pokemon list[], int *listCount)
{
    int choice;
    do
    {
        printLine('=', 90);
        printf("<<<<<<<<<<<<\t\t\t    POKEMON PROJECT\t\t\t       >>>>>>>>>>>\n");
        printLine('=', 90);
        printf("        \t\t\t1. Manage Pokemon List\n");
        printf("        \t\t\t2. Manage Your Team\n");
        printf("        \t\t\t3. Exit\n");

        while (1)
        {
            printf("        \t\t\tEnter Your Choice (1-3): ");
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3)
            {
                while (getchar() != '\n');  // Clear Buffer
                break; // Valid Input, Exit Loop
            }
            else
            {
                printLine('-', 90);
                printf(">>>>>>>>>>>>\t     Oops! Please Enter A Valid Choice Between 1 And 3.       <<<<<<<<<<<<\n");
                printLine('-', 90);
                while (getchar() != '\n'); // Clear Invalid Input
            }
        }

        switch (choice)
        {
        case 1:
            managePokemonList(list, listCount);
            break;
        case 2:
            manageTeam(list, *listCount);
            break;
        case 3:
            clearScreen();
            printLine('=', 90);
            printf("<<<<<<<<<<            \t\tTHANK YOU FOR TRAINING WITH US!                  >>>>>>>>>"
                   "\n<<<<<<<<<<  MAY YOUR JOURNEY BE FILLED WITH EPIC BATTLES AND LEGENDARY POKEMON!  >>>>>>>>>\n");
            printLine('=', 90);
            printf("\n");
            return; // Exit Program
        }
    } while (1);
}

// Main Function
int main()
{
    struct Pokemon list[100]; // Master Pokemon List Storage
    int listCount = 0;        // Number Of Pokemon Loaded

    clearScreen();
    printLine('=', 90);
    printf("<<<<<<<<<<<<          \t\tWELCOME, POKEMON TRAINER! \t\t       >>>>>>>>>>>"
           "\n<<<<<<<<<<<<  PREPARE TO BUILD YOUR ULTIMATE TEAM AND EMBARK ON AN ADVENTURE!  >>>>>>>>>>>\n");
    printLine('=', 90); // Print Another Line For Visual Separation

    loadPokemonList(list, &listCount); // Load Pokemon List From File
    mainMenu(list, &listCount);        // Start Main Program Menu
    return 0;
}
