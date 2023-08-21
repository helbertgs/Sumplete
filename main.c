#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Sumplete Sumplete;
struct Sumplete {
    int **board;
    int *cols;
    int *rows;
    int size;
};

Sumplete init(int size) {
    Sumplete sumplete;

    sumplete.board = (int **)malloc(size * sizeof(int *));
    sumplete.cols = (int *)malloc(size * sizeof(int *));
    sumplete.rows = (int *)malloc(size * sizeof(int *));
    sumplete.size = size;
    
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

        printf("| %d\n", sumplete->rows[row]);
    }

    for (int i = 0; i < 2 * sumplete->size + 3; i++) {
        printf("-");
    }
    print("\n");

    for (int col = 0; col < sumplete->size; col++) {
        printf("%d ", sumplete->cols[col]);
    }

    print("\n\n");
}