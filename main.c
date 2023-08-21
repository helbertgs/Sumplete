#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Sumplete Sumplete;
struct Sumplete {
    int size;
    int **board;
};

Sumplete init(int size) {
    Sumplete sumplete;
    sumplete.size = size;
    sumplete.board = (int **)malloc(size * sizeof(int *));

    for (int row = 0; row < size; row++) {
        sumplete.board[row] = (int *)malloc(size * sizeof(int *));
    }

    return sumplete;
}

void printBoard(Sumplete *sumplete) {
    for (int row = 0; row < sumplete->size; row++) {
        for (int col = 0; col < sumplete->size; col++) {
            printf("%d ", sumplete->board[row][col]);
        }
    }
}