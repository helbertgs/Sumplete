#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Sumplete Sumplete;
struct Sumplete {
    int **board;
};

Sumplete init(int size) {
    Sumplete sumplete;
    sumplete.board = (int **)malloc(size * sizeof(int *));

    for (int row = 0; row < size; row++) {
        sumplete.board[row] = (int *)malloc(size * sizeof(int *));
    }

    return sumplete;
}