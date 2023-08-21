// Adding Color to Your Programs: https://www.theurbanpenguin.com/4184-2/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Definitions
#define WHITE "\033[0;37m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"

typedef struct Sumplete Sumplete;
struct Sumplete {
  int **board;
  int **states;
  int *cols;
  int *rows;
  int size;
};

Sumplete init(int size) {
  Sumplete sumplete;

  sumplete.board = (int **)malloc(size * sizeof(int *));
  sumplete.states = (int **)malloc(size * sizeof(int *));
  sumplete.cols = (int *)malloc(size * sizeof(int *));
  sumplete.rows = (int *)malloc(size * sizeof(int *));
  sumplete.size = size;

  for (int row = 0; row < size; row++) {
    sumplete.board[row] = (int *)malloc(size * sizeof(int *));
    sumplete.states[row] = (int *)malloc(size * sizeof(int *));
  }

  return sumplete;
}

// Altera a cor do elemento, quando o mesmo for exibido no console. A cor sera baseada no estado do elemento.
void changeCharacterColor(int value, int state) {
  switch (state) {
  case 1:
    printf(RED);
    printf("%d ", value);
    break;
  case 2:
    printf(GREEN);
    printf("%d ", value);
    break;
  default:
    printf("%d ", value);
  }

  printf(WHITE);
}

// Função responsável por exibir o board.
void printBoard(Sumplete *sumplete) {
  for (int row = 0; row < sumplete->size; row++) {
    for (int col = 0; col < sumplete->size; col++) {
      changeCharacterColor(sumplete->board[row][col], sumplete->states[row][col]);
    }

    printf("| %d\n", sumplete->rows[row]);
  }

  for (int i = 0; i < 2 * sumplete->size + 3; i++) {
    printf("-");
  }
  printf("\n");

  for (int col = 0; col < sumplete->size; col++) {
    printf("%d ", sumplete->cols[col]);
  }

  printf("\n\n");
}

// Altera o estado de um indice da matriz para: "estado desconhecido".
void markAsUnknown(Sumplete *sumplete, int row, int col) {
  sumplete->states[row][col] = 0;
}

// Altera o estado de um indice da matriz para: "Numero removido".
void markAsRemoved(Sumplete *sumplete, int row, int col) {
  sumplete->states[row][col] = 1;
}

// Altera o estado de um indice da matriz para: "Numero mantido".
void markAsRetain(Sumplete *sumplete, int row, int col) {
  sumplete->states[row][col] = 2;
}

int main(void) {
  return 0;
}
