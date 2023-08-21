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
  int *cols;
  bool isFinished;
  char *level;
  char *playername;
  int *rows;
  int size;
  int **states;
};

void initialize(Sumplete *sumplete, int size) {
  sumplete->board = (int **)malloc(size * sizeof(int *));
  sumplete->states = (int **)malloc(size * sizeof(int *));
  sumplete->cols = (int *)malloc(size * sizeof(int *));
  sumplete->rows = (int *)malloc(size * sizeof(int *));
  sumplete->size = size;
  sumplete->playername = "";
  sumplete->level = "";
  sumplete->isFinished = false;

  for (int row = 0; row < size; row++) {
    sumplete->board[row] = (int *)malloc(size * sizeof(int *));
    sumplete->states[row] = (int *)malloc(size * sizeof(int *));
  }
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

void startNewGame(Sumplete *sumplete) {
}

void loadGame(Sumplete *sumplete) {
}

void continueGame(Sumplete *sumplete) {
}

void showRanking(Sumplete *sumplete) {
}

void exitGame(Sumplete *sumplete) {
  sumplete->isFinished = true;
}

void menu(Sumplete *sumplete) {
  printf("Bem vindo ao jogo SUMPLETE\n\n0. Sair do jogo\n1. Começar um novo "
         "jogo\n2. Continuar um jogo salvo em arquivo\n3. Continuar o jogo "
         "atual\n4. Exibir o ranking\nDurante o jogo digite \"voltar\" para "
         "retornar ao menu.\n\nEscolha a opção: ");

  int option;
  scanf("%d", &option);

  switch (option) {
  case 0:
    exitGame(sumplete);
    break;
  case 1:
    startNewGame(sumplete);
    break;
  case 2:
    loadGame(sumplete);
    break;
  case 3:
    continueGame(sumplete);
    break;
  case 4:
    showRanking(sumplete);
    break;
  default:
    printf("Comando desconhecido!");
  }
}

int main(void) {
  Sumplete sumplete;

  menu(&sumplete);
  return 0;
}
