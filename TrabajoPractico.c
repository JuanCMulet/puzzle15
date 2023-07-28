#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 16

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
    
    printf("\n\n El total de inversiones es: %d", totalInversions);
    printf("\n El espacio vacío se encuentra en la fila: %d", row);
    
    /*  
        To know if a grid game is viable we add the total inversions and the row in wich the blank space is
        located. If the sum is an even number then its viable, otherwise its not. For a better explanation on how
        this works visit: 
        https://www.youtube.com/watch?v=YI1WqYKHi78&ab_channel=Numberphile
        https://mathworld.wolfram.com/15Puzzle.html 
    */
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
    printf("\nW - UP | A - LEFT | S - DOWN | D - RIGHT\n\n");
}

void swapSpace(int* grid, int size, int i, int j) {
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

void moveSpace(int* grid, int size) {
    char option;
    int check;
    int loc;
    int temp;
    
    for (int i = 0; i < size ; i++) {
        if (grid[i] == 16) {
            loc = i;
        }
    }
    
    do {
        printf("Move to: ");
        scanf(" %c", &option);
        
        switch (option) {
            case 'W':
            case 'w':
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
            
            default:
                printf("\nInvalid input\n");
                check = 0;
                break;
        }
    } while (check < 1);
    
    
    
}

int checkWin(const int grid[], const int gridWin[], int size) {
    for (int i = 0; i < size; i++) {
        if (grid[i] != gridWin[i]) {
            return 0; // Arrays are not equal
        }
    }
    return 1; // Arrays are equal
}

void createGame(int* grid, int* winGrid, int size) {
    do {
        randomizeGrid(grid, size);
    } while (viableGrid(grid,size) != 1);
    showGrid(grid, size);
    
    do {
        moveSpace(grid, size);
        showGrid(grid, size);
    } while (checkWin(grid, winGrid, size) < 1);
    
    printf("You won!");
    
}

int main() {
    int gameGrid[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 15};
    int gameWin[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    createGame(gameGrid, gameWin, SIZE);
    

    return 0;
}