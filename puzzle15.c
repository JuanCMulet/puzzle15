#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef __unix__ // Unix/Linux-specific header file
    #include <unistd.h> 
    #include <curses.h>
    #include <sys/time.h>
#elif defined(__WIN32__) || defined(__WIN64__) // Windows-specific header file
    #include <windows.h> 
#endif

#define SIZE 16
#define EMPTY -1

void clearConsole() {
    #ifdef __unix__
        initscr();
        clear();
        refresh();
        endwin();
    #elif defined(__WIN32__) || defined(__WIN64__)
        system("cls");
    #endif

}

int validInput() {
    int input;
    char buffer[100];
    int validInput = 0;

    while (!validInput) {
        printf("Your input: ");

        // Read user input as a string using fgets
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input.\n");
            return 1;
        }

        // Attempt to convert the string to an integer using sscanf
        if (sscanf(buffer, "%d", &input) == 1) {
            // Input was a valid integer
            validInput = 1;
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
        }
    }

    return input;
}

double getTimeUnix(struct timeval start, struct timeval end) {
    //Function in Unix to calculate the elapsed while inside the program.
    return (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
}

double getTimeWindows(SYSTEMTIME start, SYSTEMTIME end) {
    //Function in Windows to calculate the elapsed while inside the program.
    FILETIME ftStart, ftEnd;
    ULARGE_INTEGER uliStart, uliEnd;

    SystemTimeToFileTime(&start, &ftStart);
    SystemTimeToFileTime(&end, &ftEnd);

    uliStart.LowPart = ftStart.dwLowDateTime;
    uliStart.HighPart = ftStart.dwHighDateTime;
    uliEnd.LowPart = ftEnd.dwLowDateTime;
    uliEnd.HighPart = ftEnd.dwHighDateTime;

    return (double)(uliEnd.QuadPart - uliStart.QuadPart) / 10000000.0;
}

int emptySquareRow(int index) {
    int row;
    
    //Simple check to find in wich row of the 4x4 grid the blank space is located
    if (index > 11) {
        row = 4;
    } else if (index > 7) {
        row = 3;
    } else if (index > 3) {
        row = 2;
    } else {
        row = 1;
    }
    
    return row;
    
}

//Many grid starts are not viable so we first check if we can solve the puzzle or not
int viableGrid(int grid[], int size) {
    
    int row;
    int totalInversions = 0;
    
    //We read the array looking for inversions and check the position of the blank space
    for (int i = 0; i < size-1; i++) {
        if (grid[i] == 16) {
            /*We skip number 16 (blank space) from the inversion counting and pass it to another function
            to find in wich row its located.*/
            row = emptySquareRow(i);
            continue;
        }
        for (int j = i+1; j < size; j++) {
            /*  
                If the number we are looking at (grid[i]) is bigger than the next number in the array (grid[j]) 
                we call that an inversion. We then count the total inversions in the grid.
            */
            if (grid[i] > grid[j]) {
                totalInversions++;
            }
        }
    }
    
    /*  
        To know if a grid game is viable we add the total inversions and the row in wich the blank space is
        located. If the sum is an even number then its viable, otherwise its not. For a better explanation on how
        this works visit: 
        https://www.youtube.com/watch?v=YI1WqYKHi78&ab_channel=Numberphile
        https://mathworld.wolfram.com/15Puzzle.html*/ 
    
    printf("\n\n El total de inversiones es: %d", totalInversions);
    printf("\n El espacio vacío se encuentra en la fila: %d", row);
    if ( (totalInversions+row)%2 == 0 ) {
        printf("\n El juego es posible de resolver");
        return 1;
    } else {
        printf("\n El juego NO es posible de resolver");
        return 0;
    }
    
    
}

void showGrid(int grid[], int size) {
    printf("\n\n\n");
    for(int i = 0; i < size; i++) {
        if (grid[i] == 16) {
            printf("|    ");
        } else {
            printf("| %2d ", grid[i]);
        }
        if((i+1) % 4 == 0) {
            printf("|");
            printf("\n");
            printf(" -------------------\n");
        }
    }
    printf("\nW - UP | A - LEFT | S - DOWN | D - RIGHT\nE - Exit game\n\n");
}

void swapSpace(int* grid, int size, int i, int j) { // Swaps the numbers in the grid
    int temp = grid[i];
    grid[i] = grid[j];
    grid[j] = temp;
}

void randomizeGrid(int* grid, int size) {
    //We generate a random seed for it to be fully random.
    srand(time(NULL));
    
    //We move in the array from end to start
    for(int i = size-1; i > 0; i--) {
        //We generate a random index between 0 and i, including i.
        int j = rand() % (i + 1);
        
        //We perform a simple swap using a temp variable
        swapSpace(grid, size, i, j);
    }
    
}

int moveSpace(int* grid, int size) {
    int loc;
    char option;
    int check;
    
    for (int i = 0; i < size ; i++) { // Looks for the empty square and asigns its location to loc
        if (grid[i] == 16) {
            loc = i;
        }
    }
    
    do {
        printf("Move to: ");
        scanf(" %c", &option);
        
        switch (option) { // Logic for keyboard movement.
            case 'W':
            case 'w':
                //Safetey guards when trying to move outside the grid.
                if (loc == 0 || loc == 1 || loc == 2 || loc == 3) {
                    printf("\nInvalid move\n");
                    check = 0;
                } else {
                    swapSpace(grid, size, loc, loc-4);
                    check = 1;
                }
                break;
                
            case 'A':
            case 'a':
                if (loc == 0 || loc == 4 || loc == 8 || loc == 12) {
                    printf("\nInvalid move\n");
                    check = 0;
                } else {
                    swapSpace(grid, size, loc, loc-1);
                    check = 1;
                }
                break;
                
            case 'S':
            case 's':
                if (loc == 12 || loc == 13 || loc == 14 || loc == 15) {
                    printf("\nInvalid move\n");
                    check = 0;
                } else {
                    swapSpace(grid, size, loc, loc+4);
                    check = 1;
                }
                break;
            
            case 'D':
            case 'd':
                if (loc == 3 || loc == 7 || loc == 11 || loc == 15) {
                    printf("\nInvalid move\n");
                    check = 0;
                } else {
                    swapSpace(grid, size, loc, loc+1);
                    check = 1;
                }
                break;
            
            case 'E':
            case 'e':
                return 2;
                
            default:
                printf("\nInvalid input\n");
                check = 0;
                break;
        }
    } while (check < 1);
    
    return 0;
}

int checkWin(const int grid[], const int gridWin[], int size) {
    for (int i = 0; i < size; i++) {
        if (grid[i] != gridWin[i]) {
            return 0; //Arrays are not equal.
        }
    }
    return 1; //Arrays are equal.
}

int betMode() {
    int moves;
    char* betText =
"\nIn how many moves you think you'll win?\n\
- 1000 points if in exactly M moves.\n\
- 500 points if in the range of [M-10, M].\n\
- 100 points if in the range of [M, M+10].\n\
- 0 points otherwise\n\n";

    printf("%s", betText);
    do {
        printf("Pick a number between 40 and 200: \n");
        moves = validInput();
    } while (moves < 40  || moves > 200);
    
    return moves;
}

int calcPoints(int moves, int bet) {
    if (moves < bet && moves >= bet-10) {
        return 500; //If done between M and M-10 moves.
    } else if (moves > bet && moves <= bet+10) {
        return 100; //If done between M and M+10 moves.
    } else if (moves == bet) {
        return 1000; //If done in exactly M moves.
    } else {
        return 0;
    }
}

int gamePlay(int* grid, int* winGrid, int size, int bet) {
    int totalMoves = 0;
    int score = 0;
    int ending; // 0 Normal state - 1 ended by wining - 2 ended by quiting
    
    do { // We ask the player to move the square...
        clearConsole();
        printf("\nTotal Moves: %d\n", totalMoves);
        showGrid(grid, size);
        if (moveSpace(grid, size) == 2) {
            ending = 2;
            score = -1;
            printf("No points for quitters!\n");
            printf("Next time for sure!\n\n\n");
        } else if (checkWin(grid, winGrid, size) == 1) {
            ending = 1;
            totalMoves += 1;
            clearConsole();
            printf("\nYou won!\n");
        } else {
            totalMoves += 1; // We count the total moves made in the game;
            ending = 0;
        }
    } while (ending < 1); //... until the game its solved or exit.
    
    if (bet > 0 && ending == 1) {
        //If there was a bet for moves we run this to calculate points and print the results.
        score = calcPoints(totalMoves, bet);
        printf("Total moves: %d\n", totalMoves);
        printf("Moves bet: %d\n", bet);
        printf("\nYou Total Score is: %d\n\n", score);
    }
    
    return score;
}

void gameMode(int op1, int op2, int op3) {
    // op1 - Bet / op2 - 10rounds / op3 - timer

    int winGrid[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int grid[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int movesBet = 0;
    
    if (op2 == 1) {
        // We initialize an array to store all the games scores.
        int allScores[10][2] = {
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}, 
            {EMPTY, EMPTY}
            };
        int totalGames = 1;
        int gameResult;
        
        //We use this to store the timer values depending on operative system
        #ifdef __unix__
            struct timeval start, end;
        #elif defined(__WIN32__) || defined(__WIN64__)
            SYSTEMTIME start, end;
        #endif
        double totalTime;
        int minutes, seconds;
        
        do {
            for (int i = 0; i < SIZE; i++) {
                grid[i] = i+1;
            }
            do { // We create random grid starts...
                randomizeGrid(grid, SIZE);
            } while (viableGrid(grid,SIZE) != 1); //...until its a playable one.

            movesBet = betMode(); //Store the moves bet for the current game.

            if (op3 == 1) {
                //We initialize the timer for the current game.
                #ifdef __unix__
                    gettimeofday(&start, NULL);
                #elif defined(__WIN32__) || defined(__WIN64__)
                    GetSystemTime(&start);
                #endif
            }

            gameResult = gamePlay(grid, winGrid, SIZE, movesBet); //Game starts.

            if (op3 == 1) {
                //Once the game is won we stop the timer.
                #ifdef __unix__
                    gettimeofday(&end, NULL);
                    totalTime = getTimeUnix(start, end);
                #elif defined(__WIN32__) || defined(__WIN64__)
                    GetSystemTime(&end);
                    totalTime = getTimeWindows(start, end);
                #endif
            }

            allScores[totalGames-1][0] = gameResult; //We store the score...
            allScores[totalGames-1][1] = totalTime; //And the for that game.
            totalGames++; //We add +1 each time to check once 10 games have completed.

            if (gameResult > -1) {
                //We run this after a game is finished independent of winning or quitting.
                for (int i = 0; i < 10; i++) {
                    //Then we print the scores only if the row in the array has a value.
                    if (allScores[i][0] != EMPTY) {
                        if (allScores[i][1] != EMPTY) {
                            minutes = (int)allScores[i][1] / 60;
                            seconds = (int)allScores[i][1] % 60;
                            printf("Round %d: %d Points in %d:%02d minutes\n", i+1, allScores[i][0], minutes, seconds);
                            
                        } else {
                            printf("Round %d: %d Points\n", i+1, allScores[i][0]);
                        }
                    }
                }
            }
        } while (gameResult != -1 && totalGames <= 10); //We run this entire code until either 10 games have been played or the player quits.
    } else {
        for (int i = 0; i < SIZE; i++) {
                grid[i] = i+1;
            }
        do { // We create random grid starts...
                randomizeGrid(grid, SIZE);
        } while (viableGrid(grid,SIZE) != 1); //...until its a playable one.
        if (op1 == 1) {
            //If Normal Bet mode was selected.
            movesBet = betMode();
            gamePlay(grid, winGrid, SIZE, movesBet);
        } else {
            //If Normal mode was selected.
            gamePlay(grid, winGrid, SIZE, movesBet);
        }
    }
}

void createGame(int mode) {
    
    
    if (mode == 4) {
        gameMode(1, 1, 1);
    } else if (mode == 3) {
        gameMode(1, 1, 0);
    } else if (mode == 2) {
        gameMode(1, 0, 0);
    } else {
        gameMode(0, 0, 0);
    }
}

//######################### Interface/Menus Code #############################

void playMenu() {
    int option;
    
    char* playInterface =
"##### Puzzle15 by Juan Mulet #####\n\n\
              NEW GAME\n\n\
Press a number (0-4) to move through the menu:\n\
1 - Normal Game (1 round, no bets, no timer)\n\
2 - Betting Game (1 round, bet total moves, no timer)\n\
3 - Betting Game 10 (10 games, bet total moves, no timer)\n\
4 - Full Game (Betting Game 10 with timer)\n\n\
0 - Go Back\n\n";

    printf("%s", playInterface);
    
    do {
        option = validInput();
    } while (option > 4 || option < 0);
    
    if (option == 1) {
        createGame(1);
    } else if (option == 2) {
        createGame(2);
    } else if (option == 3) {
        createGame(3);
    } else if (option == 4) {
        createGame(4);
    } else {
        clearConsole();
    }
    
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
        option = validInput();
    } while (option > 2 || option < 0);
    
    if (option == 1) {
        clearConsole();
        printf("\nStill under construction sorry!\n"); 
    } else if (option == 2) {
        clearConsole();
        printf("\nStill under construction sorry!\n"); 
    } else {
        clearConsole();
    }

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
        option = validInput();
    } while (option > 3 || option < 0);
    
    if (option == 1) {
        clearConsole();
        printf("\nStill under construction sorry!\n"); 
    } else if (option == 2) {
        clearConsole();
        printf("\nStill under construction sorry!\n");
    } else if (option == 3) {
        clearConsole();
        printf("\nStill under construction sorry!\n");
    } else {
        clearConsole();
    }

}

void mainMenu() {
    char* mainInterface = 
"##### Puzzle15 by Juan Mulet #####\n\n\
             MAIN MENU\n\n\
Press a number (0-3) to move through the menu:\n\
1 - Start New Game\n\
2 - Highscores\n\
3 - Puzzle Variants\n\
0 - Exit Game\n\n";

    
    int option;
    do {
        printf("%s", mainInterface);
        option = -1;
        do {
            option = validInput();
        } while (option > 3 || option < 0);

        if (option == 1) {
            clearConsole();
            playMenu();
        } else if (option == 2) {
            clearConsole();
            scoreMenu();
        } else if (option == 3) {
            clearConsole();
            variantMenu();
        } else {
            clearConsole();
            printf("\nHope you had fun!\n");
            #ifdef __unix__
                sleep(1.7);
            #elif defined(__WIN32__) || defined(__WIN64__)
                Sleep(1700);
            #endif
            printf("\nGood Bye!\n");
            #ifdef __unix__
                sleep(1);
            #elif defined(__WIN32__) || defined(__WIN64__)
                Sleep(1000);
            #endif
        }

    } while (option != 0);
    
    

}

int main() {
    
    mainMenu();
    
    return 0;
}