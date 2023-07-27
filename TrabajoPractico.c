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
    } else {
        printf("\n El juego NO es posible de resolver");
    }
    
    return totalInversions;
}

void randomizeGrid(int* grid, int size) {
    
    //We generate a random seed for it to be fully random.
    srand(time(NULL));
    
    //We move in the array from end to start
    for(int i = size-1; i > 0; i--) {
        //We generate a random index between 0 and i, including i.
        int j = rand() % (i + 1);
        
        //We perform a simple swap using a temp variable
        int temp = grid[i];
        grid[i] = grid[j];
        grid[j] = temp;
    }
    
}

int main() {
    int gameGrid[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int gameWin[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    printf("Array randomizado:\n");
    for(int i = 0; i < SIZE; i++) {
        if (gameGrid[i] == 16) {
            printf("|    ");
        } else {
            printf("| %2d ", gameGrid[i]);
        }
        if((i+1) % 4 == 0) {
            printf("|");
            printf("\n");
            printf(" -------------------\n");
        }
    }
    
    randomizeGrid(gameGrid, SIZE);
    
    printf("\n\nArray randomizado:\n");
    for(int i = 0; i < SIZE; i++) {
        if (gameGrid[i] == 16) {
            printf("|    ");
        } else {
            printf("| %2d ", gameGrid[i]);
        }
        if((i+1) % 4 == 0) {
            printf("|");
            printf("\n");
            printf(" -------------------\n");
        }
    }
    
    viableGrid(gameGrid, SIZE);
    

    return 0;
}