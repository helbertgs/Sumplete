// Adding Color to Your Programs: https://www.theurbanpenguin.com/4184-2/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definitions
#define WHITE "\033[0;37m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"

typedef struct Score Score;
struct Score {
  char playername[20];
  double time;
};

typedef struct Ranking Ranking;
struct Ranking {
  int size;
  Score score[5];
};

// Estrutura de dados com todas as informações necessárias para o funcionamento
// do jogo.
typedef struct Sumplete Sumplete;
struct Sumplete {
  int **board;
  int **solution;
  int *cols;
  bool isFinished;
  bool isShowMenu;
  char *level;
  char playername[20];
  int *rows;
  int size;
  int **states;
  time_t start;
  time_t end;
};

// Inicializa as informações do jogo.
void initialize(Sumplete *sumplete) {
  sumplete->board = (int **)malloc(sumplete->size * sizeof(int *));
  sumplete->solution = (int **)malloc(sumplete->size * sizeof(int *));
  sumplete->states = (int **)malloc(sumplete->size * sizeof(int *));
  sumplete->cols = (int *)malloc(sumplete->size * sizeof(int *));
  sumplete->rows = (int *)malloc(sumplete->size * sizeof(int *));
  sumplete->isFinished = false;
  sumplete->isShowMenu = false;
  sumplete->start = time(0);
  sumplete->end = time(0);

  for (int row = 0; row < sumplete->size; row++) {
    sumplete->board[row] = (int *)malloc(sumplete->size * sizeof(int *));
    sumplete->states[row] = (int *)malloc(sumplete->size * sizeof(int *));
    sumplete->solution[row] = (int *)malloc(sumplete->size * sizeof(int *));
  }
}

// Gera um array com numeros aleatorios entre 1 e 9.
void generateRandomArray(int size, int arr[]) {
  for (int i = 0; i < size; i++) {
    arr[i] = rand() % 7 + 1;
  }
}

// Gera o board com os numeros aleatorios.
void generateBoard(Sumplete *sumplete) {
  for (int row = 0; row < sumplete->size; row++) {
    generateRandomArray(sumplete->size, sumplete->board[row]);
  }

  // Determina quais os elementos serão usados no somatório das linhas/colunas.
  for (int i = 0; i < sumplete->size; i++) {
    for (int j = 0; j < sumplete->size; j++) {
      int num = rand() % 7 + 1;
      if (num < 5) {
        sumplete->solution[i][j] = 0;
      } else {
        sumplete->solution[i][j] = sumplete->board[i][j];
      }
    }
  }

  for (int i = 0; i < sumplete->size; i++) {
    int sum = 0;
    for (int j = 0; j < sumplete->size; j++) {
      sum += sumplete->solution[i][j];
    }
    sumplete->rows[i] = sum;
  }

  for (int i = 0; i < sumplete->size; i++) {
    int sum = 0;
    for (int j = 0; j < sumplete->size; j++) {
      sum += sumplete->solution[j][i];
    }
    sumplete->cols[i] = sum;
  }
}

// Altera a cor do elemento, quando o mesmo for exibido no console. A cor sera
// baseada no estado do elemento.
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
  sumplete->end = time(0);
  printf("Time: %f\n", difftime(sumplete->end, sumplete->start));
  for (int row = 0; row < sumplete->size; row++) {
    for (int col = 0; col < sumplete->size; col++) {
      changeCharacterColor(sumplete->board[row][col],
                           sumplete->states[row][col]);
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

// Função responsável por exibir o board.
void printSolution(Sumplete *sumplete) {
  printf("\n");
  for (int row = 0; row < sumplete->size; row++) {
    for (int col = 0; col < sumplete->size; col++) {
      changeCharacterColor(sumplete->solution[row][col],
                           sumplete->states[row][col]);
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

// Le os dados de um arquivo e carrega os mesmos em uma string.
char *readAndLoadFile(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long fileLength = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = (char *)malloc(fileLength + 1);
  if (content == NULL) {
    perror("Erro ao alocar memória");
    fclose(file);
    return NULL;
  }

  size_t bytesRead = fread(content, 1, fileLength, file);
  if (bytesRead != (size_t)fileLength) {
    perror("Erro ao ler o arquivo");
    free(content);
    fclose(file);
    return NULL;
  }

  content[fileLength] = '\0';

  fclose(file);
  return content;
}

char *readLineFromFile(const char *filename, int lineNumber) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo");
    return NULL;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  for (int i = 1; i <= lineNumber; i++) {
    read = getline(&line, &len, file);
    if (read == -1) {
      if (feof(file)) {
        fprintf(stderr, "A linha %d está fora dos limites do arquivo\n",
                lineNumber);
        free(line);
        fclose(file);
        return NULL;
      } else {
        perror("Erro ao ler a linha do arquivo");
        free(line);
        fclose(file);
        return NULL;
      }
    }
  }

  fclose(file);
  return line;
}

// Salva os dados de uma string em um arquivo.
void saveToFile(const char *filename, const char *content) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para escrita");
    return;
  }

  if (fprintf(file, "%s", content) < 0) {
    perror("Erro ao escrever no arquivo");
  }

  fclose(file);
}

// Seleciona o nome do jogador
void selectPlayerName(Sumplete *sumplete) {
  bool execute = true;

  while (execute) {
    char playername[20];
    printf("Digite o nome do jogador 1: ");
    scanf("%s", playername);

    if (strcmp(playername, "") != 0) {
      strncpy(sumplete->playername, playername, 20);
      execute = false;
    }
  }
}

// Solcita ao jogador o tamanho do tabuleiro.
void selectBoardSize(Sumplete *sumplete) {
  bool execute = true;

  while (execute) {
    int size;
    printf("Digite o tamanho do tabuleiro (3 a 9): ");
    scanf("%d", &size);

    int *aux = &size;

    if (*aux > 2 && *aux < 10) {
      sumplete->size = size;
      execute = false;
    }
  }
}

// Solicita ao jogador o nivel de dificuldade do tabuleiro apenas se a dimensão
// do tabuleiro for maior que 4.
void selectLevel(Sumplete *sumplete) {
  if (sumplete->size < 5) {
    sumplete->level = "F";
    return;
  }

  bool execute = true;

  while (execute) {
    char level;
    printf("Digite o nivel de dificuldade:");
    printf("\nF - Facil\nM - Medio\nD - Dificil\nDificuldade: ");
    scanf(" %c", &level);

    char *aux = &level;

    if (*aux == 'D' || *aux == 'F' || *aux == 'M') {
      sumplete->level = &level;
      execute = false;
    }
  }
}

// Encerra o jogo.
void exitGame(Sumplete *sumplete) { sumplete->isFinished = true; }

// Altera a matriz de estado onde os elemntos informam se o elemento deve ser
// removido ou mantido, com base na matriz de solução.
void resolve(Sumplete *sumplete) {
  for (int row = 0; row < sumplete->size; row++) {
    for (int col = 0; col < sumplete->size; col++) {
      if (sumplete->solution[row][col] > 0) {
        markAsRetain(sumplete, row, col);
      } else {
        markAsRemoved(sumplete, row, col);
      }
    }
  }
}

void saveGame(Sumplete *sumplete) {

  char rows[40];

  for (int row = 0; row < sumplete->size; row++) {
    if (row == 0) {
      sprintf(rows, "%d", sumplete->rows[row]);
    } else {
      sprintf(rows, "%s %d", rows, sumplete->rows[row]);
    }
  }

  FILE *fp;
  fp = fopen("save.txt", "w");

  char text[1024];
  sprintf(text, "%d\n%s\n%s\n%d", sumplete->size, rows, sumplete->playername,
          (int)difftime(time(0), sumplete->start));

  fputs(text, fp);
  fputs("\r\n", fp);

  fclose(fp);

  // char matrix[256];

  // for (int row = 0; row < sumplete->size; row++) {
  //   for (int col = 0; col < sumplete->size; col++) {
  //     sprintf(matrix, "%s %d", matrix, sumplete->board[row][col]);
  //   }
  //   sprintf(matrix, "%s\n", matrix);
  //   printf("%s", matrix);
  // }
}

// Continua com o jogo atual.
void continueGame(Sumplete *sumplete) {
  sumplete->isFinished = false;

  printBoard(sumplete);
  char command[20];
  printf("%s, digite o comando: ", sumplete->playername);
  scanf(" %s", command);

  if (strcmp(command, "voltar") == 0) {
    sumplete->isShowMenu = true;
  } else if (strcmp(command, "manter") == 0) {
    printf("Opcao selecionada: Manter\n");
  } else if (strcmp(command, "remover") == 0) {
    printf("Opcao selecionada: Remover\n");
  } else if (strcmp(command, "resolver") == 0) {
    resolve(sumplete);
  } else if (strcmp(command, "salvar") == 0) {
    saveGame(sumplete);
  } else {
    printf("Opcao invalida\n");
  }
}

// Inicia um novo jogo.
void startNewGame(Sumplete *sumplete) {
  selectPlayerName(sumplete);
  selectBoardSize(sumplete);
  selectLevel(sumplete);
  initialize(sumplete);
  generateBoard(sumplete);
  continueGame(sumplete);
}

// Exibe o ranking.
void showRanking(Sumplete *sumplete) {
  char *file = readAndLoadFile("sumplete.ini");
  printf("%s\n\n", file);
  sumplete->isShowMenu = true;
}

// Carrega um jogo salvo.
void loadGame(Sumplete *sumplete) { sumplete->board[2][1] = 5; }

// Menu principal do jogo.
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

  while (!sumplete->isFinished) {
    if (sumplete->isShowMenu) {
      sumplete->isFinished = true;
    } else {
      continueGame(sumplete);
    }
  }

  if (sumplete->isShowMenu) {
    sumplete->isShowMenu = false;
    menu(sumplete);
  }
}

int main(void) {
  Sumplete sumplete;
  menu(&sumplete);

  return 0;
}