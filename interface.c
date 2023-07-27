#include <stdio.h>
#ifdef __unix__ // Unix/Linux-specific header file
    #include <unistd.h> 
    #include <curses.h>
#elif defined(__WIN32__) || defined(__WIN64__) // Windows-specific header file
    #include <windows.h> 
    #include <conio.h>
#endif
#define SIZE 16

/*void clearConsole() {
    #ifdef __unix__
        initscr();
        clear();
        refresh();
        endwin();
    #elif defined(__WIN32__) || defined(__WIN64__)
        clrscr();
    #endif
    
    return;
}*/

void mainMenu() {
    int option;
    
    char* mainInterface = 
"##### Puzzle15 by Juan Mulet #####\n\n\
             MAIN MENU\n\n\
Press a number (0-3) to move through the menu:\n\
1 - Start New Game\n\
2 - Highscores\n\
3 - Puzzle Variants\n\
0 - Exit Game\n\n";

    printf("%s", mainInterface);
    
    do {
        printf("Move to: ");
        scanf("%d", &option);
    } while (option > 3 || option < 0);

    if (option == 1) {
        //clearConsole();
        playMenu();
    } else if (option == 2) {
        //clearConsole();
        scoreMenu();
    } else if (option == 3) {
        //clearConsole();
        variantMenu();
    } else {
        //clearConsole();
        printf("\n¡Hope you had fun!\n");
        #ifdef __unix__
             sleep(1.7);
        #elif defined(__WIN32__) || defined(__WIN64__)
            Sleep(1700);
        #endif
        printf("\n¡Good Bye!\n");
        #ifdef __unix__
             sleep(1);
        #elif defined(__WIN32__) || defined(__WIN64__)
            Sleep(1000);
        #endif
        return;
    }
    
    return;
}

void playMenu() {
    int option;
    char* playInterface =
"##### Puzzle15 by Juan Mulet #####\n\n\
              NEW GAME\n\n\
Press a number (0-4) to move through the menu:\n\
1 - Normal Game (1 round, no bets, no timer)\n\
2 - Betting Game (1 round, bet total moves, no timer)\n\
3 - Betting Game Infinite (keep playing until you lose, bet total moves, no timer)\n\
4 - Full Game (Betting Game Infinite with timer)\n\n\
0 - Go Back\n\n";

    printf("%s", playInterface);
    
    do {
        printf("Move to: ");
        scanf("%d", &option);
    } while (option > 4 || option < 0);
    
    if (option == 1) {
        
    } else if (option == 2) {
        
    } else if (option == 3) {
        
    } else if (option == 4) {
        
    } else {
        //clearConsole();
        mainMenu();
    }
    
    return;
}

void scoreMenu() {
    int option;
    char* scoreInterface =
"##### Puzzle15 by Juan Mulet #####\n\n\
             HIGHSCORES\n\n\
Press a number (0-2) to move through the menu:\n\
1 - Show Highscores\n\
2 - Reset Highscores\n\n\
0 - Go Back\n\n";

    printf("%s", scoreInterface);
    
    do {
        printf("Move to: ");
        scanf("%d", &option);
    } while (option > 2 || option < 0);
    
    if (option == 1) {
        
    } else if (option == 2) {
        
    } else if (option == 3) {
        
    } else if (option == 4) {
        
    } else {
        //clearConsole();
        mainMenu();
    }
    
    return;
}

void variantMenu() {
    int option;
    char* variantInterface =
"##### Puzzle15 by Juan Mulet #####\n\n\
            PUZZLE VARIANTS\n\n\
Press a number (0-3) to move through the menu:\n\
1 - 15 to 1\n\
2 - Vertical\n\
3 - Odd | Evens\n\n\
0 - Go Back\n\n";

    printf("%s", variantInterface);
    
    do {
        printf("Move to: ");
        scanf("%d", &option);
    } while (option > 3 || option < 0);
    
    if (option == 1) {
        
    } else if (option == 2) {
        
    } else if (option == 3) {
        
    } else if (option == 4) {
        
    } else {
        //clearConsole();
        mainMenu();
    }
    
    return;
}

int main() {
    int gameGrid[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    mainMenu();
    

    return 0;
}